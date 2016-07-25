#include <Components.hpp>
#include "InputSystem.hpp"
#include "EntitySystem.hpp"

InputSystem::InputSystem(EntitySystem& ents, OIS::Keyboard& key, Ogre::Camera& cam)
	: entities_{ents}, first_person_{false}, first_person_id_{Component::NO_ENTITY}, keyboard_{key},
	  KEY_UP{OIS::KC_W}, KEY_DOWN{OIS::KC_S}, KEY_LEFT{OIS::KC_A}, KEY_RIGHT{OIS::KC_D},
	  cam_{cam}, cam_position_{}, cam_orientation_{}, ai_backup_{nullptr},
	  task_backup_{nullptr}, delete_input_{false}
{ /* DUMMY BODY */ }

void InputSystem::update(tdt::real delta)
{
	if(first_person_)
	{
		bool moved{false}, rotated{false};

		lpp::Script& script = lpp::Script::instance();
		auto& in_comp = *entities_.get_component<InputComponent>(first_person_id_);
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_UP))
		{
			script.call<void, tdt::uint, int>(in_comp.input_handler + ".handle", first_person_id_, KEY_UP);
			moved = true;
		}
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_DOWN))
		{
			script.call<void, tdt::uint, int>(in_comp.input_handler + ".handle", first_person_id_, KEY_DOWN);
			moved = true;
		}
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_LEFT))
		{
			script.call<void, tdt::uint, int>(in_comp.input_handler + ".handle", first_person_id_, KEY_LEFT);
			rotated = true;
		}
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_RIGHT))
		{
			script.call<void, tdt::uint, int>(in_comp.input_handler + ".handle", first_person_id_, KEY_RIGHT);
			rotated = true;
		}

		auto& graph_comp = *entities_.get_component<GraphicsComponent>(first_person_id_);
		if(rotated)
		{ // TODO: Due to the fact that ogrehead.mesh is facing backwards, this will make the view right, but the
		  //       controlls get swapped, research!
			cam_.setOrientation(
				graph_comp.node->getOrientation() * Ogre::Quaternion{Ogre::Degree{180.f}, Ogre::Vector3::UNIT_Y}
			);
		}
		if(moved)
		{
			cam_.setPosition(graph_comp.node->getPosition());
		}
	}
}

bool InputSystem::is_first_person() const
{
	return first_person_;
}

void InputSystem::set_first_person(bool on_off, tdt::uint id)
{
	if(on_off == first_person_)
		return; // Only one first person mode entity at a time.


	if(id != Component::NO_ENTITY)
		first_person_id_ = id; // Allows for escaping first person mode without specifying the entity ID.
	first_person_ = on_off;

	if(first_person_ && !entities_.has_component<GraphicsComponent>(first_person_id_))
	{
		first_person_ = false;
		return;
	}


	if(first_person_)
	{
		cam_position_ = cam_.getPosition();
		cam_orientation_ = cam_.getOrientation();

		// Adds the InputComponent if possible.
		bool ai = entities_.has_component<AIComponent>(first_person_id_);
		if(!entities_.has_component<InputComponent>(first_person_id_) && ai)
		{
			delete_input_ = true; // Delete it afterwards.

			entities_.add_component<InputComponent>(first_person_id_); // The entity has to have InputComponent blueprint.
			auto& ai_comp = *entities_.get_component<AIComponent>(first_person_id_);
			auto& in_comp = *entities_.get_component<InputComponent>(first_person_id_);

			auto& script = lpp::Script::instance();
			if(!script.is_nil(ai_comp.blueprint + ".InputComponent.input_handler"))
				in_comp.input_handler = script.get<std::string>(ai_comp.blueprint + ".InputComponent.input_handler");
		}

		// AIComponent backup.
		if(ai)
		{
			ai_backup_.reset(new AIComponent{std::move(*entities_.get_component<AIComponent>(first_person_id_))});
			entities_.delete_component<AIComponent>(first_person_id_);
		}

		auto task_handler = entities_.get_component<TaskHandlerComponent>(first_person_id_);
		if(task_handler)
		{
			task_backup_.reset(new TaskHandlerComponent{*task_handler});
			entities_.delete_component<TaskHandlerComponent>(first_person_id_);
		}

		auto& graph_comp = *entities_.get_component<GraphicsComponent>(first_person_id_);
		cam_.setOrientation(
			graph_comp.node->getOrientation() * Ogre::Quaternion{Ogre::Degree{180.f}, Ogre::Vector3::UNIT_Y}
		);
		cam_.setPosition(graph_comp.node->getPosition());
	}
	else
	{ // Restore 3rd person view.
		cam_.setPosition(cam_position_);
		cam_.setOrientation(cam_orientation_);

		// AIComponent restore.
		if(ai_backup_)
		{
			entities_.add_component<AIComponent>(first_person_id_);
			auto ai_comp = entities_.get_component<AIComponent>(first_person_id_);

			if(ai_comp)
			{
				*ai_comp = std::move(*ai_backup_);
				ai_backup_.reset(nullptr);
			}
		}

		if(task_backup_)
		{
			entities_.add_component<TaskHandlerComponent>(first_person_id_);
			auto task_comp = entities_.get_component<TaskHandlerComponent>(first_person_id_);
			
			if(task_comp)
			{
				task_comp->busy = task_backup_->busy;
				task_comp->curr_task = task_backup_->curr_task;
				task_comp->possible_tasks = task_backup_->possible_tasks;
				task_comp->task_queue.swap(task_backup_->task_queue);
				task_backup_.reset(nullptr);
			}
		}

		if(delete_input_)
		{
			delete_input_ = false;
			entities_.delete_component<InputComponent>(first_person_id_);
		}
	}
	entities_.get_component<GraphicsComponent>(first_person_id_)->node->setVisible(!first_person_);
}

void InputSystem::rebind(int key, int new_key)
{
	lpp::Script& script = lpp::Script::instance();
	switch(key)
	{
		case OIS::KC_W:
			KEY_UP = new_key;
			script.set("game.enum.input.key_up", KEY_UP);
			break;
		case OIS::KC_S:
			KEY_DOWN = new_key;
			script.set("game.enum.input.key_down", KEY_DOWN);
			break;
		case OIS::KC_A:
			KEY_LEFT = new_key;
			script.set("game.enum.input.key_left", KEY_LEFT);
			break;
		case OIS::KC_D:
			KEY_RIGHT = new_key;
			script.set("game.enum.input.key_right", KEY_RIGHT);
			break;
		default:
			break;
	}
}
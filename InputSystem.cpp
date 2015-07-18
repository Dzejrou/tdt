#include "InputSystem.hpp"

InputSystem::InputSystem(EntitySystem& ents, OIS::Keyboard& key)
	: entities_{ents}, first_person_{false}, first_person_id_{0}, keyboard_{key},
	KEY_UP{OIS::KC_W}, KEY_DOWN{OIS::KC_S}, KEY_LEFT{OIS::KC_A}, KEY_RIGHT{OIS::KC_D}
{ /* DUMMY BODY */ }

void InputSystem::update(Ogre::Real delta)
{
	lpp::Script& script = lpp::Script::get_singleton();
	for(auto& ent : entities_.get_component_container<InputComponent>())
	{
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_UP))
			script.call<void, std::size_t, int>(ent.second.input_handler, ent.first, KEY_UP);
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_DOWN))
			script.call<void, std::size_t, int>(ent.second.input_handler, ent.first, KEY_DOWN);
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_LEFT))
			script.call<void, std::size_t, int>(ent.second.input_handler, ent.first, KEY_LEFT);
		if(keyboard_.isKeyDown((OIS::KeyCode)KEY_RIGHT))
			script.call<void, std::size_t, int>(ent.second.input_handler, ent.first, KEY_RIGHT);
	}
}

bool InputSystem::is_valid(std::size_t id) const
{
	return entities_.has_component<InputComponent>(id);
}

bool InputSystem::is_first_person() const
{
	return first_person_;
}

void InputSystem::set_first_person(bool on_off, std::size_t id)
{
	first_person_ = on_off;
	first_person_id_ = id;
}

void InputSystem::rebind(int key, int new_key)
{
	lpp::Script& script = lpp::Script::get_singleton();
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

void InputSystem::set_input_handler(std::size_t id, const std::string& handler)
{
	if(is_valid(id))
		entities_.get_component<InputComponent>(id).input_handler = handler;
}

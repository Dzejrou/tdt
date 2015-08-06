#include "GameSerializer.hpp"
#include "Game.hpp"

GameSerializer::GameSerializer(EntitySystem& ents)
	: entities_{ents}, script_{lpp::Script::get_singleton()}, saved_entities_{},
	  file_{}
{ /* DUMMY BODY */ }

void GameSerializer::save_game(Game& game, const std::string& fname)
{
	std::string file_name{"saves/" + fname + ".lua"};
	file_.open(file_name);
	std::vector<std::string> temp_vars{};

	// TODO: Things like player info etc.

	// Save the map info.
	std::string map{
		  "game.create_graph(" + std::to_string(game.grid_system_->width_) + ", "
		+ std::to_string(game.grid_system_->height_) + ", " + std::to_string(game.grid_system_->distance_)
		+ ", " + std::to_string(game.grid_system_->start_.x) + ", " + std::to_string(game.grid_system_->start_.y)
		+ ")\n"
	};
	std::string nodes{"\n-- GRAPH NODE ALIASES:\n"};
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
	{
		nodes.append("entity_" + std::to_string(ent.first) + "=" +  std::to_string(ent.first) + "\n");
		temp_vars.emplace_back("entity_" + std::to_string(ent.first));
	}
	file_ << map << nodes << "\n\n -- ENTITIES:";

	// Save individual entities.
	std::string entity_name{};
	for(const auto& ent : entities_.get_component_list())
	{
		// Do not save nodes and lines!
		if(ent.second.test(GridNodeComponent::type) || ent.second.test(GridLineComponent::type))
			continue;

		entity_name = "entity_" + std::to_string(ent.first);
		temp_vars.push_back(entity_name);
		
		file_ << "\n" << entity_name + " = game.create_entity()\n";
		for(std::size_t i = 0; i < ent.second.size(); ++i)
		{
			if(ent.second.test(i))
			{
				switch(i)
				{
					case PhysicsComponent::type:
						save_component<PhysicsComponent>(ent.first, entity_name);
						break;
					case HealthComponent::type:
						save_component<HealthComponent>(ent.first, entity_name);
						break;
					case AIComponent::type:
						save_component<AIComponent>(ent.first, entity_name);
						break;
					case GraphicsComponent::type:
						save_component<GraphicsComponent>(ent.first, entity_name);
						break;
					case MovementComponent::type:
						save_component<MovementComponent>(ent.first, entity_name);
						break;
					case CombatComponent::type:
						save_component<CombatComponent>(ent.first, entity_name);
						break;
					case EventComponent::type:
						save_component<EventComponent>(ent.first, entity_name);
						break;
					case InputComponent::type:
						save_component<InputComponent>(ent.first, entity_name);
						break;
					case TimeComponent::type:
						save_component<TimeComponent>(ent.first, entity_name);
						break;
					case ManaComponent::type:
						save_component<ManaComponent>(ent.first, entity_name);
						break;
					case SpellComponent::type:
						save_component<SpellComponent>(ent.first, entity_name);
						break;
					case ProductionComponent::type:
						save_component<ProductionComponent>(ent.first, entity_name);
						break;
					case PathfindingComponent::type:
						save_component<PathfindingComponent>(ent.first, entity_name);
						break;
					case TaskComponent::type:
						save_component<TaskComponent>(ent.first, entity_name);
						break;
					case TaskHandlerComponent::type:
						save_component<TaskHandlerComponent>(ent.first, entity_name);
						break;
				}
			}
		}	
	}
	save_tasks();

	file_ << "\n\n -- AUXILIARY VARIABLES TO BE DELETED:\nto_be_deleted = {\n";
	std::size_t count{0}; // Saves vertical space.
	for(const auto& tmp : temp_vars)
	{ // This will allow to delete all those auxiliary variables when loading.
		file_ << tmp + ", ";
		if(count++ % 10 == 0)
			file_ << "\n";
	}
	file_ << "}";
	file_.flush();
	file_.close();
}

void GameSerializer::load_game(Game& game, const std::string& fname)
{
	// Clean current game.
	for(auto& ent : entities_.get_component_list())
	{
		entities_.destroy_entity(ent.first);
	}
	entities_.cleanup();

	std::string file_name{"saves/" + fname + ".lua"};
	try
	{
		script_.load(file_name); // Yes, THAT simple!
	}
	catch(lpp::Exception& ex)
	{
		game.console_.print_text("<FAIL> Could not load from file: " + fname, Console::RED_TEXT);
		game.console_.print_text(ex.what_lua(), Console::RED_TEXT);
	}
}

void GameSerializer::save_tasks()
{
	file_ << "\n -- TASKS: --\n";
	for(auto& task_pair : task_pairs_)
	{
		file_ << "game.add_task(entity_" + std::to_string(task_pair.first) + ", entity_"
			   + std::to_string(task_pair.second) + ")\n";
	}
	task_pairs_.clear();
}

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

	std::string entity_name{};
	for(const auto& ent : entities_.get_component_list())
	{
		entity_name = "entity_" + std::to_string(ent.first);
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
					case ManaComponent::type:
					case SpellComponent::type:
					case ProductionComponent::type:
						// TODO:
						break;
					case GridNodeComponent::type:
					case GridLineComponent::type:
						// Cannot be loaded automatically, will be handled by GridSystem.
						// TODO: More research on this.
						break;
					case PathfindingComponent::type:
						save_component<PathfindingComponent>(ent.first, entity_name);
						break;
					case TaskComponent::type:
						// Cannot be loaded automatically, will be handled by TaskSystem.
						break;
					case TaskHandlerComponent::type:
						save_component<TaskHandlerComponent>(ent.first, entity_name);
						break;
				}
			}
		}
	
	}
}

void GameSerializer::load_game(Game& game, const std::string& fname)
{
	std::string file_name{"saves/" + fname + ".lua"};

	try
	{
		script_.load(file_name); // Yes, THAT simple!
	}
	catch(lpp::Exception& ex)
	{
		game.console_.print_text("<FAIL> Could not load from file: " + fname, Console::RED_TEXT);
	}
}

void GameSerializer::save_entity(std::size_t)
{
}

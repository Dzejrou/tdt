#include "GameSerializer.hpp"
#include "Game.hpp"
#include "GUI.hpp"

/**
 * Brief: Macro that serves as a simpler way to use the serializers_ array when calling it's members.
 * Param: Type of the component to be loaded.
 * Param: ID of the entity that loads the component.
 * Param: Name of the table that contains the component data.
 */
#define SAVE_COMPONENT(TYPE, ID, TABLE) (((this)->*serializers_[TYPE])(ID, TABLE))

GameSerializer::GameSerializer(EntitySystem& ents)
	: entities_{ents}, script_{lpp::Script::get_singleton()},
	  file_{}, save_entities_{}, save_components_{},
	  serializers_{}
{
	serializers_[PhysicsComponent::type] = &GameSerializer::save_component<PhysicsComponent>;
	serializers_[HealthComponent::type] = &GameSerializer::save_component<HealthComponent>;
	serializers_[AIComponent::type] = &GameSerializer::save_component<AIComponent>;
	serializers_[GraphicsComponent::type] = &GameSerializer::save_component<GraphicsComponent>;
	serializers_[MovementComponent::type] = &GameSerializer::save_component<MovementComponent>;
	serializers_[CombatComponent::type] = &GameSerializer::save_component<CombatComponent>;
	serializers_[EventComponent::type] = &GameSerializer::save_component<EventComponent>;
	serializers_[InputComponent::type] = &GameSerializer::save_component<InputComponent>;
	serializers_[TimeComponent::type] = &GameSerializer::save_component<TimeComponent>;
	serializers_[ManaComponent::type] = nullptr; // TODO
	serializers_[SpellComponent::type] = nullptr; // TODO
	serializers_[ProductionComponent::type] = &GameSerializer::save_component<ProductionComponent>;
	serializers_[GridNodeComponent::type] = nullptr; // Cannot be saved, is generated with the graph.
	serializers_[ProductComponent::type] = &GameSerializer::save_component<ProductComponent>;
	serializers_[PathfindingComponent::type] = &GameSerializer::save_component<PathfindingComponent>;
	serializers_[TaskComponent::type] = &GameSerializer::save_component<TaskComponent>;
	serializers_[TaskHandlerComponent::type] = &GameSerializer::save_component<TaskHandlerComponent>;
	serializers_[StructureComponent::type] = &GameSerializer::save_component<StructureComponent>;
	serializers_[HomingComponent::type] = &GameSerializer::save_component<HomingComponent>;
	serializers_[EventHandlerComponent::type] = &GameSerializer::save_component<EventHandlerComponent>;
	serializers_[DestructorComponent::type] = &GameSerializer::save_component<DestructorComponent>;
	serializers_[GoldComponent::type] = &GameSerializer::save_component<GoldComponent>;
	serializers_[FactionComponent::type] = &GameSerializer::save_component<FactionComponent>;
	serializers_[PriceComponent::type] = &GameSerializer::save_component<PriceComponent>;
	serializers_[AlignComponent::type] = &GameSerializer::save_component<AlignComponent>;
	serializers_[MineComponent::type] = &GameSerializer::save_component<MineComponent>;
	serializers_[ManaCrystalComponent::type] = &GameSerializer::save_component<ManaCrystalComponent>;
	serializers_[OnHitComponent::type] = &GameSerializer::save_component<OnHitComponent>;
	serializers_[ConstructorComponent::type] = &GameSerializer::save_component<ConstructorComponent>;
	serializers_[TriggerComponent::type] = &GameSerializer::save_component<TriggerComponent>;
	serializers_[UpgradeComponent::type] = &GameSerializer::save_component<UpgradeComponent>;
	serializers_[NotificationComponent::type] = &GameSerializer::save_component<NotificationComponent>;
	serializers_[ExplosionComponent::type] = &GameSerializer::save_component<ExplosionComponent>;
	serializers_[LimitedLifeSpanComponent::type] = &GameSerializer::save_component<LimitedLifeSpanComponent>;
}

void GameSerializer::save_game(Game& game, const std::string& fname)
{
	std::string file_name{"saves/" + fname + ".lua"};
	file_.open(file_name);
	std::vector<std::string> temp_vars{};

	std::string header{
		"game.gui.log.clear()\n"
	};

	auto& player = Player::instance();
	std::string plr{
		  "game.player.nulify_stats()\ngame.player.add_gold(" + std::to_string(player.get_gold())
		+ ")\ngame.player.add_mana(" + std::to_string(player.get_mana())
		+ ")\ngame.player.add_max_mana(" + std::to_string(player.get_max_mana())
		+ ")\ngame.player.add_mana_regen(" + std::to_string(player.get_mana_regen()) + ")\n\n"
	};

	// Save the map info.
	std::string map{
		  "game.grid.create(" + std::to_string(Grid::instance().width_) + ", "
		+ std::to_string(Grid::instance().height_) + ", " + std::to_string(Grid::instance().distance_)
		+ ", " + std::to_string(Grid::instance().start_.x) + ", " + std::to_string(Grid::instance().start_.y)
		+ ")\n"
	};
	std::string nodes{"\n-- GRAPH NODE ALIASES:\n"};
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
	{
		nodes.append("entity_" + std::to_string(ent.first) + "=" +  std::to_string(ent.first) + "\n");
		temp_vars.emplace_back("entity_" + std::to_string(ent.first));
	}
	file_ << header << plr << map << nodes << "\n\n-- ENTITIES:\n";

	// Save individual entities.
	std::string entity_name{};
	for(const auto& ent : entities_.get_component_list())
	{
		// Do not save nodes and lines!
		if(ent.second.test(GridNodeComponent::type))
			continue;

		entity_name = "entity_" + std::to_string(ent.first);
		temp_vars.push_back(entity_name);
		
		save_entities_.emplace_back(entity_name + " = game.entity.create()");
		for(std::size_t i = 0; i < ent.second.size(); ++i)
		{
			if(ent.second.test(i))
				SAVE_COMPONENT(i, ent.first, entity_name);
		}	
	}
	for(auto& ent : save_entities_)
		file_ << ent << "\n";
	file_ << "\n";
	for(auto& comp : save_components_)
		file_ << comp << "\n";
	file_ << "\n";
	save_tasks();

	file_ << "\n\n-- AUXILIARY VARIABLES TO BE DELETED:\nto_be_deleted = {\n";
	std::size_t count{0}; // Saves vertical space.
	for(const auto& tmp : temp_vars)
	{ // This will allow to delete all those auxiliary variables when loading.
		file_ << "'" << tmp + "', ";
		if(count++ % 10 == 0)
			file_ << "\n";
	}
	file_ << "}";
	file_.flush();
	file_.close();
	save_entities_.clear();
	save_components_.clear();
}

void GameSerializer::load_game(Game& game, const std::string& fname)
{
	// Clean current game.
	entities_.delete_entities();
	entities_.cleanup();

	std::string file_name{"saves/" + fname + ".lua"};
	try
	{
		script_.load(file_name); // Yes, THAT simple!

		// Cleanup.
		script_.execute(
			"for _, v in ipairs(to_be_deleted) do \
				_G[v] = nil \
			 end \
			 to_be_deleted = nil \
			 collectgarbage()"
			);

		game.reset_camera();
	}
	catch(lpp::Exception& ex)
	{
		GUI::instance().get_console().print_text("<FAIL> Could not load from file: " + fname, Console::RED_TEXT);
		GUI::instance().get_console().print_text(ex.what_lua(), Console::RED_TEXT);
	}
}

void GameSerializer::save_tasks()
{
	file_ << "\n-- TASKS: --\n";
	for(auto& task_pair : task_pairs_)
	{
		file_ << "game.add_task(entity_" + std::to_string(task_pair.first) + ", entity_"
			   + std::to_string(task_pair.second) + ")\n";
	}
	task_pairs_.clear();
}
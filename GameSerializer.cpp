#include "GameSerializer.hpp"
#include "Game.hpp"
#include "GUI.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

/**
 * Brief: Macro that serves as a simpler way to use the serializers_ array when calling it's members.
 * Param: Type of the component to be loaded.
 * Param: ID of the entity that loads the component.
 * Param: Name of the table that contains the component data.
 */
#define SAVE_COMPONENT(TYPE, ID, TABLE) (((this)->*serializers_[TYPE])(ID, TABLE))

GameSerializer::GameSerializer(EntitySystem& ents)
	: entities_{ents}, script_{lpp::Script::instance()},
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
	serializers_[ManaComponent::type] = &GameSerializer::save_component<ManaComponent>;
	serializers_[SpellComponent::type] = &GameSerializer::save_component<SpellComponent>;
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
	serializers_[NameComponent::type] = &GameSerializer::save_component<NameComponent>;
	serializers_[ExperienceValueComponent::type] = &GameSerializer::save_component<ExperienceValueComponent>;
	serializers_[LightComponent::type] = &GameSerializer::save_component<LightComponent>;
	serializers_[CommandComponent::type] = &GameSerializer::save_component<CommandComponent>;
	serializers_[CounterComponent::type] = &GameSerializer::save_component<CounterComponent>;
}

void GameSerializer::save_game(Game& game, const std::string& fname)
{
	std::string file_name{"saves/" + fname + ".lua"};
	file_.open(file_name);
	std::vector<std::string> temp_vars{};

	std::string header{
		  "game.gui.log.clear()\nentity_" + std::to_string(Component::NO_ENTITY)
		+ " = " + std::to_string(Component::NO_ENTITY) + "\n"
	};

	auto& player = Player::instance();
	std::string plr{
		  "game.player.nulify_stats()\ngame.player.add_gold(" + std::to_string(player.get_gold())
		+ ")\ngame.player.add_max_mana(" + std::to_string(player.get_max_mana())
		+ ")\ngame.player.add_mana(" + std::to_string(player.get_mana())
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
		for(tdt::uint i = 0; i < ent.second.size(); ++i)
		{
			if(ent.second.test(i) && i < serializers_.size() && serializers_[i])
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

	// Wave system serialization, requires nodes so might be a bit higher,
	// but just in case is left till the end of the save file.
	file_ << save_wave_system(game) << "\n" << save_unlocks();

	file_ << "\n\n-- AUXILIARY VARIABLES TO BE DELETED:\nto_be_deleted = {\n";
	tdt::uint count{0}; // Saves vertical space.
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
	game.reset_unlocks();

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
		file_ << "game.task.add(entity_" + std::to_string(task_pair.first) + ", entity_"
			   + std::to_string(task_pair.second) + ")\n";
	}
	task_pairs_.clear();
}

std::string GameSerializer::save_wave_system(Game& game)
{
	if(!game.wave_system_)
		return "-- NO ENTITY SYSTEM PRESENT!";

	auto& wsys = *game.wave_system_;

	std::string comm{
		  "-- WAVE SYSTEM\ngame.wave.set_table('" + wsys.get_wave_table() + "')\n"
		+ "game.wave.set_state(" + std::to_string((int)wsys.get_state()) + ")\n"
		+ "game.wave.set_wave_count(" + std::to_string(wsys.get_wave_count()) + ")\n"
		+ "game.wave.set_curr_wave_number(" + std::to_string(wsys.get_curr_wave_number()) + ")\n"
		+ "game.wave.set_countdown(" + std::to_string(wsys.get_countdown_value()) + ")\n"
		+ "game.wave.set_spawn_cooldown(" + std::to_string(wsys.get_spawn_cooldown()) + ")\n"
		+ "game.wave.set_spawn_timer(" + std::to_string(wsys.get_spawn_timer()) + ")\n"
		+ "game.wave.set_entities_spawned(" + std::to_string(wsys.get_entities_spawned()) + ")\n"
		+ "game.wave.set_wave_entities(" + std::to_string(wsys.get_wave_entities()) + ")\n"
		+ "game.wave.set_entity_total(" + std::to_string(wsys.get_entity_total()) + ")\n"
	};

	for(const auto& blueprint : wsys.get_entity_blueprints())
		comm.append("game.wave.add_entity_blueprint('" + blueprint + "')\n");

	for(const auto& node : wsys.get_spawning_nodes())
		comm.append("game.wave.add_spawn_node(entity_" + std::to_string(node) + ")\n");
	comm.append("game.wave.update_label_text()\n");

	return comm;
}

std::string GameSerializer::save_unlocks()
{
	std::string comm{};

	for(const auto& spell : GUI::instance().get_spell_casting().get_spells())
		comm.append("game.spell.register_spell('" + spell + "')\n");

	for(const auto& building : GUI::instance().get_builder().get_buildings())
		comm.append("game.gui.builder.register_building('" + building + "')\n");

	auto& research = GUI::instance().get_research();
	const auto& unlocked = research.get_unlocked();
	for(tdt::uint i = 0; i < unlocked.size(); ++i)
	{
		if(!unlocked[i])
			continue;
		comm.append("game.gui.research.dummy_unlock(" + std::to_string(i / research.cols_ + 1) + ", "
					+ std::to_string(i % research.cols_ + 1) + ")\n");
	}

	return comm;
}

#include "WaveSystem.hpp"
#include "Helpers.hpp"

WaveSystem::WaveSystem(EntitySystem& ents)
	: state_{WAVE_STATE::INACTIVE}, entities_{ents}, curr_wave_number_{},
	  wave_count_{}, entities_spawned_{}, entities_total_{}, next_wave_countdown_{180},
	  second_timer_{}, label_text_{"WAVE SYSTEM OFFLINE"}, window_{},
	  script_{lpp::Script::get_singleton()}, spawning_nodes_{}, spawn_timer_{},
	  spawn_cooldown_{}, entity_blueprints_{}, endless_mode_{}
{ /* DUMMY BODY */ }

void WaveSystem::update(tdt::real delta)
{
	switch(state_)
	{
		case WAVE_STATE::ACTIVE:
			if(entities_spawned_ < entities_total_)
			{
				if(spawn_timer_ >= spawn_cooldown_)
				{
					spawn_timer_ = tdt::real{};
					spawn();
					update_label_text();
				}
				else
					spawn_timer_ += delta;
			}
			break;
		case WAVE_STATE::WAITING:
			if(second_timer_ >= 1.f)
			{
				second_timer_ = tdt::real{};
				if(next_wave_countdown_ == 0)
					start_wave();
				else
				{
					--next_wave_countdown_;
					update_label_text();
				}
			}
			else
				second_timer_ += delta;
			break;
		case WAVE_STATE::INACTIVE:
			break;
	}
}

void WaveSystem::set_countdown_window(CEGUI::Window* win)
{
	window_ = win;
	if(window_)
		update_label_text();
}

void WaveSystem::next_wave()
{
	next_wave_countdown_ = tdt::uint{};
}

void WaveSystem::advance_wave_countdown(tdt::uint val)
{
	if(next_wave_countdown_ > val)
		next_wave_countdown_ -= val;
	else
		next_wave_countdown_ = 0;
}

void WaveSystem::wave_entity_died()
{
	if(wave_entities_ <= 1 && entities_spawned_ >= entities_total_)
		end_wave();
	else if(wave_entities_ >= 1)
		--wave_entities_;
	update_label_text();
}

void WaveSystem::start()
{
	script_.call<void>(wave_table_ + ".init");
	state_ = WAVE_STATE::WAITING;
	if(window_)
		window_->setVisible(true);
}

void WaveSystem::pause(bool val)
{
	if(val && state_ == WAVE_STATE::WAITING)
		state_ = WAVE_STATE::INACTIVE;
	else if(!val && state_ == WAVE_STATE::INACTIVE)
		state_ = WAVE_STATE::WAITING;
}

void WaveSystem::set_entity_total(tdt::uint val)
{
	entities_total_ = val;
}

tdt::uint WaveSystem::get_entity_total() const
{
	return entities_total_;
}

void WaveSystem::set_wave_count(tdt::uint val)
{
	wave_count_ = val;
}

tdt::uint WaveSystem::get_wave_count() const
{
	return wave_count_;
}

void WaveSystem::add_spawn_node(tdt::uint id)
{
	spawning_nodes_.emplace_back(id);
}

void WaveSystem::clear_spawn_nodes()
{
	spawning_nodes_.clear();
}

void WaveSystem::set_spawn_cooldown(tdt::real val)
{
	spawn_cooldown_ = val;
}

tdt::real WaveSystem::get_spawn_cooldown() const
{
	return spawn_cooldown_;
}

void WaveSystem::update_label_text()
{
	if(!window_)
		return;

	switch(state_)
	{
		case WAVE_STATE::ACTIVE:
			label_text_ = "WAVE #" + std::to_string(curr_wave_number_ + 1) + ": "
				        + std::to_string(wave_entities_) + " / " + std::to_string(entities_spawned_)
				        + " (" + std::to_string(entities_total_) + ")";
			break;
		case WAVE_STATE::WAITING:
		{
			tdt::uint cdown = next_wave_countdown_;
			tdt::uint seconds = cdown % 60;
			cdown /= 60;
			tdt::uint minutes = cdown % 60;
			cdown /= 60;
			tdt::uint hours = cdown % 60;

			label_text_ = "NEXT WAVE IN: " + std::to_string(hours) + " - "
				        + std::to_string(minutes) + " - " + std::to_string(seconds);
			break;
		}
		case WAVE_STATE::INACTIVE:
			label_text_ = "WAVE SYSTEM OFFLINE";
			break;
	}
	window_->setText(label_text_);
}

void WaveSystem::add_entity_blueprint(const std::string& val)
{
	entity_blueprints_.emplace_back(val);
}

const std::vector<std::string>& WaveSystem::get_entity_blueprints() const
{
	return entity_blueprints_;
}

void WaveSystem::set_wave_table(const std::string& val)
{
	wave_table_ = val;
}

const std::string& WaveSystem::get_wave_table() const
{
	return wave_table_;
}

const std::vector<tdt::uint>& WaveSystem::get_spawning_nodes() const
{
	return spawning_nodes_;
}

void WaveSystem::set_curr_wave_number(tdt::uint val)
{
	curr_wave_number_ = val;
}

tdt::uint WaveSystem::get_curr_wave_number() const
{
	return curr_wave_number_;
}

void WaveSystem::set_countdown_value(tdt::uint val)
{
	next_wave_countdown_ = val;
}

tdt::uint WaveSystem::get_countdown_value() const
{
	return next_wave_countdown_;
}

void WaveSystem::set_state(WAVE_STATE val)
{
	state_ = val;
}

WAVE_STATE WaveSystem::get_state() const
{
	return state_;
}

void WaveSystem::set_spawn_timer(tdt::real val)
{
	spawn_timer_ = val;
}

tdt::real WaveSystem::get_spawn_timer() const
{
	return spawn_timer_;
}

void WaveSystem::set_wave_entities(tdt::uint val)
{
	wave_entities_ = val;
}

tdt::uint WaveSystem::get_wave_entities() const
{
	return wave_entities_;
}

void WaveSystem::set_entities_spawned(tdt::uint val)
{
	entities_spawned_ = val;
}

tdt::uint WaveSystem::get_entities_spawned() const
{
	return entities_spawned_;
}

void WaveSystem::clear_entity_blueprints()
{
	entity_blueprints_.clear();
}

void WaveSystem::set_endless_mode(bool val)
{
	endless_mode_ = val;
}

bool WaveSystem::get_endless_mode() const
{
	return endless_mode_;
}

void WaveSystem::start_wave()
{
	script_.call<void>(wave_table_ + ".wstart_" + std::to_string(curr_wave_number_));
	spawn_timer_ = spawn_cooldown_; // Allows instant spawn of the first batch.
	next_wave_countdown_ = tdt::uint{};
	entities_spawned_ = tdt::uint{};
	wave_entities_ = tdt::uint{};
	state_ = WAVE_STATE::ACTIVE;
	update_label_text();
}

void WaveSystem::end_wave()
{
	script_.call<void>(wave_table_ + ".wend_" + std::to_string(curr_wave_number_));

	if(!endless_mode_)
		++curr_wave_number_;

	if(curr_wave_number_ < wave_count_)
		state_ = WAVE_STATE::WAITING;
	else
		state_ = WAVE_STATE::INACTIVE; // The end.
}

void WaveSystem::spawn()
{
	if(entities_spawned_ >= entities_total_)
		return;

	tdt::uint to_spawn{entities_total_ - entities_spawned_};
	if(spawning_nodes_.size() < to_spawn)
		to_spawn = spawning_nodes_.size();

	for(tdt::uint i = 0; i < to_spawn; ++i)
	{
		tdt::uint id{};
		if(i + entities_spawned_ < entity_blueprints_.size())
			id = entities_.create_entity(entity_blueprints_[i + entities_spawned_]);
		else if(0 < entity_blueprints_.size())
			id = entities_.create_entity(entity_blueprints_[0]);
		else
			return;

		entities_.add_component<DestructorComponent>(id); // It should have it, but just in case.
		auto comp = entities_.get_component<DestructorComponent>(id);
		comp->blueprint = "wave_entity_destructor";

		PhysicsHelper::set_2d_position(entities_, id, PhysicsHelper::get_2d_position(entities_, spawning_nodes_[i]));
	}

	entities_spawned_ += to_spawn;
	wave_entities_ += to_spawn;
	update_label_text();
}

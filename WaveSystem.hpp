#pragma once

#include <CEGUI/CEGUI.h>
#include <string>
#include <vector>
#include "System.hpp"
#include "Typedefs.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"
#include "Enums.hpp"

/**
 *
 * Note: This systems contains a large number of setters/getters (while most of
 *       other systems do not). This is because this system has to be fully serialized
 *       when saving the game to save the game's progress.
 */
class WaveSystem : public System
{
	public:
		/**
		 *
		 */
		WaveSystem(EntitySystem&);
		
		/**
		 *
		 */
		~WaveSystem() = default;

		/**
		 *
		 */
		void update(tdt::real) override;

		/**
		 *
		 */
		void set_countdown_window(CEGUI::Window*);

		/**
		 *
		 */
		void next_wave();

		/**
		 *
		 */
		void advance_wave_countdown(tdt::uint);

		/**
		 *
		 */
		void wave_entity_died();

		/**
		 *
		 */
		void start();

		/**
		 *
		 */
		void pause(bool);

		/**
		 *
		 */
		void set_entity_total(tdt::uint);

		/**
		 *
		 */
		tdt::uint get_entity_total() const;

		/**
		 *
		 */
		void set_wave_count(tdt::uint);

		/**
		 *
		 */
		tdt::uint get_wave_count() const;

		/**
		 *
		 */
		void add_spawn_node(tdt::uint);

		/**
		 *
		 */
		void clear_spawn_nodes();

		/**
		 *
		 */
		void set_spawn_cooldown(tdt::real);

		/**
		 *
		 */
		tdt::real get_spawn_cooldown() const;

		/**
		 *
		 */
		void update_label_text();

		/**
		 *
		 */
		void add_entity_blueprint(const std::string&);

		/**
		 *
		 */
		const std::vector<std::string>& get_entity_blueprints() const;

		/**
		 *
		 */
		void set_wave_table(const std::string&);

		/**
		 *
		 */
		const std::string& get_wave_table() const;

		/**
		 *
		 */
		const std::vector<tdt::uint>& get_spawning_nodes() const;

		/**
		 *
		 */
		void set_curr_wave_number(tdt::uint);

		/**
		 *
		 */
		tdt::uint get_curr_wave_number() const;

		/**
		 *
		 */
		void set_countdown_value(tdt::uint);

		/**
		 *
		 */
		tdt::uint get_countdown_value() const;

		/**
		 *
		 */
		void set_state(WAVE_STATE);

		/**
		 *
		 */
		WAVE_STATE get_state() const;

		/**
		 *
		 */
		void set_spawn_timer(tdt::real);

		/**
		 *
		 */
		tdt::real get_spawn_timer() const;

		/**
		 *
		 */
		void set_wave_entities(tdt::uint);

		/**
		 *
		 */
		tdt::uint get_wave_entities() const;

		/**
		 *
		 */
		void set_entities_spawned(tdt::uint);

		/**
		 *
		 */
		tdt::uint get_entities_spawned() const;

		/**
		 *
		 */
		void clear_entity_blueprints();

		/**
		 *
		 */
		void set_endless_mode(bool);

		/**
		 *
		 */
		bool get_endless_mode() const;

	private:
		/**
		 *
		 */
		void start_wave();

		/**
		 *
		 */
		void end_wave();

		/**
		 *
		 */
		void spawn();

		/**
		 *
		 */
		WAVE_STATE state_;

		/**
		 *
		 */
		EntitySystem& entities_;

		/**
		 *
		 */
		tdt::uint curr_wave_number_;

		/**
		 *
		 */
		tdt::uint wave_count_;

		/**
		 *
		 */
		tdt::uint wave_entities_;

		/**
		 *
		 */
		tdt::uint entities_spawned_;

		/**
		 *
		 */
		tdt::uint entities_total_;

		/**
		 *
		 */
		tdt::uint next_wave_countdown_;

		/**
		 *
		 */
		tdt::real second_timer_;

		/**
		 *
		 */
		std::string label_text_;

		/**
		 *
		 */
		CEGUI::Window* window_;

		/**
		 *
		 */
		lpp::Script& script_;

		/**
		 *
		 */
		std::vector<tdt::uint> spawning_nodes_;

		/**
		 *
		 */
		tdt::real spawn_timer_, spawn_cooldown_;

		/**
		 *
		 */
		std::string wave_table_;

		/**
		 *
		 */
		std::vector<std::string> entity_blueprints_;

		/**
		 *
		 */
		bool endless_mode_;
};
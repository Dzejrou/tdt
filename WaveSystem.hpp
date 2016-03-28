#pragma once

#include <string>
#include <vector>
#include "System.hpp"
#include "Typedefs.hpp"
#include "Enums.hpp"
namespace CEGUI
{
	class Window;
}
namespace lpp
{
	class Script;
}
class EntitySystem;

/**
 * This system creates the entities attacking the player's dungeon in a similar
 * fashion to tower defense games.
 * Note: This systems contains a large number of setters/getters (while most of
 *       other systems do not). This is because this system has to be fully serialized
 *       when saving the game to save the game's progress.
 */
class WaveSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: EntitySystem in which wave entities will be created.
		 */
		WaveSystem(EntitySystem&);
		
		/**
		 * Destructor.
		 */
		~WaveSystem() = default;

		/**
		 * Brief: Updates all necessary timers and checks if a wave
		 *        has arrived and if so, spawns it.
		 * Param: Time since last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Saves pointer to the window that is used to show
		 *        the countdown to the next wave.
		 * Param: The new window.
		 */
		void set_countdown_window(CEGUI::Window*);

		/**
		 * Brief: Finnishes the wave countdown, causing a wave
		 *        to be spawned on the next update call.
		 */
		void next_wave();

		/**
		 * Brief: Advances the countdown by a given amount of time.
		 * Param: Number of seconds to subtract from the countdown.
		 */
		void advance_wave_countdown(tdt::uint);

		/**
		 * Brief: Registers a death of an entity that belongs to the
		 *        current wave (called by it's destructor).
		 */
		void wave_entity_died();

		/**
		 * Brief: Starts (and initializes) the wave system.
		 */
		void start();

		/**
		 * Brief: Changes the state of the system.
		 * Param: If true, the wave countdown gets paused,
		 *        if false, the wave countdown gets resumed.
		 */
		void pause(bool);

		/**
		 * Brief: Sets the total number of entities the wave
		 *        is gonna have.
		 * Param: The new number of entities.
		 */
		void set_entity_total(tdt::uint);

		/**
		 * Brief: Returns the total number of entities the wave
		 *        is gonna have.
		 */
		tdt::uint get_entity_total() const;

		/**
		 * Brief: Sets the number of waves before the system stops.
		 * Param: The new number of waves.
		 */
		void set_wave_count(tdt::uint);

		/**
		 * Brief: Returns the total number of waves the system has.
		 */
		tdt::uint get_wave_count() const;

		/**
		 * Brief: Adds a grid node to the spawn list.
		 * Param: ID of the node.
		 */
		void add_spawn_node(tdt::uint);

		/**
		 * Brief: Removes any registered spawn nodes.
		 */
		void clear_spawn_nodes();

		/**
		 * Brief: Sets the delay between spawns (if # of spawn nodes
		 *        is smaller than # of wave entities).
		 * Param: The new spawn cooldown.
		 */
		void set_spawn_cooldown(tdt::real);

		/**
		 * Brief: Returns the delay between spawns.
		 */
		tdt::real get_spawn_cooldown() const;

		/**
		 * Brief: Updates the countdown window's text.
		 */
		void update_label_text();

		/**
		 * Brief: Adds a blueprint table for a new wave entity.
		 * Param: Name of the blueprint table.
		 */
		void add_entity_blueprint(const std::string&);

		/**
		 * Brief: Returns a vector of all entities in the wave.
		 */
		const std::vector<std::string>& get_entity_blueprints() const;

		/**
		 * Brief: Sets the table this system is using to create waves.
		 * Param: Name of the new wave table.
		 */
		void set_wave_table(const std::string&);

		/**
		 * Brief: Returns the table this system is using to create waves.
		 */
		const std::string& get_wave_table() const;

		/**
		 * Brief: Returns a vector of nodes that are marked as spawners
		 *        for the wave.
		 */
		const std::vector<tdt::uint>& get_spawning_nodes() const;

		/**
		 * Brief: Sets the number of the current wave.
		 * Param: The new wave number.
		 */
		void set_curr_wave_number(tdt::uint);

		/**
		 * Brief: Returns the number of the current wave.
		 */
		tdt::uint get_curr_wave_number() const;

		/**
		 * Brief: Sets the time remaining before the next wave.
		 * Param: The new countdown time value.
		 */
		void set_countdown_value(tdt::uint);

		/**
		 * Brief: Returns the time remaining before the next wave.
		 */
		tdt::uint get_countdown_value() const;

		/**
		 * Brief: Changes the state of the wave system.
		 * Param: The new state.
		 */
		void set_state(WAVE_STATE);

		/**
		 * Brief: Returns the state of the wave system.
		 */
		WAVE_STATE get_state() const;

		/**
		 * Brief: Sets the time on the spawn timer, which causes
		 *        the next spawn batch to appear when it reaches
		 *        the spawn cooldown value.
		 * Param: The new spawn timer value.
		 */
		void set_spawn_timer(tdt::real);

		/**
		 * Brief: Returns the time on the spawn timer, which causes
		 *        the next spawn batch to appear when it reaches
		 *        the spawn cooldown value.
		 */
		tdt::real get_spawn_timer() const;

		/**
		 * Brief: Sets the number of entities the current wave has alive.
		 * Param: The enw number of entities.
		 */
		void set_wave_entities(tdt::uint);

		/**
		 * Brief: Returns the number of entities the current wave has alive.
		 */
		tdt::uint get_wave_entities() const;

		/**
		 * Brief: Sets the number of entities already spawned in this wave.
		 * Param: The new entity count.
		 */
		void set_entities_spawned(tdt::uint);

		/**
		 * Brief: Returns the number of entities already spawned in this wave.
		 */
		tdt::uint get_entities_spawned() const;

		/**
		 * Brief: Clears any entity blueprints that were gonna be used in the next wave.
		 */
		void clear_entity_blueprints();

		/**
		 * Brief: Sets the endless flag (true -> last wave repeats).
		 * Param: If true, endless mode is turned on, otherwise it's turned off.
		 */
		void set_endless_mode(bool);

		/**
		 * Brief: Returns the endless flag (true -> last wave repeats).
		 */
		bool get_endless_mode() const;

	private:
		/**
		 * Brief: Starts the current wave.
		 */
		void start_wave();

		/**
		 * Brief: Ends the current wave.
		 */
		void end_wave();

		/**
		 * Brief: Spawns the next batch of entities.
		 */
		void spawn();

		/**
		 * The current state of the system.
		 */
		WAVE_STATE state_;

		/**
		 * Entity system in which the wave entities will be created.
		 */
		EntitySystem& entities_;

		/**
		 * Number of the current wave.
		 */
		tdt::uint curr_wave_number_;

		/**
		 * Total number of waves.
		 */
		tdt::uint wave_count_;

		/**
		 * Number of entities in the current wave that
		 * are spawned and still alive.
		 */
		tdt::uint wave_entities_;

		/**
		 * Number of entities that were already spawned during
		 * this wave.
		 */
		tdt::uint entities_spawned_;

		/**
		 * Total number of entities in the current wave.
		 */
		tdt::uint entities_total_;

		/**
		 * Time in seconds till the next wave starts.
		 */
		tdt::uint next_wave_countdown_;

		/**
		 * Auxiliary timer that is used to measure seconds.
		 */
		tdt::real second_timer_;

		/**
		 * Text that is displayed in the countdown window.
		 */
		std::string label_text_;

		/**
		 * Pointer to the countdown window.
		 */
		CEGUI::Window* window_;

		/**
		 * Reference to the script engine for easier use.
		 */
		lpp::Script& script_;

		/**
		 * Nodes that are used for entity spawning.
		 */
		std::vector<tdt::uint> spawning_nodes_;

		/**
		 * Timers used for entity spawning.
		 */
		tdt::real spawn_timer_, spawn_cooldown_;

		/**
		 * Name of the table containing init, wstart
		 * and wend functions that define a wave system.
		 */
		std::string wave_table_;

		/**
		 * Entities that are gonna be spawned.
		 */
		std::vector<std::string> entity_blueprints_;

		/**
		 * If true, the current wave keeps repeating.
		 */
		bool endless_mode_;
};
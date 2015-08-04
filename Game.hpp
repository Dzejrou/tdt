#pragma once

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <memory>
#include <vector>

#include "EntitySystem.hpp"
#include "HealthSystem.hpp"
#include "MovementSystem.hpp"
#include "AISystem.hpp"
#include "InputSystem.hpp"
#include "GridSystem.hpp"
#include "TaskSystem.hpp"
#include "lppscript/LppScript.hpp"
#include "Console.hpp"
#include "SelectionBox.hpp"
#include "EntityPlacer.hpp"
#include "EntityCreator.hpp"

enum class GAME_STATE
{
	RUNNING, ENDED, CONSOLE, PAUSED, MENU
};

class Game : public Ogre::FrameListener, public OIS::KeyListener,
			 public OIS::MouseListener, public Ogre::WindowEventListener
{
	public:
		/**
		 * Constructor.
		 */
		Game();

		/**
		 * Destructor.
		 */
		~Game();

		/**
		 * Brief: Starts the game.
		 */
		void run();

		/**
		 * Brief: Updates the game in one frame.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real);

		/**
		 * Brief: Changes the game's state.
		 * Param: The new state.
		 */
		void set_state(GAME_STATE);
	protected:
		/**
		 * Inherited methods (callbacks).
		 * Handle Ogre3D and OIS related stuff.
		 */
		bool frameRenderingQueued(const Ogre::FrameEvent&) override;
		bool keyPressed(const OIS::KeyEvent&) override;
		bool keyReleased(const OIS::KeyEvent&) override;
		bool mouseMoved(const OIS::MouseEvent&) override;
		bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID) override;
		bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID) override;
		void windowResized(Ogre::RenderWindow* rw) override;
		void windowClosed(Ogre::RenderWindow* rw) override;
	private:
		/**
		 * Init methods.
		 */
		void ogre_init();
		void ois_init();
		void level_init();
		void lua_init();
		void cegui_init();

		/**
		 * Current game state.
		 */
		GAME_STATE state_;

		/**
		 * Pointers to Ogre3D objects.
		 */
		std::unique_ptr<Ogre::Root> root_;
		Ogre::SceneManager* scene_mgr_;
		Ogre::RenderWindow* window_;
		Ogre::Camera* main_cam_;
		Ogre::Viewport* main_view_;
		Ogre::Light* main_light_;

		OIS::InputManager* input_;
		OIS::Keyboard* keyboard_;
		OIS::Mouse* mouse_;
		Ogre::Vector3 camera_dir_;

		/**
		 * Unique pointers to systems (sadly all systems require the EntitySystem, which
		 * requires Ogre::SceneManager, so the all have to be instantiated after the ogre_init method
		 * call and thus cannot be references).
		 */
		std::unique_ptr<EntitySystem> entity_system_;
		std::unique_ptr<HealthSystem> health_system_;
		std::unique_ptr<MovementSystem> movement_system_;
		std::unique_ptr<AISystem> ai_system_;
		std::unique_ptr<InputSystem> input_system_;
		std::unique_ptr<GridSystem> grid_system_;
		std::unique_ptr<TaskSystem> task_system_;

		/**
		 * Vector of all systems used for updating the game's logic.
		 */
		std::vector<System*> systems_;

		/**
		 * CEGUI renderer.
		 */
		CEGUI::OgreRenderer* renderer_;

		/**
		 * Brief: Converts an OIS key code to CEGUI key code.
		 * Param: OIS key code.
		 */
		CEGUI::MouseButton ois_to_cegui(OIS::MouseButtonID);

		/**
		 * Ingame console.
		 */
		Console console_;

		/**
		 * Allows to spawn entities with the mouse ingame.
		 */
		std::unique_ptr<EntityPlacer> placer_;

		/**
		 * The game's ground represented by a plane, used for ray intersections.
		 */
		std::unique_ptr<Ogre::Plane> ground_;

		/**
		 * Indicates whether the camera is in a free movement mode.
		 */
		bool camera_free_mode_;

		/**
		 * Backup of the camera position before going to free mode.
		 */
		Ogre::Vector3 camera_position_backup_;

		/**
		 * Backup of the camera orientation before going to free mode.
		 */
		Ogre::Quaternion camera_orientation_backup_;

		/**
		 * Brief: Toggles the free camera movement mode.
		 */
		void toggle_camera_free_mode();

		/**
		 * Brief: Returns a pair consisting of the location of the point where the player
		 *        clicked on the ground plane and a boolean indicating if the click was indeed
		 *        on the ground plane.
		 */
		std::pair<bool, Ogre::Vector3> get_mouse_click_position(const OIS::MouseEvent&) const;

		/**
		 * Selection box used to select multiple entities at once.
		 */
		std::unique_ptr<SelectionBox> selection_box_;

		/**
		 *
		 */
		std::unique_ptr<EntityCreator> entity_creator_;

		/**
		 * These methods are to be used from Lua, note that Lua can register only
		 * static functions, so a static pointer to the instance of this game is created in
		 * the game's constructor and used in these static functions.
		 */
		static Game* lua_this;

		// Core functions.
		static int lua_get_avg_fps(lpp::Script::state);
		static int lua_get_fps(lpp::Script::state);
		static int lua_print(lpp::Script::state);
		static int lua_set_game_state(lpp::Script::state);
		static int lua_toggle_bounding_boxes(lpp::Script::state);
		static int lua_toggle_camera_free_mode(lpp::Script::state);
		static int lua_toggle_entity_creator(lpp::Script::state);
		static int lua_list_selected(lpp::Script::state);
		static int lua_destroy_selected(lpp::Script::state);
		static int lua_list_components_of(lpp::Script::state);
		static int lua_load(lpp::Script::state);
		static int lua_reload_all(lpp::Script::state);

		// Entity system.
		static int lua_create_entity(lpp::Script::state);
		static int lua_destroy_entity(lpp::Script::state);
		static int lua_add_component(lpp::Script::state);
		static int lua_delete_component(lpp::Script::state);
		static int lua_init_graphics_component(lpp::Script::state);
		static int lua_list_entity_tables(lpp::Script::state);
		static int lua_place_entity(lpp::Script::state);
		static int lua_register_entity(lpp::Script::state);

		// Movement system.
		static int lua_move_to(lpp::Script::state);
		static int lua_move(lpp::Script::state);
		static int lua_rotate(lpp::Script::state);
		static int lua_is_moving(lpp::Script::state);
		static int lua_is_solid(lpp::Script::state);
		static int lua_can_move_to(lpp::Script::state);
		static int lua_collide(lpp::Script::state);
		static int lua_get_distance(lpp::Script::state);
		static int lua_get_position(lpp::Script::state);
		static int lua_get_speed_modifier(lpp::Script::state);
		static int lua_set_speed_modifier(lpp::Script::state);
		static int lua_enemy_in_radius(lpp::Script::state);
		static int lua_closest_enemy(lpp::Script::state);
		static int lua_dir_to_closest_enemy(lpp::Script::state);
		static int lua_dir_to_closest_enemy_in_radius(lpp::Script::state);
		static int lua_dir_to_enemy(lpp::Script::state);
		static int lua_get_dir(lpp::Script::state);
		static int lua_get_dir_back(lpp::Script::state);
		static int lua_get_dir_left(lpp::Script::state);
		static int lua_get_dir_right(lpp::Script::state);
		static int lua_get_angle(lpp::Script::state);
		static int lua_get_angle_between(lpp::Script::state);
		static int lua_look_at(lpp::Script::state);

		// Health system.
		static int lua_get_health(lpp::Script::state);
		static int lua_add_health(lpp::Script::state);
		static int lua_sub_health(lpp::Script::state);
		static int lua_heal(lpp::Script::state);
		static int lua_buff(lpp::Script::state);
		static int lua_get_defense(lpp::Script::state);
		static int lua_add_defense(lpp::Script::state);
		static int lua_sub_defense(lpp::Script::state);

		// AI system.
		static int lua_is_friendly(lpp::Script::state);
		static int lua_is_neutral(lpp::Script::state);
		static int lua_is_inanimate(lpp::Script::state);
		static int lua_get_blueprint(lpp::Script::state);
		static int lua_get_state(lpp::Script::state);
		static int lua_get_faction(lpp::Script::state);
		static int lua_set_blueprint(lpp::Script::state);
		static int lua_set_state(lpp::Script::state);
		static int lua_set_faction(lpp::Script::state);

		// Input system.
		static int lua_set_input_handler(lpp::Script::state);
		static int lua_toggle_first_person(lpp::Script::state);

		// Grid system.
		static int lua_add_node(lpp::Script::state);
		static int lua_add_line(lpp::Script::state);
		static int lua_get_node(lpp::Script::state);
		static int lua_get_node_from_position(lpp::Script::state);
		static int lua_create_grid_graphics(lpp::Script::state);
		static int lua_delete_grid_graphics(lpp::Script::state);
		static int lua_toggle_grid_visible(lpp::Script::state);
		static int lua_is_free(lpp::Script::state);
		static int lua_set_free(lpp::Script::state);
		static int lua_set_free_selected(lpp::Script::state);
		static int lua_pathfind(lpp::Script::state);
		static int lua_clear_path_colour(lpp::Script::state);

		// Task system.
		static int lua_add_task(lpp::Script::state);
		static int lua_cancel_task(lpp::Script::state);
		static int lua_create_task(lpp::Script::state);
		static int lua_list_tasks_of(lpp::Script::state);
		static int lua_task_possible(lpp::Script::state);
		static int lua_clear_task_queue(lpp::Script::state);
};
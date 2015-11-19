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
#include "SelectionBox.hpp"
#include "EntityPlacer.hpp"
#include "EntityCreator.hpp"
#include "GameSerializer.hpp"
#include "CombatSystem.hpp"
#include "ProductionSystem.hpp"
#include "Enums.hpp"
#include "LuaInterface.hpp"
#include "TimeSystem.hpp"
#include "EventSystem.hpp"
#include "Grid.hpp"
#include "GUI.hpp"

class Game : public Ogre::FrameListener, public OIS::KeyListener,
			 public OIS::MouseListener, public Ogre::WindowEventListener
{
	friend class GameSerializer;
	friend class LuaInterface;
	friend class GUI;
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
		std::unique_ptr<EntitySystem> entity_system_{nullptr};
		std::unique_ptr<HealthSystem> health_system_{nullptr};
		std::unique_ptr<MovementSystem> movement_system_{nullptr};
		std::unique_ptr<AISystem> ai_system_{nullptr};
		std::unique_ptr<InputSystem> input_system_{nullptr};
		std::unique_ptr<GridSystem> grid_system_{nullptr};
		std::unique_ptr<TaskSystem> task_system_{nullptr};
		std::unique_ptr<CombatSystem> combat_system_{nullptr};
		std::unique_ptr<ProductionSystem> production_system_{nullptr};
		std::unique_ptr<TimeSystem> time_system_{nullptr};
		std::unique_ptr<EventSystem> event_system_{nullptr};

		/**
		 * Used to save the game.
		 */
		std::unique_ptr<GameSerializer> game_serializer_{nullptr};

		/**
		 * Vector of all systems used for updating the game's logic.
		 */
		std::vector<System*> systems_{};

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
		 * A gui window that allows to place entities selected from a menu.
		 * (TODO: Allow to create/modify entities.)
		 */
		std::unique_ptr<EntityCreator> entity_creator_;
};
#include "Game.hpp"

/**
 * Static member initialization.
 */
Game* Game::lua_this{nullptr};

Game::Game()
	: state_{GAME_STATE::RUNNING}, root_{nullptr}, window_{nullptr},
	  scene_mgr_{nullptr}, main_cam_{nullptr}, main_light_{nullptr},
	  main_view_{nullptr}, input_{nullptr}, keyboard_{nullptr}, mouse_{nullptr},
	  camera_dir_{0, 0, 0}, renderer_{nullptr}, console_{}, placer_{nullptr}, ground_{nullptr},
	  camera_free_mode_{false}, camera_position_backup_{0, 0, 0},
	  camera_orientation_backup_{}, selection_box_{}, entity_creator_{nullptr}
{
	ogre_init();
	ois_init();
	cegui_init();
	console_.init();
	windowResized(window_); // Will adjust dimensions for OIS mouse.

	entity_system_.reset(new EntitySystem(*scene_mgr_));
	health_system_.reset(new HealthSystem(*entity_system_));
	movement_system_.reset(new MovementSystem(*entity_system_));
	ai_system_.reset(new AISystem(*entity_system_));
	input_system_.reset(new InputSystem(*entity_system_, *keyboard_, *main_cam_));
	grid_system_.reset(new GridSystem(*entity_system_, *scene_mgr_));
	task_system_.reset(new TaskSystem(*entity_system_, *grid_system_));

	systems_.emplace_back(entity_system_.get());
	systems_.emplace_back(health_system_.get());
	systems_.emplace_back(movement_system_.get());
	systems_.emplace_back(ai_system_.get());
	systems_.emplace_back(input_system_.get());
	systems_.emplace_back(grid_system_.get());
	systems_.emplace_back(task_system_.get());

	selection_box_.reset(new SelectionBox{"MainSelectionBox",
						                  *entity_system_,
						                  *scene_mgr_->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList{}),
						                  *scene_mgr_->createRayQuery(Ogre::Ray{}),
						                  *scene_mgr_});
	placer_.reset(new EntityPlacer{*entity_system_, *scene_mgr_, *grid_system_});
	entity_creator_.reset(new EntityCreator{*placer_, *entity_system_});
	game_serializer_.reset(new GameSerializer{*entity_system_});

	lua_this = this;
	lua_init();
	level_init();
}

Game::~Game()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(window_, this);
	windowClosed(window_);
}

void Game::run()
{
	scene_mgr_->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	root_->startRendering();
}

void Game::update(Ogre::Real delta)
{
	if(camera_free_mode_)
		main_cam_->moveRelative(camera_dir_);

	for(auto& sys : systems_)
		sys->update(delta);
}

void Game::set_state(GAME_STATE state)
{
	state_ = state;
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& event)
{
	keyboard_->capture();
	mouse_->capture();

	update(event.timeSinceLastFrame); // TODO: Test with timeSinceLastFrame from frameStarted method!
	CEGUI::System::getSingleton().injectTimePulse(event.timeSinceLastFrame); // Update CEGUI.

	// TODO:
	// Research hypothesis - processor will assume false on conditionals.
	if(state_ == GAME_STATE::ENDED)
		return false;
	else
		return true;
}

bool Game::keyPressed(const OIS::KeyEvent& event)
{
	// Pass to CEGUI.
	auto& cont = CEGUI::System::getSingleton().getDefaultGUIContext();
	cont.injectKeyDown((CEGUI::Key::Scan)event.key);
	cont.injectChar((CEGUI::Key::Scan)event.text);

	if(console_.is_visible())
	{
		if(event.key == OIS::KC_GRAVE)
			console_.set_visible(false);
		return true;
	}

	switch(event.key)
	{
		case OIS::KC_ESCAPE:
			state_ = GAME_STATE::ENDED;
			return false;
		case OIS::KC_GRAVE:
			console_.set_visible(true);
			break;
		case OIS::KC_0:
		{
			std::string comm{
				"if id then game.destroy_entity(id) end \
                 game.clear_path_colour() \
				 id = game.create_entity('ogre') \
				 task1 = game.create_task(255, game.enum.task_type.go_to) \
				 task2 = game.create_task(15, game.enum.task_type.go_to) \
				 task3 = game.create_task(240, game.enum.task_type.go_to) \
				 task4 = game.create_task(0, game.enum.task_type.go_to) \
				 game.add_task(id, task1) \
                 game.add_task(id, task2) \
                 game.add_task(id, task3) \
                 game.add_task(id, task4)"
			};
			lpp::Script::get_singleton().execute(comm);
			break;
		}
	}

	// Allows for free camera movement during debugging.
	if(camera_free_mode_)
	{
		switch(event.key)
		{
			case OIS::KC_A:
				camera_dir_.x -= 1;
				break;
			case OIS::KC_D:
				camera_dir_.x += 1;
				break;
			case OIS::KC_W:
				camera_dir_.z -= 1;
				break;
			case OIS::KC_S:
				camera_dir_.z += 1;
				break;
			case OIS::KC_SPACE:
				camera_dir_.y += 1;
				break;
			case OIS::KC_LCONTROL:
				camera_dir_.y -= 1;
				break;
		}
	}

	return true;
}

bool Game::keyReleased(const OIS::KeyEvent& event)
{
	// Pass to CEGUI.
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)event.key);

	if(console_.is_visible())
		return true;

	// Allows for free camera movement during debbuging.
	if(camera_free_mode_)
	{
		switch(event.key)
		{
			case OIS::KC_A:
				camera_dir_.x += 1;
				break;
			case OIS::KC_D:
				camera_dir_.x -= 1;
				break;
			case OIS::KC_W:
				camera_dir_.z += 1;
				break;
			case OIS::KC_S:
				camera_dir_.z -= 1;
				break;
			case OIS::KC_SPACE:
				camera_dir_.y -= 1;
				break;
			case OIS::KC_LCONTROL:
				camera_dir_.y += 1;
				break;
		}
	}

	return true;
}

bool Game::mouseMoved(const OIS::MouseEvent& event)
{
	if(event.state.buttonDown(OIS::MB_Right))
	{
		main_cam_->yaw(Ogre::Degree(-.13f * event.state.X.rel));
		main_cam_->pitch(Ogre::Degree(-.13f * event.state.Y.rel));
	}

	// Update CEGUI mouse position. TODO: Do this only if GUI is visible?
	auto& gui_cont = CEGUI::System::getSingleton().getDefaultGUIContext();
	gui_cont.injectMouseMove((float)event.state.X.rel, (float)event.state.Y.rel);
	if(event.state.Z.rel != 0) // Mouse scroll.
		gui_cont.injectMouseWheelChange(event.state.Z.rel / 120.f); // Note: 120.f is a magic number used by MS, might not be
																	//       cross-platform.

	if(placer_->is_visible())
	{
		auto res = get_mouse_click_position(event);
		if(res.first)
			placer_->update_position(res.second);
	}
	else if(selection_box_->is_selecting())
	{
		auto& mouse = gui_cont.getMouseCursor();
		Ogre::Vector2 end{ // Can't use get_mouse_click_position as this is rendered in 2D.
			mouse.getPosition().d_x / (float)event.state.width,
			mouse.getPosition().d_y / (float)event.state.height
		};
		selection_box_->extend_to(end);
	}

	return true;
}

bool Game::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	auto& gui_context = CEGUI::System::getSingleton().getDefaultGUIContext();
	gui_context.injectMouseButtonDown(ois_to_cegui(id));

	if(id == OIS::MB_Left && !console_.is_visible() && !placer_->is_visible()) // TODO: State switch!
	{ // Start selection.
		auto& mouse = gui_context.getMouseCursor();

		Ogre::Vector2 start{
			mouse.getPosition().d_x / (float)event.state.width,
			mouse.getPosition().d_y / (float)event.state.height
		};
		selection_box_->set_starting_point(start);
		selection_box_->clear();
		selection_box_->set_selecting(true);
		//selection_box_->set_corners(start, start);
	}

	if(placer_->is_visible())
	{
		if(id == OIS::MB_Left)
			placer_->place(console_);
		else if(id == OIS::MB_Right)
			placer_->set_visible(false);
	}


	return true;
}

bool Game::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	auto& gui_context = CEGUI::System::getSingleton().getDefaultGUIContext();
	gui_context.injectMouseButtonUp(ois_to_cegui(id));

	if(id == OIS::MB_Left && selection_box_->is_selecting())
	{
		auto& mouse = gui_context.getMouseCursor();
		Ogre::Vector2 end{
			mouse.getPosition().d_x / (float)event.state.width,
			mouse.getPosition().d_y / (float)event.state.height
		};
		selection_box_->execute_selection(end, *main_cam_, keyboard_->isKeyDown(OIS::KC_LSHIFT));
		selection_box_->set_selecting(false);
	}

	return true;
}

void Game::windowResized(Ogre::RenderWindow * window)
{
	if(window != window_) // For the possibility of more windows.
		return;
	std::size_t width, height, depth;
	int left, top;
	window->getMetrics(width, height, depth, left, top);

	// This synchronizes the mouse with the new window size.
	auto& mouse_state = mouse_->getMouseState();
	mouse_state.width = width;
	mouse_state.height = height;
}

void Game::windowClosed(Ogre::RenderWindow * window)
{
	if(window != window_)
		return; // For the possibility of more windows.

	if(input_)
	{ // OIS cleanup.
		input_->destroyInputObject(mouse_);
		input_->destroyInputObject(keyboard_);
		OIS::InputManager::destroyInputSystem(input_);
		mouse_ = nullptr;
		keyboard_ = nullptr;
		input_ = nullptr;
	}
	
	state_ = GAME_STATE::ENDED;
}

void Game::ogre_init()
{
	Ogre::String plugs, res;
#ifdef _DEBUG
	plugs = "plugins_d.cfg";
	res = "resources_d.cfg";
#else
	plugs = "plugins.cfg";
	res = "resources.cfg";
#endif
	root_.reset(new Ogre::Root{plugs});

	Ogre::ConfigFile cf;
	cf.load(res);

	// Load resource settings.
	Ogre::String name, loc_type, group;
	auto selit = cf.getSectionIterator();
	while(selit.hasMoreElements())
	{
		group = selit.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = selit.getNext();
		for(auto& x : *settings)
		{
			loc_type = x.first;
			name = x.second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, loc_type, group);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	if(!(root_->restoreConfig() || root_->showConfigDialog()))
	{   // Configuration read failed, end the game.
		throw std::exception{"[Error] Failed to create or load config file."};
	}
	else
		root_->initialise(false);

	// Window init.
	window_ = root_->createRenderWindow("Dungeon Keeper", 1366, 768, false);
	window_->setVisible(true);

	// Scene init.
	// TODO: Research different types of scene managers!
	scene_mgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
	main_cam_ = scene_mgr_->createCamera("MainCam");
	main_cam_->setPosition(300, 300, 300);
	main_cam_->lookAt(100, 100, 100);
	main_cam_->setNearClipDistance(5);
	main_view_ = window_->addViewport(main_cam_);
	main_cam_->setAspectRatio(Ogre::Real(main_view_->getActualWidth()) /
							  Ogre::Real(main_view_->getActualHeight()));
	main_light_ = scene_mgr_->createLight("MainLight");
	main_light_->setPosition(20, 80, 50);

	Ogre::WindowEventUtilities::addWindowEventListener(window_, this);
	root_->addFrameListener(this);
}

void Game::ois_init()
{
	OIS::ParamList pl;
	std::size_t whnd = 0;
	std::string whnd_str{};

	window_->getCustomAttribute("WINDOW", &whnd);
	whnd_str = std::to_string(whnd);
	pl.insert(std::make_pair(std::string("WINDOW"), whnd_str));

	input_ = OIS::InputManager::createInputSystem(pl);

	keyboard_ = static_cast<OIS::Keyboard*>(input_->createInputObject(OIS::OISKeyboard, true));
	mouse_ = static_cast<OIS::Mouse*>(input_->createInputObject(OIS::OISMouse, true));

	keyboard_->setEventCallback(this);
	mouse_->setEventCallback(this);
}

void Game::level_init()
{
	// Create floor.
	ground_.reset(new Ogre::Plane{Ogre::Vector3::UNIT_Y, 0});
	Ogre::MeshManager::getSingleton().createPlane(
		"ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		*ground_, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z
		);
	Ogre::Entity* ground_entity = scene_mgr_->createEntity("ground");
	ground_entity->setCastShadows(false);
	auto ground_node = scene_mgr_->getRootSceneNode()->createChildSceneNode();
	ground_node->attachObject(ground_entity);
	ground_node->setPosition(750.f, 0.f, 750.f);
	ground_entity->setMaterialName("rocky_ground");
	ground_entity->setQueryFlags(0);

	grid_system_->create_graph(16, 16, 100.f, 0.f, 0.f);
}

void Game::lua_init()
{
	// Register all functions that will be used in Lua.
	lpp::Script& script = lpp::Script::get_singleton();
	lpp::Script::regs game_funcs[] = {
		// Core functions.
		{"get_avg_fps", Game::lua_get_avg_fps},
		{"get_fps", Game::lua_get_fps},
		{"print", Game::lua_print},
		{"set_game_state", Game::lua_set_game_state},
		{"toggle_bounding_boxes", Game::lua_toggle_bounding_boxes},
		{"toggle_camera_free_mode", Game::lua_toggle_camera_free_mode},
		{"toggle_entity_creator", Game::lua_toggle_entity_creator},
		{"list_selected", Game::lua_list_selected},
		{"destroy_selected", Game::lua_destroy_selected},
		{"list_components_of", Game::lua_list_components_of},
		{"load", Game::lua_load},
		{"reload_all", Game::lua_reload_all},
		{"save_game", Game::lua_save_game},
		{"load_game", Game::lua_load_game},

		// Ogre related functions.
		{"set_mesh", Game::lua_set_mesh},
		{"set_material", Game::lua_set_material},
		{"set_visible", Game::lua_set_visible},

		// Entity manipulation.
		{"create_entity", Game::lua_create_entity},
		{"destroy_entity", Game::lua_destroy_entity},
		{"add_component", Game::lua_add_component},
		{"delete_component", Game::lua_delete_component},
		{"init_graphics_component", Game::lua_init_graphics_component},
		{"list_entity_tables", Game::lua_list_entity_tables},
		{"place_entity", Game::lua_place_entity},
		{"register_entity", Game::lua_register_entity},

		// Movement system.
		{"move_to", Game::lua_move_to},
		{"move", Game::lua_move},
		{"rotate", Game::lua_rotate},
		{"is_moving", Game::lua_is_moving},
		{"is_solid", Game::lua_is_solid},
		{"can_move_to", Game::lua_can_move_to},
		{"collide", Game::lua_collide},
		{"get_distance", Game::lua_get_distance},
		{"get_position", Game::lua_get_position},
		{"get_speed", Game::lua_get_speed_modifier},
		{"set_speed", Game::lua_set_speed_modifier},
		{"enemy_in_radius", Game::lua_enemy_in_radius},
		{"closest_enemy", Game::lua_closest_enemy},
		{"dir_to_closest_enemy", Game::lua_dir_to_closest_enemy},
		{"dir_to_closest_enemy_in_radius", Game::lua_dir_to_closest_enemy_in_radius},
		{"dir_to_enemy", Game::lua_dir_to_enemy},
		{"get_dir", Game::lua_get_dir},
		{"get_dir_back", Game::lua_get_dir_back},
		{"get_dir_left", Game::lua_get_dir_left},
		{"get_dir_right", Game::lua_get_dir_right},
		{"get_angle", Game::lua_get_angle},
		{"get_angle_between", Game::lua_get_angle_between},
		{"look_at", Game::lua_look_at},
		{"set_solid", Game::lua_set_solid},
		{"set_half_height", Game::lua_set_half_height},

		// Health system.
		{"get_health", Game::lua_get_health},
		{"add_health", Game::lua_add_health},
		{"sub_health", Game::lua_sub_health},
		{"heal", Game::lua_heal},
		{"buff", Game::lua_buff},
		{"get_defense", Game::lua_get_defense},
		{"add_defense", Game::lua_add_defense},
		{"sub_defense", Game::lua_sub_defense},
		{"set_regen", Game::lua_set_regen},
		{"set_alive", Game::lua_set_alive},

		// AI system.
		{"is_friendly", Game::lua_is_friendly},
		{"is_neutral", Game::lua_is_neutral},
		{"is_inanimate", Game::lua_is_inanimate},
		{"get_blueprint", Game::lua_get_blueprint},
		{"get_state", Game::lua_get_state},
		{"get_faction", Game::lua_get_faction},
		{"set_blueprint", Game::lua_set_blueprint},
		{"set_state", Game::lua_set_state},
		{"set_faction", Game::lua_set_faction},

		// Input system.
		{"set_input_handler", Game::lua_set_input_handler},
		{"toggle_first_person", Game::lua_toggle_first_person},

		// Grid system.
		{"add_node", Game::lua_add_node},
		{"add_line", Game::lua_add_line},
		{"get_node", Game::lua_get_node},
		{"get_node_from_position", Game::lua_get_node_from_position},
		{"create_grid_graphics", Game::lua_create_grid_graphics},
		{"delete_grid_graphics", Game::lua_delete_grid_graphics},
		{"toggle_grid_visible", Game::lua_toggle_grid_visible},
		{"is_free", Game::lua_is_free},
		{"set_free", Game::lua_set_free},
		{"set_free_selected", Game::lua_set_free_selected},
		{"pathfind", Game::lua_pathfind},
		{"clear_path_colour", Game::lua_clear_path_colour},
		{"set_pathfinding_blueprint", Game::lua_set_pathfinding_blueprint},
		{"create_graph", Game::lua_create_graph},

		// Task system.
		{"add_task", Game::lua_add_task},
		{"cancel_task", Game::lua_cancel_task},
		{"create_task", Game::lua_create_task},
		{"list_tasks_of", Game::lua_list_tasks_of},
		{"task_possible", Game::lua_task_possible},
		{"clear_task_queue", Game::lua_clear_task_queue},
		{"set_task_source", Game::lua_set_task_source},
		{"set_task_target", Game::lua_set_task_target},
		{"set_task_type", Game::lua_set_task_type},
		{"add_possible_task", Game::lua_add_possible_task},
		{"delete_possible_task", Game::lua_delete_possible_task},

		// Ending sentinel (required by Lua).
		{nullptr, nullptr}
	};
	luaL_newlib(script.get_state(), game_funcs);
	lua_setglobal(script.get_state(), "game");

	// Load all necessary scripts.
	script.load("scripts/core_utils.lua");
	script.load("scripts/ogre.lua");
	script.load("scripts/basic_wall.lua");

	// InputComponent related enums.
	script.set("game.enum.input.key_up", OIS::KC_W);
	script.set("game.enum.input.key_down", OIS::KC_S);
	script.set("game.enum.input.key_left", OIS::KC_A);
	script.set("game.enum.input.key_right", OIS::KC_D);
}

void Game::cegui_init()
{
	renderer_ = &CEGUI::OgreRenderer::bootstrapSystem(*window_);
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getDefaultImage());

	// Button test.
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* sheet = wmgr.createWindow("DefaultWindow", "TestWindow/Sheet");
	CEGUI::Window* quit = wmgr.createWindow("AlfiskoSkin/Button", "TestWindow/QuitButton");
	quit->setText("Q U I T");
	quit->setSize(CEGUI::USize(CEGUI::UDim(0.15f, 0.f), CEGUI::UDim(0.05f, 0.f)));
	sheet->addChild(quit);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
	quit->subscribeEvent(CEGUI::PushButton::EventClicked, [&](){ this->set_state(GAME_STATE::ENDED); });
}

CEGUI::MouseButton Game::ois_to_cegui(OIS::MouseButtonID id)
{
	switch(id)
	{
		case OIS::MB_Left:
			return CEGUI::LeftButton;
		case OIS::MB_Right:
			return CEGUI::RightButton;
		case OIS::MB_Middle:
			return CEGUI::MiddleButton;
		default:
			return CEGUI::LeftButton;
	}
}

void Game::toggle_camera_free_mode()
{
	if(camera_free_mode_)
	{
		camera_free_mode_ = false;
		main_cam_->setPosition(camera_position_backup_);
		main_cam_->setOrientation(camera_orientation_backup_);
	}
	else
	{
		camera_free_mode_ = true;
		camera_position_backup_ = main_cam_->getPosition();
		camera_orientation_backup_ = main_cam_->getOrientation();
	}
}

std::pair<bool, Ogre::Vector3> Game::get_mouse_click_position(const OIS::MouseEvent& event) const
{
	auto& mouse = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor();
	float screen_x = mouse.getPosition().d_x / (float)event.state.width;
	float screen_y = mouse.getPosition().d_y / (float)event.state.height;
	Ogre::Ray ray = main_cam_->getCameraToViewportRay(screen_x, screen_y);

	auto res = ray.intersects(*ground_);
	auto pos = ray.getPoint(res.second);

	return std::make_pair(res.first, pos);
}

/**
 * Note: Function definitions below act as an interface between C++ and Lua, they all have
 *		 to have the signature int fname(lpp::Script::state) and return the number of results
 *       pushed onto the Lua stack (Lua allows to return multiple results if needed).
 * Important: These functions will have their arguments on the stack in REVERSED ORDER!
 *            (Because, you know, it's a stack...)
 */
#pragma region LUA
int Game::lua_get_avg_fps(lpp::Script::state L)
{
	auto res = lua_this->window_->getAverageFPS();
	lua_pushnumber(L, res);
	return 1;
}
int Game::lua_get_fps(lpp::Script::state L)
{
	auto res = lua_this->window_->getLastFPS();
	lua_pushnumber(L, res);
	return 1;
}

int Game::lua_print(lpp::Script::state L)
{
	std::string msg = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lua_this->console_.print_text(msg, Console::ORANGE_TEXT);
	return 0;
}

int Game::lua_set_game_state(lpp::Script::state L)
{
	GAME_STATE state = (GAME_STATE)luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	lua_this->set_state(state);
	return 0;
}

int Game::lua_toggle_bounding_boxes(lpp::Script::state)
{
	lua_this->scene_mgr_->showBoundingBoxes(!lua_this->scene_mgr_->getShowBoundingBoxes());
	return 0;
}

int Game::lua_toggle_camera_free_mode(lpp::Script::state)
{
	lua_this->toggle_camera_free_mode();
	return 0;
}

int Game::lua_toggle_entity_creator(lpp::Script::state L)
{
	lua_this->entity_creator_->set_visible(!lua_this->entity_creator_->is_visible());
	return 0;
}

int Game::lua_list_selected(lpp::Script::state)
{
	auto& to_be_destroyed = lua_this->selection_box_->get_selected_entities();
	for(auto& ent : to_be_destroyed)
	{
		lua_this->console_.print_text(std::to_string(ent), Console::ORANGE_TEXT);
	}

	return 0;
}

int Game::lua_destroy_selected(lpp::Script::state)
{
	auto& to_be_destroyed = lua_this->selection_box_->get_selected_entities();
	for(auto& ent : to_be_destroyed)
	{
		lua_this->entity_system_->destroy_entity(ent);
	}
	lua_this->selection_box_->clear_selected_entities();

	return 0;
}

int Game::lua_list_components_of(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::string report{};
	auto& ent = lua_this->entity_system_->get_component_list().find(id);
	if(ent != lua_this->entity_system_->get_component_list().end())
	{
		for(std::size_t i = 0; i < ent->second.size(); ++i)
		{
			if(ent->second.test(i))
				report.append(std::to_string(i) + ", ");
		}
	}

	lua_this->console_.print_text(report, Console::ORANGE_TEXT);
	return 0;
}

int Game::lua_load(lpp::Script::state L)
{
	std::string script = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lpp::Script::get_singleton().load(script);
	return 0;
}

int Game::lua_reload_all(lpp::Script::state L)
{
	lpp::Script::get_singleton().reload_all_scripts();
	return 0;
}

int Game::lua_save_game(lpp::Script::state L)
{
	if(lua_gettop(L) > 0)
	{
		std::string fname = luaL_checkstring(L, -1);
		lua_pop(L, 1);
		lua_this->game_serializer_->save_game(*lua_this, fname);
	}
	else
		lua_this->game_serializer_->save_game(*lua_this);

	return 0;
}

int Game::lua_load_game(lpp::Script::state L)
{
	if(lua_gettop(L) > 0)
	{
		std::string fname = luaL_checkstring(L, -1);
		lua_pop(L, 1);
		lua_this->game_serializer_->load_game(*lua_this, fname);
	}
	else
		lua_this->game_serializer_->load_game(*lua_this);

	return 0;
}

int Game::lua_set_mesh(lpp::Script::state L)
{
	std::string mesh = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	if(lua_this->entity_system_->has_component<GraphicsComponent>(id))
		lua_this->entity_system_->get_component<GraphicsComponent>(id).mesh = mesh;
	return 0;
}

int Game::lua_set_material(lpp::Script::state L)
{
	std::string mat = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	if(lua_this->entity_system_->has_component<GraphicsComponent>(id))
		lua_this->entity_system_->get_component<GraphicsComponent>(id).material = mat;
	return 0;
}

int Game::lua_set_visible(lpp::Script::state L)
{
	bool vis = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	if(lua_this->entity_system_->has_component<GraphicsComponent>(id))
		lua_this->entity_system_->get_component<GraphicsComponent>(id).node->setVisible(vis);
	return 0;
}

int Game::lua_create_entity(lpp::Script::state L)
{
	std::string table_name{""};
	if(lua_gettop(L) >= 1)
	{
		table_name = luaL_checkstring(L, 1);
		lua_pop(L, 1);
	}

	std::size_t id = lua_this->entity_system_->create_entity(table_name);
	lua_pushinteger(L, id); // Return the new id.
	return 1;
}

int Game::lua_destroy_entity(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->entity_system_->destroy_entity(id);
	return 0;
}

int Game::lua_add_component(lpp::Script::state L)
{
	int comp = (int)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->entity_system_->add_component(id, comp);
	return 0;
}

int Game::lua_delete_component(lpp::Script::state L)
{
	int comp = (int)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->entity_system_->delete_component(id, comp);
	return 0;
}

int Game::lua_init_graphics_component(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->entity_system_->init_graphics_component(id);
	return 0;
}

int Game::lua_list_entity_tables(lpp::Script::state L)
{
	auto& ents = lua_this->entity_system_->get_registered_entities();

	if(!ents.empty())
	{
		for(const auto& ent : ents)
			lua_this->console_.print_text(ent, Console::ORANGE_TEXT);
	}
	else
		lua_this->console_.print_text("NO REGISTERED ENTITY TABLES.", Console::ORANGE_TEXT);
	return 0;
}

int Game::lua_place_entity(lpp::Script::state L)
{
	std::string table_name = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lua_this->placer_->set_current_entity_table(table_name);
	lua_this->placer_->set_visible(true);
	return 0;
}

int Game::lua_register_entity(lpp::Script::state L)
{
	std::string table_name = luaL_checkstring(L, -1);
	lua_pop(L, 1);

	lua_this->entity_system_->register_entity(table_name);
	return 0;
}

int Game::lua_move_to(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	lua_this->movement_system_->move_to(id, Ogre::Vector3{x, y, z});
	return 0;
}

int Game::lua_move(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	bool res = lua_this->movement_system_->move(id, Ogre::Vector3{x, y, z});
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_rotate(lpp::Script::state L)
{
	Ogre::Real delta = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->rotate(id, delta);
	return 0;
}

int Game::lua_is_moving(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->movement_system_->is_moving(id);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_is_solid(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->movement_system_->is_solid(id);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_can_move_to(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	bool res = lua_this->movement_system_->can_move_to(id, Ogre::Vector3{x, y, z});
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_collide(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	bool res = lua_this->movement_system_->collide(id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_get_distance(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	Ogre::Real res = lua_this->movement_system_->get_distance(id1, id2);
	lua_pushnumber(L, res);
	return 1;
}

int Game::lua_get_position(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	Ogre::Vector3 res = lua_this->movement_system_->get_position(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_get_speed_modifier(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	Ogre::Real res = lua_this->movement_system_->get_speed_modifier(id);
	lua_pushnumber(L, res);
	return 1;
}

int Game::lua_set_speed_modifier(lpp::Script::state L)
{
	Ogre::Real speed = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->set_speed_modifier(id, speed);
	return 0;
}

int Game::lua_enemy_in_radius(lpp::Script::state L)
{
	Ogre::Real radius = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	std::size_t res = lua_this->movement_system_->enemy_in_radius(id, radius);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_closest_enemy(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t res = lua_this->movement_system_->closest_enemy(id);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_dir_to_closest_enemy(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->dir_to_closest_enemy(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_dir_to_closest_enemy_in_radius(lpp::Script::state L)
{
	Ogre::Real radius = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto res = lua_this->movement_system_->dir_to_closest_enemy(id, radius);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_dir_to_enemy(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	auto res = lua_this->movement_system_->dir_to_enemy(id1, id2);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_get_dir(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_get_dir_back(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir_back(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_get_dir_left(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir_left(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_get_dir_right(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	auto res = lua_this->movement_system_->get_dir_right(id);
	lua_pushnumber(L, res.x);
	lua_pushnumber(L, res.y);
	lua_pushnumber(L, res.z);
	return 3;
}

int Game::lua_get_angle(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -4);
	lua_pop(L, 4);

	auto dir = lua_this->movement_system_->get_dir(id);
	auto res = lua_this->movement_system_->get_angle(dir, Ogre::Vector3{x, y, z});
	lua_pushnumber(L, res);
	return 1;
}

int Game::lua_get_angle_between(lpp::Script::state L)
{
	Ogre::Real z2 = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y2 = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x2 = (Ogre::Real)luaL_checknumber(L, -3);
	Ogre::Real z1 = (Ogre::Real)luaL_checknumber(L, -4);
	Ogre::Real y1 = (Ogre::Real)luaL_checknumber(L, -5);
	Ogre::Real x1 = (Ogre::Real)luaL_checknumber(L, -6);
	lua_pop(L, 6);

	auto res = lua_this->movement_system_->get_angle(Ogre::Vector3{x1, y1, z1}, Ogre::Vector3{x2, y2, z2});
	lua_pushnumber(L, res);
	return 3;
}

int Game::lua_look_at(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->look_at(id1, id2);
	return 0;
}

int Game::lua_set_solid(lpp::Script::state L)
{
	bool solid = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->set_solid(id, solid);
	return 0;
}

int Game::lua_set_half_height(lpp::Script::state L)
{
	Ogre::Real hh = (Ogre::Real)luaL_checknumber(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->movement_system_->set_half_height(id, hh);
	return 0;
}

int Game::lua_get_health(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t res = lua_this->health_system_->get_health(id);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_add_health(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->add_health(id, val);
	return 0;
}

int Game::lua_sub_health(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->sub_health(id, val);
	return 0;
}

int Game::lua_heal(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 2);

	lua_this->health_system_->heal(id);
	return 0;
}

int Game::lua_buff(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->buff(id, val);
	return 0;
}

int Game::lua_get_defense(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::size_t res = (std::size_t)lua_this->health_system_->get_defense(id);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_add_defense(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->add_defense(id, val);
	return 0;
}

int Game::lua_sub_defense(lpp::Script::state L)
{
	std::size_t val = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->sub_defense(id, val);
	return 0;
}

int Game::lua_set_regen(lpp::Script::state L)
{
	std::size_t regen = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->set_regen(id, regen);
	return 0;
}

int Game::lua_set_alive(lpp::Script::state L)
{
	bool alive = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->health_system_->set_alive(id, alive);
	return 0;
}

int Game::lua_is_friendly(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	bool res = lua_this->ai_system_->is_friendly(id1, id2);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_is_neutral(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->ai_system_->is_neutral(id);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_is_inanimate(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->ai_system_->is_inanimate(id);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_get_blueprint(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	std::string res = lua_this->ai_system_->get_blueprint(id);
	lua_pushstring(L, res.c_str());
	return 1;
}

int Game::lua_get_state(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	int res = (int)lua_this->ai_system_->get_state(id);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_get_faction(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	int res = (int)lua_this->ai_system_->get_faction(id);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_set_blueprint(lpp::Script::state L)
{
	std::string blueprint = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->ai_system_->set_blueprint(id, blueprint);
	return 0;
}

int Game::lua_set_state(lpp::Script::state L)
{
	ENTITY_STATE state = (ENTITY_STATE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->ai_system_->set_state(id, state);
	return 0;
}

int Game::lua_set_faction(lpp::Script::state L)
{
	FACTION faction = (FACTION)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->ai_system_->set_faction(id, faction);
	return 0;
}

int Game::lua_set_input_handler(lpp::Script::state L)
{
	std::string handler = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->input_system_->set_input_handler(id, handler);
	return 0;
}

int Game::lua_toggle_first_person(lpp::Script::state L)
{
	std::size_t id{Component::NO_ENTITY};
	if(lua_gettop(L) >= 1) // Allow for easy exit.
	{
		id = (std::size_t)luaL_checkinteger(L, -1);
		lua_pop(L, 1);
	}

	lua_this->input_system_->set_first_person(!lua_this->input_system_->is_first_person(), id);
	return 0;
}

int Game::lua_add_node(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real y = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -3);
	lua_pop(L, 3);

	std::size_t res = lua_this->grid_system_->add_node(x, y, z);
	lua_pushnumber(L, res);
	return 1;
}

int Game::lua_add_line(lpp::Script::state L)
{
	std::size_t id2 = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id1 = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	std::size_t res = lua_this->grid_system_->add_line(id1, id2);
	lua_pushnumber(L, res);
	return 1;
}

int Game::lua_get_node(lpp::Script::state L)
{
	std::size_t y = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t x = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	std::size_t res = lua_this->grid_system_->get_node(x, y);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_get_node_from_position(lpp::Script::state L)
{
	Ogre::Real z = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real x = (Ogre::Real)luaL_checknumber(L, -2);
	lua_pop(L, 2);

	std::size_t res = lua_this->grid_system_->get_node_from_position(x, z);
	lua_pushinteger(L, res);
	return 1;
}

int Game::lua_create_grid_graphics(lpp::Script::state L)
{
	lua_this->grid_system_->create_graphics();
	return 0;
}

int Game::lua_delete_grid_graphics(lpp::Script::state L)
{
	lua_this->grid_system_->delete_graphics();
	return 0;
}

int Game::lua_toggle_grid_visible(lpp::Script::state)
{
	lua_this->grid_system_->set_visible(!lua_this->grid_system_->is_visible());
	return 0;
}

int Game::lua_is_free(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	bool res = lua_this->grid_system_->is_free(id);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_set_free(lpp::Script::state L)
{
	bool free = lua_toboolean(L, -1) == 1;
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->set_free(id, free);
	return 0;
}

int Game::lua_set_free_selected(lpp::Script::state L)
{
	bool free = lua_toboolean(L, -1) == 1;
	lua_pop(L, 1);

	lua_this->grid_system_->set_free_selected(*lua_this->selection_box_, free);
	return 0;
}

int Game::lua_pathfind(lpp::Script::state L)
{
	std::size_t end = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t start = (std::size_t)luaL_checkinteger(L, -2);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -3);
	lua_pop(L, 3);

	bool res = lua_this->grid_system_->perform_a_star(id, start, end);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_clear_path_colour(lpp::Script::state L)
{
	lua_this->grid_system_->clear_path_colour();
	return 0;
}

int Game::lua_set_pathfinding_blueprint(lpp::Script::state L)
{
	std::string blueprint = luaL_checkstring(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->grid_system_->set_pathfinding_blueprint(id, blueprint);
	return 0;
}

int Game::lua_create_graph(lpp::Script::state L)
{
	Ogre::Real start_y = (Ogre::Real)luaL_checknumber(L, -1);
	Ogre::Real start_x = (Ogre::Real)luaL_checknumber(L, -2);
	Ogre::Real dist = (Ogre::Real)luaL_checknumber(L, -3);
	std::size_t height = (std::size_t)luaL_checkinteger(L, -4);
	std::size_t width = (std::size_t)luaL_checkinteger(L, -5);
	lua_pop(L, 5);

	lua_this->grid_system_->create_graph(width, height, dist,
										 start_x, start_y);
	return 0;
}

int Game::lua_add_task(lpp::Script::state L)
{
	std::size_t task_id = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t ent_id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->add_task(ent_id, task_id);
	return 0;
}

int Game::lua_cancel_task(lpp::Script::state L)
{
	std::size_t task_id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->task_system_->cancel_task(task_id);
	return 0;
}

int Game::lua_create_task(lpp::Script::state L)
{
	TASK_TYPE task = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t target = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	std::size_t id = lua_this->task_system_->create_task(target, task);
	lua_pushinteger(L, id);
	return 1;
}

int Game::lua_list_tasks_of(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	
	if(lua_this->entity_system_->has_component<TaskHandlerComponent>(id))
	{
		std::string report{};
		auto& task_queue = lua_this->entity_system_->get_component<TaskHandlerComponent>(id).task_queue;

		for(auto& task : task_queue)
		{
			report.append(std::to_string(task) + ": ");
			if(lua_this->entity_system_->has_component<TaskComponent>(task))
			{
				auto& task_comp = lua_this->entity_system_->get_component<TaskComponent>(task);
				report.append(lua_this->task_system_->get_task_name(task_comp.task_type)
							  + " (" + std::to_string(task_comp.source)
							  + " -> " + std::to_string(task_comp.target) + ").\n");
			}
			else
				report.append(lua_this->task_system_->get_task_name(TASK_TYPE::NONE));
		}
		lua_this->console_.print_text(report, Console::ORANGE_TEXT);
	}
	else
		lua_this->console_.print_text("<FAIL> GIVEN ENTITY HAS NO TASKS.", Console::RED_TEXT);

	return 0;
}

int Game::lua_task_possible(lpp::Script::state L)
{
	std::size_t task_id = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t ent_id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	bool res = lua_this->task_system_->task_possible(ent_id, task_id);
	lua_pushboolean(L, res);
	return 1;
}

int Game::lua_clear_task_queue(lpp::Script::state L)
{
	std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
	lua_pop(L, 1);

	lua_this->task_system_->clear_task_queue(id);
	return 0;
}

int Game::lua_set_task_source(lpp::Script::state L)
{
	std::size_t source = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->set_task_source(id, source);
	return 0;
}

int Game::lua_set_task_target(lpp::Script::state L)
{
	std::size_t target = (std::size_t)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->set_task_target(id, target);
	return 0;
}

int Game::lua_set_task_type(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->set_task_type(id, type);
	return 0;
}

int Game::lua_add_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->add_possible_task(id, type);
	return 0;
}
int Game::lua_delete_possible_task(lpp::Script::state L)
{
	TASK_TYPE type = (TASK_TYPE)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->task_system_->delete_possible_task(id, type);
	return 0;
}
#pragma endregion
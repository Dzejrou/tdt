#include "Game.hpp"

Game* Game::lua_this{nullptr};

Game::Game()
	: state_{GAME_STATE::RUNNING}, root_{nullptr}, window_{nullptr},
	  scene_mgr_{nullptr}, main_cam_{nullptr}, main_light_{nullptr},
	  main_view_{nullptr}, input_{nullptr}, keyboard_{nullptr}, mouse_{nullptr},
	  camera_dir_{0, 0, 0}, renderer_{nullptr}, console_{}, lmb_down_{false}, rmb_down_{false}
{
	ogre_init();
	ois_init();
	level_init();
	cegui_init();
	console_.init();

	entity_system_.reset(new EntitySystem(*scene_mgr_));
	health_system_.reset(new HealthSystem(*entity_system_));
	movement_system_.reset(new MovementSystem(*entity_system_));
	ai_system_.reset(new AISystem(*entity_system_));
	input_system_.reset(new InputSystem(*entity_system_, *keyboard_, *main_cam_));

	systems_.emplace_back(health_system_.get());
	systems_.emplace_back(movement_system_.get());
	systems_.emplace_back(ai_system_.get());
	systems_.emplace_back(input_system_.get());

	lua_this = this;
	lua_init();
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
	if(!keyboard_->isKeyDown(OIS::KC_C))
	{
		main_cam_->moveRelative(camera_dir_);
	}

	health_system_->update_regen();
	// TODO: Possibly revert the update system to improve caching? Check std::map memory repr.
	for(auto& ent : entity_system_->get_component_list())
	{
		for(auto& system : systems_)
		{
			if(system->is_valid(ent.first))
				system->update(ent.first, delta);
		}
	}
	entity_system_->cleanup();
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
		if(event.key == OIS::KC_TAB)
			console_.set_visible(false);
		return true;
	}

	switch(event.key)
	{
		case OIS::KC_ESCAPE:
			state_ = GAME_STATE::ENDED;
			return false;
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
		case OIS::KC_TAB:
			console_.set_visible(true);
			break;
	}

	return true;
}

bool Game::keyReleased(const OIS::KeyEvent& event)
{
	// Pass to CEGUI.
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)event.key);

	if(console_.is_visible())
		return true;

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

	return true;
}

bool Game::mouseMoved(const OIS::MouseEvent& event)
{
	if(event.state.buttonDown(OIS::MB_Left))
	{
		main_cam_->yaw(Ogre::Degree(-.13f * event.state.X.rel));
		main_cam_->pitch(Ogre::Degree(-.13f * event.state.Y.rel));
	}
	else if(event.state.buttonDown(OIS::MB_Right))
	{
		main_cam_->yaw(Ogre::Degree(.13f * event.state.X.rel));
		main_cam_->pitch(Ogre::Degree(.13f * event.state.Y.rel));
	}

	// Update CEGUI mouse position. TODO: Do this only if GUI is visible?
	auto& cont = CEGUI::System::getSingleton().getDefaultGUIContext();
	cont.injectMouseMove(event.state.X.rel, event.state.Y.rel);
	if(event.state.Z.rel != 0) // Mouse scroll.
		cont.injectMouseWheelChange(event.state.Z.rel / 120.f); // Note: 120.f is a magic number used by MS, might not be
																//       cross-platform.

	return true;
}

bool Game::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(ois_to_cegui(id));
	return true;
}

bool Game::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(ois_to_cegui(id));
	return true;
}

void Game::windowResized(Ogre::RenderWindow * window)
{
	// TODO: Ask about the necessity of this.
	if(window != window_)
		return; // For the possibility of more windows.

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
	window_ = root_->createRenderWindow("Dungeon Keeper", 800, 600, false);
	window_->setVisible(true);

	// Scene init.
	// TODO: Research different types of scene managers!
	scene_mgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
	main_cam_ = scene_mgr_->createCamera("MainCam");
	main_cam_->lookAt(0, 0, 0);
	main_cam_->setPosition(0, 75, 75);
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
	Ogre::Plane ground{Ogre::Vector3::UNIT_Y, 0};
	Ogre::MeshManager::getSingleton().createPlane(
		"ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		ground, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z
		);
	Ogre::Entity* ground_entity = scene_mgr_->createEntity("ground");
	ground_entity->setCastShadows(false);
	scene_mgr_->getRootSceneNode()->createChildSceneNode()->attachObject(ground_entity);
	ground_entity->setMaterialName("rocky_ground");
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

		// Entity manipulation.
		{"create_entity", Game::lua_create_entity},
		{"destroy_entity", Game::lua_destroy_entity},
		{"add_component", Game::lua_add_component},
		{"delete_component", Game::lua_delete_component},

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

		// Health system.
		{"get_health", Game::lua_get_health},
		{"add_health", Game::lua_add_health},
		{"sub_health", Game::lua_sub_health},
		{"heal", Game::lua_heal},
		{"buff", Game::lua_buff},
		{"get_defense", Game::lua_get_defense},
		{"add_defense", Game::lua_add_defense},
		{"sub_defense", Game::lua_sub_defense},

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

		// Ending sentinel (required by Lua).
		{nullptr, nullptr}
	};
	luaL_newlib(script.get_state(), game_funcs);
	lua_setglobal(script.get_state(), "game");

	// Load all necessary scripts.
	script.load("scripts/core_utils.lua");
	script.load("scripts/ogre.lua");

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

	lua_this->console_.print_text(msg, CEGUI::Colour{1.f, 0.5f, 0.1f});
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

int Game::lua_create_entity(lpp::Script::state L)
{
	std::string table_name = luaL_checkstring(L, 1);
	lua_pop(L, 1);

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
	EntityState state = (EntityState)luaL_checkinteger(L, -1);
	std::size_t id = (std::size_t)luaL_checkinteger(L, -2);
	lua_pop(L, 2);

	lua_this->ai_system_->set_state(id, state);
	return 0;
}

int Game::lua_set_faction(lpp::Script::state L)
{
	Faction faction = (Faction)luaL_checkinteger(L, -1);
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
	std::size_t id{0};
	if(lua_gettop(L) >= 1) // Allow for easy exit.
	{
		std::size_t id = (std::size_t)luaL_checkinteger(L, -1);
		lua_pop(L, 1);
	}

	lua_this->input_system_->set_first_person(!lua_this->input_system_->is_first_person(), id);
	return 0;
}
#pragma endregion
#include "Game.hpp"

Game::Game() // TODO: Init systems.
	: state_{GAME_STATE::INTRO_MENU}, root_{nullptr}, window_{nullptr},
	  scene_mgr_{nullptr}, main_cam_{nullptr}, main_light_{nullptr},
	  main_view_{nullptr}, input_{nullptr}, keyboard_{nullptr}, mouse_{nullptr},
	  camera_dir_{0, 0, 0}, renderer_{nullptr}, placer_{nullptr}, ground_{nullptr},
	  camera_free_mode_{false}, camera_position_backup_{0, 0, 0},
	  camera_orientation_backup_{}, selection_box_{}, entity_creator_{nullptr},
      mouse_position_{0.f, 0.f}, level_generator_{nullptr}
{
	ogre_init();
	ois_init();
	cegui_init();
	windowResized(window_); // Will adjust dimensions for OIS mouse.

	entity_system_.reset(new EntitySystem{*scene_mgr_});
	health_system_.reset(new HealthSystem{*entity_system_});
	movement_system_.reset(new MovementSystem{*entity_system_});
	input_system_.reset(new InputSystem{*entity_system_, *keyboard_, *main_cam_});
	grid_system_.reset(new GridSystem{*entity_system_, *scene_mgr_});
	combat_system_.reset(new CombatSystem{*entity_system_, *scene_mgr_, *grid_system_});
	event_system_.reset(new EventSystem{*entity_system_});
	task_system_.reset(new TaskSystem{*entity_system_, *grid_system_, *combat_system_});
	production_system_.reset(new ProductionSystem{*entity_system_});
	time_system_.reset(new TimeSystem{*entity_system_});
	ai_system_.reset(new AISystem{*entity_system_});
	graphics_system_.reset(new GraphicsSystem{*entity_system_});
	trigger_system_.reset(new TriggerSystem{*entity_system_});
	mana_spell_system_.reset(new ManaSpellSystem{*entity_system_});

	systems_.emplace_back(entity_system_.get());
	systems_.emplace_back(health_system_.get());
	systems_.emplace_back(movement_system_.get());
	systems_.emplace_back(ai_system_.get());
	systems_.emplace_back(input_system_.get());
	systems_.emplace_back(grid_system_.get());
	systems_.emplace_back(task_system_.get());
	systems_.emplace_back(combat_system_.get());
	systems_.emplace_back(production_system_.get());
	systems_.emplace_back(time_system_.get());
	systems_.emplace_back(event_system_.get());
	systems_.emplace_back(graphics_system_.get());
	systems_.emplace_back(trigger_system_.get());
	systems_.emplace_back(mana_spell_system_.get());

	selection_box_.reset(new SelectionBox{"MainSelectionBox",
						                  *entity_system_,
						                  *scene_mgr_->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList{}),
						                  *scene_mgr_->createRayQuery(Ogre::Ray{}),
						                  *scene_mgr_});
	placer_.reset(new EntityPlacer{*entity_system_, *grid_system_, *scene_mgr_});
	entity_creator_.reset(new EntityCreator{*placer_, *entity_system_});
	game_serializer_.reset(new GameSerializer{*entity_system_});

	level_generator_.reset(new level_generators::DEFAULT_LEVEL_GENERATOR(*entity_system_, 10));
	create_empty_level(16, 16); // In case initial load fails.
	GUI::instance().init(this);
	LuaInterface::init(this);
	entity_creator_->init(GUI::instance().get_window("ENTITY_MANAGER"));
	GUI::instance().get_research().init(GUI::instance().get_window("RESEARCH"));
	Player::instance().init(entity_system_.get());
}

Game::~Game()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(window_, this);
	windowClosed(window_);
}

void Game::run()
{
	scene_mgr_->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	game_serializer_->load_game(*this, "intro_dummy_level");
	root_->startRendering();
}

void Game::update(Ogre::Real delta)
{
	GUI::instance().get_top_bar().update_time(delta);
	CEGUI::System::getSingleton().injectTimePulse(delta);
	if(camera_free_mode_)
		main_cam_->moveRelative(camera_dir_ * delta * /* atm hardcoded speed, move to lua! */ 180.f);

	if(GUI::instance().get_console().is_visible())
		GUI::instance().get_console().update_fps(delta, window_->getLastFPS());

	if(state_ == GAME_STATE::RUNNING || state_ == GAME_STATE::INTRO_MENU)
	{
		for(auto& sys : systems_)
			sys->update(delta);
	}
}

void Game::set_state(GAME_STATE state)
{
	if((state_ == GAME_STATE::INTRO_MENU || state_ == GAME_STATE::MENU)
	   && state != GAME_STATE::RUNNING && state != GAME_STATE::ENDED)
		return; // Invalid transition.

	if(state_ != state)
	{
		if(state == GAME_STATE::RUNNING)
		{
			GUI::instance().set_visible("MESSAGE", false);
		}
		else if(state == GAME_STATE::PAUSED)
			GUI::instance().set_visible("MESSAGE", true);
		state_ = state;
	}
}

void Game::new_game(std::size_t width, std::size_t height)
{
	GUI::instance().get_log().clear();
	create_empty_level(width, height);
	level_generator_->generate(width, height);
}

void Game::create_empty_level(std::size_t width, std::size_t height)
{
	entity_system_->delete_entities();
	entity_system_->cleanup();

	Ogre::SceneNode* ground_node{};
	if(ground_entity_)
	{ // Recreate if already exists.
		ground_node = ground_entity_->getParentSceneNode();
		ground_node->detachObject(ground_entity_);
		scene_mgr_->destroyEntity(ground_entity_);
		scene_mgr_->destroySceneNode(ground_node);

		auto& mesh_mgr = Ogre::MeshManager::getSingleton();
		if(mesh_mgr.resourceExists("ground"))
		{
			//auto plane = mesh_mgr.getByName("ground");
			mesh_mgr.unload("ground");
			mesh_mgr.remove("ground");
		}
		mesh_mgr.unloadUnreferencedResources();
	}

	Ogre::Real actual_width{width * 100.f - 100.f}, actual_height{height * 100.f - 100.f};
	ground_.reset(new Ogre::Plane{Ogre::Vector3::UNIT_Y, 0});
	Ogre::MeshManager::getSingleton().createPlane(
		"ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		*ground_, actual_width, actual_height, 20, 20, true, 1, (Ogre::Real)width, (Ogre::Real)height, Ogre::Vector3::UNIT_Z
	);

	ground_entity_ = scene_mgr_->createEntity("ground");
	ground_node = scene_mgr_->getRootSceneNode()->createChildSceneNode();

	ground_entity_->setCastShadows(false);
	ground_node->attachObject(ground_entity_);
	ground_node->setPosition((width * 100.f - 100.f) / 2.f, 0.f, (height * 100.f - 100.f) / 2.f);
	ground_entity_->setMaterialName("rocky_ground");
	ground_entity_->setQueryFlags(0);
	Grid::instance().create_graph(*entity_system_, Ogre::Vector2{0, 0}, width, height, 100.f);
}

void Game::reset_camera()
{
	main_cam_->setPosition(0.f, 600.f, 0.f);
	auto target = Grid::instance().get_center_position(*entity_system_);
	main_cam_->lookAt(target.x, 0.f, target.y);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& event)
{
	keyboard_->capture();
	mouse_->capture();

	update(event.timeSinceLastFrame);
	CEGUI::System::getSingleton().injectTimePulse(event.timeSinceLastFrame); // Update CEGUI.

	if(state_ == GAME_STATE::ENDED)
		return false;
	else
		return true;
}

bool Game::keyPressed(const OIS::KeyEvent& event)
{
	switch(event.key)
	{
		case OIS::KC_ESCAPE:
			if(GUI::instance().escape_pressed())
				return true;
			if(state_ != GAME_STATE::MENU && state_ != GAME_STATE::INTRO_MENU)
				set_state(state_ == GAME_STATE::RUNNING ? GAME_STATE::PAUSED : GAME_STATE::RUNNING);
			return true;
		case OIS::KC_GRAVE:
			if(keyboard_->isModifierDown(OIS::Keyboard::Modifier::Shift))
				entity_creator_->set_visible(!entity_creator_->is_visible());
			else
				GUI::instance().get_console().set_visible(!GUI::instance().get_console().is_visible());
			return true;
	}

	// Pass to CEGUI.
	auto& cont = CEGUI::System::getSingleton().getDefaultGUIContext();
	auto b1 = cont.injectKeyDown((CEGUI::Key::Scan)event.key);
	auto b2 = cont.injectChar((CEGUI::Key::Scan)event.text);
	if(b1 || b2 || state_ == GAME_STATE::MENU) // Guarantees both key and char injection.
		return true;

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
	if(CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)event.key)
	   || state_ == GAME_STATE::ENDED)
		return true; // Note: This wont return if editbox was focused!

	// Allows for free camera movement during debbuging.
	if(camera_free_mode_ && !GUI::instance().get_console().is_visible())
	{
		switch(event.key)
		{
			case OIS::KC_A:
				camera_dir_.x = 0;
				break;
			case OIS::KC_D:
				camera_dir_.x = 0;
				break;
			case OIS::KC_W:
				camera_dir_.z = 0;
				break;
			case OIS::KC_S:
				camera_dir_.z = 0;
				break;
			case OIS::KC_SPACE:
				camera_dir_.y = 0;
				break;
			case OIS::KC_LCONTROL:
				camera_dir_.y = 0;
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
	auto pos = get_mouse_click_position(event);
	if(pos.first)
	{ // Save mouse position, so that it can be retrieved form Lua.
		mouse_position_.x = pos.second.x;
		mouse_position_.y = pos.second.z;
	}

	if(placer_->is_visible() && pos.first)
		placer_->update_position(pos.second);
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
	if(gui_context.injectMouseButtonDown(ois_to_cegui(id)) || state_ == GAME_STATE::MENU)
		return true;

	if(id == OIS::MB_Left && !placer_->is_visible()) // TODO: State switch!
	{ // Start selection.
		auto& mouse = gui_context.getMouseCursor();

		Ogre::Vector2 start{
			mouse.getPosition().d_x / (float)event.state.width,
			mouse.getPosition().d_y / (float)event.state.height
		};
		selection_box_->set_starting_point(start);
		selection_box_->clear();
		selection_box_->set_selecting(true);
	}

	if(placer_->is_visible())
	{
		if(id == OIS::MB_Left && ((placer_->can_place_when_game_paused() && state_ == GAME_STATE::PAUSED)
		   || state_ == GAME_STATE::RUNNING))
			placer_->place(GUI::instance().get_console());
		else if(id == OIS::MB_Right)
			placer_->set_visible(false);
	}


	return true;
}

bool Game::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
	auto& gui_context = CEGUI::System::getSingleton().getDefaultGUIContext();
	gui_context.injectMouseButtonUp(ois_to_cegui(id));
	if(state_ == GAME_STATE::MENU)
		return true;

	if(id == OIS::MB_Left && selection_box_->is_selecting())
	{
		auto& mouse = gui_context.getMouseCursor();
		Ogre::Vector2 end{
			mouse.getPosition().d_x / (float)event.state.width,
			mouse.getPosition().d_y / (float)event.state.height
		};
		selection_box_->execute_selection(end, *main_cam_, keyboard_->isKeyDown(OIS::KC_LSHIFT));
		if(selection_box_->get_selected_entities().size() == 1)
			GUI::instance().get_tracker().set_tracked_entity(selection_box_->get_selected_entities()[0], *entity_system_);
		selection_box_->set_selecting(false);
	}

	return true;
}

void Game::windowResized(Ogre::RenderWindow* window)
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

void Game::windowClosed(Ogre::RenderWindow* window)
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
#ifdef _DEBUG
	window_ = root_->createRenderWindow("Dungeon Keeper", 1920, 1080, false);
#else
	window_ = root_->createRenderWindow("Dungeon Keeper", 1920, 1080, true);
#endif
	window_->setVisible(true);

	// Scene init.
	// TODO: Research different types of scene managers!
	scene_mgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
	main_cam_ = scene_mgr_->createCamera("MainCam");
	main_cam_->setPosition(0, 300, 0);
	main_cam_->lookAt(300, 0, 300);
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
	//CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("AlfiskoSkin/Tooltip"); // no support :(

	// Button test.
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* sheet = wmgr.createWindow("DefaultWindow", "MainWindow/Sheet");
	sheet->setMousePassThroughEnabled(true);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

void Game::command_to_mine()
{
	// Find miner with the smallest task queue.
	std::size_t id = Component::NO_ENTITY;
	std::size_t queue_size = std::numeric_limits<std::size_t>::max();
	for(const auto& ent : entity_system_->get_component_container<TaskHandlerComponent>())
	{
		/**
		 * Note: Even if the mineable structure may not contain gold, only those who can
		 *       actually mine (this include gold) can mine it, so the ability to fulfill
		 *       such task is required. (Removing it allows any entity capable
		 *       of killing to mine.)
		 */
		if(ent.second.possible_tasks.test((int)TASK_TYPE::GO_KILL) &&
		   ent.second.possible_tasks.test((int)TASK_TYPE::GO_PICK_UP_GOLD) &&
		   ent.second.task_queue.size() < queue_size)
		{
			queue_size = ent.second.task_queue.size();
			id = ent.first;
		}
	}
	if(id != Component::NO_ENTITY)
	{
		for(const auto& selected : selection_box_->get_selected_entities())
		{
			if(entity_system_->has_component<MineComponent>(selected))
			{
				auto task = TaskHelper::create_task(*entity_system_, selected, TASK_TYPE::GO_KILL);
				TaskHelper::add_task(*entity_system_, id, task);
			}
		}
	}
	else
		GUI::instance().get_log().print("[ERROR] You don't have any miners.");
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
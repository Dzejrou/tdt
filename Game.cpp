#include "Game.hpp"
#include "lppscript/LppScript.hpp"
#include "EntitySystem.hpp"
#include "HealthSystem.hpp"
#include "MovementSystem.hpp"
#include "AISystem.hpp"
#include "InputSystem.hpp"
#include "GridSystem.hpp"
#include "TaskSystem.hpp"
#include "CombatSystem.hpp"
#include "ProductionSystem.hpp"
#include "TimeSystem.hpp"
#include "EventSystem.hpp"
#include "GraphicsSystem.hpp"
#include "TriggerSystem.hpp"
#include "ManaSpellSystem.hpp"
#include "WaveSystem.hpp"
#include "LuaInterface.hpp"
#include "Grid.hpp"
#include "GUI.hpp"
#include "Player.hpp"
#include "LevelGenerators.hpp"
#include "Spellcaster.hpp"
#include "OptionsWindow.hpp"
#include "Camera.hpp"
#include "SelectionBox.hpp"
#include "EntityPlacer.hpp"
#include "EntityCreator.hpp"
#include "GameSerializer.hpp"

Game::Game() // TODO: Init systems.
	: state_{GAME_STATE::INTRO_MENU}, root_{}, window_{},
	  scene_mgr_{}, main_cam_{}, main_light_{},
	  main_view_{}, input_{}, keyboard_{}, mouse_{},
	  renderer_{}, placer_{}, ground_{},
	  selection_box_{}, entity_creator_{},
	  mouse_position_{}, level_generator_{}, spell_caster_{}
{
	main_cam_.reset(new Camera{});
	ogre_init();
	ois_init();
	cegui_init();
	windowResized(window_); // Will adjust dimensions for OIS mouse.

	entity_system_.reset(new EntitySystem{*scene_mgr_});
	health_system_.reset(new HealthSystem{*entity_system_});
	movement_system_.reset(new MovementSystem{*entity_system_});
	input_system_.reset(new InputSystem{*entity_system_, *keyboard_, *(main_cam_->camera_)});
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
	wave_system_.reset(new WaveSystem{*entity_system_});

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
	systems_.emplace_back(wave_system_.get());

	selection_box_.reset(new SelectionBox{"MainSelectionBox", *entity_system_,
						                  *scene_mgr_->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList{}),
						                  *scene_mgr_->createRayQuery(Ogre::Ray{}), *scene_mgr_});
	placer_.reset(new EntityPlacer{*entity_system_, *grid_system_, *scene_mgr_});
	entity_creator_.reset(new EntityCreator{*placer_, *entity_system_});
	game_serializer_.reset(new GameSerializer{*entity_system_});

	level_generator_.reset(new level_generators::DEFAULT_LEVEL_GENERATOR(*entity_system_, 10));

	auto& gui = GUI::instance();
	gui.init(this);
	LuaInterface::init(this);
	entity_creator_->init(gui.get_window("ENTITY_MANAGER"));
	gui.get_research().init(gui.get_window("RESEARCH"));
	Player::instance().init(entity_system_.get());
	spell_caster_.reset(new Spellcaster(*placer_, *selection_box_));
	gui.get_spell_casting().set_caster(spell_caster_.get());
	Player::instance().set_initial_unlocks(gui.get_spell_casting().get_spells(),
										   gui.get_builder().get_buildings());

	// Wave system has it's countdown label directly wired to the GUI.
	wave_system_->set_countdown_window(GUI::instance().get_window("NEXT_WAVE/NEXT_LABEL"));

	create_empty_level(16, 16); // In case initial load fails.
	main_cam_->look_at(Grid::instance().get_center_position(*entity_system_));
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

void Game::update(tdt::real delta)
{
	GUI::instance().get_top_bar().update_time(delta);
	CEGUI::System::getSingleton().injectTimePulse(delta);

	if(GUI::instance().get_console().is_visible())
		GUI::instance().get_console().update_fps(delta, window_->getLastFPS());

	if(state_ == GAME_STATE::RUNNING || state_ == GAME_STATE::INTRO_MENU)
	{
		for(auto& sys : systems_)
			sys->update(delta);
	}

	// Camera movement caused by mouse.
	if(!main_cam_->get_free_mode())
	{
		auto& mouse = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor();
		auto width = main_view_->getActualWidth();
		auto height = main_view_->getActualHeight();
		auto pos = mouse.getPosition();

		if(pos.d_x < 10.f)
			main_cam_->move(DIRECTION::LEFT, delta);
		else if(pos.d_x > width - 10.f)
			main_cam_->move(DIRECTION::RIGHT, delta);
		else if(pos.d_y < 10.f)
			main_cam_->move(DIRECTION::DOWN, delta);
		else if(pos.d_y > height - 10.f)
			main_cam_->move(DIRECTION::UP, delta);
		main_cam_->update(delta); // Additional movement caused by keys.
	}
	else // Movement cause by keys (this one includes elevation).
		main_cam_->update(delta);
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

void Game::new_game(tdt::uint width, tdt::uint height)
{
	GUI::instance().get_log().clear();
	GUI::instance().get_message().set_visible(false);
	create_empty_level(width, height);

	wave_system_->clear_spawn_nodes();
	if(lpp::Script::instance().call<bool, tdt::uint, tdt::uint>("game.init_level", width, height))
		level_generator_->generate(width, height, *wave_system_);
	wave_system_->start();
	reset_unlocks();
	Player::instance().reset();
}

void Game::create_empty_level(tdt::uint width, tdt::uint height)
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
			mesh_mgr.unload("ground");
			mesh_mgr.remove("ground");
		}
		mesh_mgr.unloadUnreferencedResources();
	}

	tdt::real actual_width{width * 100.f - 100.f}, actual_height{height * 100.f - 100.f};
	ground_.reset(new Ogre::Plane{Ogre::Vector3::UNIT_Y, 0});
	Ogre::MeshManager::getSingleton().createPlane(
		"ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		*ground_, actual_width, actual_height, 20, 20, true, 1, (tdt::real)width, (tdt::real)height, Ogre::Vector3::UNIT_Z
	);

	ground_entity_ = scene_mgr_->createEntity("ground");
	ground_node = scene_mgr_->getRootSceneNode()->createChildSceneNode();

	ground_entity_->setCastShadows(false);
	ground_node->attachObject(ground_entity_);
	ground_node->setPosition((width * 100.f - 100.f) / 2.f, 0.f, (height * 100.f - 100.f) / 2.f);
	ground_entity_->setMaterialName("rocky_ground");
	ground_entity_->setQueryFlags(0);
	Grid::instance().create_graph(*entity_system_, Ogre::Vector2{0, 0}, width, height, 100.f);

	// Adjust camera.
	main_cam_->set_start(Ogre::Vector2{actual_width / 2 - 300.f, actual_height / 2 - 300.f},
						 Grid::instance().get_center_position(*entity_system_), 400.f);
	main_cam_->reset();
}

void Game::reset_camera()
{
	main_cam_->reset();
}

void Game::reset_unlocks()
{
	auto& spellcaster = GUI::instance().get_spell_casting();
	auto& builder = GUI::instance().get_builder();
	auto& player = Player::instance();

	spellcaster.clear_spells();
	builder.clear_buildings();

	for(const auto& spell : player.get_initial_spells())
		spellcaster.register_spell(spell);

	for(const auto& building : player.get_initial_buildings())
		builder.register_building(building);

	GUI::instance().get_research().reset_research();
}

void Game::set_throne_id(tdt::uint id)
{
	throne_id_ = id;
}

tdt::uint Game::get_throne_id() const
{
	return throne_id_;
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
			placer_->set_visible(false);
			spell_caster_->stop_casting();
			return true;
		case OIS::KC_GRAVE:
			if(keyboard_->isModifierDown(OIS::Keyboard::Modifier::Shift))
				entity_creator_->set_visible(!entity_creator_->is_visible());
			else
				GUI::instance().get_console().set_visible(!GUI::instance().get_console().is_visible());
			return true;
		case OIS::KC_NUMPAD0:
			toggle_camera_free_mode();
			return true;
	}

	// Pass to CEGUI.
	auto& cont = CEGUI::System::getSingleton().getDefaultGUIContext();
	auto b1 = cont.injectKeyDown((CEGUI::Key::Scan)event.key);
	auto b2 = cont.injectChar((CEGUI::Key::Scan)event.text);
	if(b1 || b2) // Guarantees both key and char injection.
		return true;

	if(state_ != GAME_STATE::RUNNING)
		return true;

	// Camera movement.
	if(!GUI::instance().get_console().is_visible())
		main_cam_->key_pressed((CEGUI::Key::Scan)event.key);

	return true;
}

bool Game::keyReleased(const OIS::KeyEvent& event)
{
	// Pass to CEGUI and Options (for key bindings).
	if(CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)event.key))
		return true;

	if(state_ != GAME_STATE::RUNNING)
		return true;

	// Camera movement.
	if(!GUI::instance().get_console().is_visible())
	{
		main_cam_->key_released((CEGUI::Key::Scan)event.key);
		GUI::instance().get_options().key_pressed((CEGUI::Key::Scan)event.key);
	}

	/**
	 * This will make sure global and targeted spells go off even when
	 * a hotkey is used.
	 */
	if(spell_caster_->get_spell_type() == SPELL_TYPE::GLOBAL ||
	   (spell_caster_->get_spell_type() == SPELL_TYPE::TARGETED &&
	   selection_box_->get_selected_entities().size() == 1))
	{
		spell_caster_->cast();
	}

	return true;
}

bool Game::mouseMoved(const OIS::MouseEvent& event)
{
	if(main_cam_->get_free_mode() && event.state.buttonDown(OIS::MB_Right))
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

	if(id == OIS::MB_Left && !placer_->is_visible())
	{ // Start selection.
		auto& mouse = gui_context.getMouseCursor();
		Ogre::Vector2 position_screen{ // Mouse position on the screen -> NOT IN GRID!
			mouse.getPosition().d_x / (float)event.state.width,
			mouse.getPosition().d_y / (float)event.state.height
		};
		selection_box_->set_starting_point(position_screen);
		selection_box_->clear();
		selection_box_->set_selecting(true);
	}

	if(spell_caster_->is_casting())
	{
		if(id == OIS::MB_Left && state_ == GAME_STATE::RUNNING
		   && !(spell_caster_->get_spell_type() == SPELL_TYPE::TARGETED &&
				selection_box_->get_selected_entities().size() != 1))
		{
			/**
			 * Note: If the spell is targeted and not one entity is selected, the spell shall be casted
			 *       on mouse button release that makes sufficient selection.
			 */
			auto position_grid = get_mouse_click_position(event); // This is position wrt to the grid.
			if(position_grid.first)
				spell_caster_->cast(Ogre::Vector2{position_grid.second.x, position_grid.second.z});

		}
		else if(id == OIS::MB_Right)
		{
			placer_->set_visible(false);
			spell_caster_->stop_casting();
		}
	}
	else if(placer_->is_visible())
	{
		if(id == OIS::MB_Left && ((placer_->can_place_when_game_paused() && state_ == GAME_STATE::PAUSED)
		   || state_ == GAME_STATE::RUNNING))
			placer_->place();
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
		selection_box_->execute_selection(end, *(main_cam_->camera_), keyboard_->isKeyDown(OIS::KC_LSHIFT));
		if(selection_box_->get_selected_entities().size() == 1)
			GUI::instance().get_tracker().set_tracked_entity(selection_box_->get_selected_entities()[0], *entity_system_);
		selection_box_->set_selecting(false);
	}

	/**
	 * Note: Selected the spell without a target, so when we select
	 *       one target, apply the effect on him.
	 *		 This will also cause global spells to be casted immediately after clicking the button.
	 */
	if(selection_box_->get_selected_entities().size() == 1 && spell_caster_->get_spell_type() == SPELL_TYPE::TARGETED ||
	   spell_caster_->get_spell_type() == SPELL_TYPE::GLOBAL)
	{
		spell_caster_->cast();
	}

	return true;
}

void Game::windowResized(Ogre::RenderWindow* window)
{
	if(window != window_) // For the possibility of more windows.
		return;
	tdt::uint width, height, depth;
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
	window_ = root_->createRenderWindow("Dungeon Keeper", 1920, 1080, false);
#endif
	window_->setVisible(true);

	// Scene init.
	// TODO: Research different types of scene managers!
	scene_mgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
	auto main_cam = scene_mgr_->createCamera("MainCam");
	main_cam->setPosition(0, 300, 0);
	main_cam->lookAt(300, 0, 300);
	main_cam->setNearClipDistance(5);
	main_view_ = window_->addViewport(main_cam);
	main_cam->setAspectRatio(tdt::real(main_view_->getActualWidth()) /
							  tdt::real(main_view_->getActualHeight()));
	main_light_ = scene_mgr_->createLight("MainLight");
	main_light_->setPosition(20, 80, 50);
	main_light_->setVisible(false); // Currently using Light Crystals.

	Ogre::WindowEventUtilities::addWindowEventListener(window_, this);
	root_->addFrameListener(this);
	main_cam_->init(main_cam);
}

void Game::ois_init()
{
	OIS::ParamList pl;
	tdt::uint whnd = 0;
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
	main_cam_->set_free_mode(!main_cam_->get_free_mode());
}

std::pair<bool, Ogre::Vector3> Game::get_mouse_click_position(const OIS::MouseEvent& event) const
{
	auto& mouse = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor();
	float screen_x = mouse.getPosition().d_x / (float)event.state.width;
	float screen_y = mouse.getPosition().d_y / (float)event.state.height;
	Ogre::Ray ray = main_cam_->camera_->getCameraToViewportRay(screen_x, screen_y);

	auto res = ray.intersects(*ground_);
	auto pos = ray.getPoint(res.second);

	return std::make_pair(res.first, pos);
}
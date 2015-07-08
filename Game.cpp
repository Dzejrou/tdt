#include "Game.hpp"

Game::Game()
    : state_{GAME_STATE::RUNNING}, root_{nullptr}, window_{nullptr},
      scene_mgr_{nullptr}, main_cam_{nullptr}, main_light_{nullptr},
      main_view_{nullptr}, input_{nullptr}, keyboard_{nullptr}, mouse_{nullptr},
      entities_{}
{
    ogre_init();
    ois_init();
}

void Game::run()
{
    scene_mgr_->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
    auto ogre = scene_mgr_->createEntity("ogrehead.mesh");
    test_node = scene_mgr_->getRootSceneNode()->createChildSceneNode();
    test_node->attachObject(ogre);

    root_->startRendering();
}

void Game::update(Ogre::Real delta)
{
    if(test_dir == 1)
        test_node->rotate(Ogre::Vector3(0, 0, 1), Ogre::Radian(0.001));
    else if(test_dir == 2)
        test_node->rotate(Ogre::Vector3(0, 0, 1), Ogre::Radian(-0.001));
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& event)
{
    if(window_->isClosed())
        return false; // Will end the game.

    keyboard_->capture();
    mouse_->capture();

    update(event.timeSinceLastFrame);

    // TODO:
    // Research hypothesis - processor will assume false on conditionals.
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
            state_ = GAME_STATE::ENDED;
            return false;
        case OIS::KC_A:
            test_dir = 1;
            break;
        case OIS::KC_D:
            test_dir = 2;
            break;
    }

    return true;
}

bool Game::keyReleased(const OIS::KeyEvent& event)
{
    if(event.key == OIS::KC_A || event.key == OIS::KC_D)
        test_dir = 0;
    return true;
}

bool Game::mouseMoved(const OIS::MouseEvent& event)
{
    if(event.state.buttonDown(OIS::MB_Left))
    {
        main_cam_->yaw(Ogre::Degree(.13 * event.state.X.rel));
        main_cam_->pitch(Ogre::Degree(.13 * event.state.Y.rel));
    }
    else if(event.state.buttonDown(OIS::MB_Right))
    {
        main_cam_->yaw(Ogre::Degree(-.13 * event.state.X.rel));
        main_cam_->pitch(Ogre::Degree(-.13 * event.state.Y.rel));
    }

    return true;
}

bool Game::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
    return true;
}

bool Game::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id)
{
    return true;
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
    Ogre::String name, loc_type;
    auto selit = cf.getSectionIterator();
    while(selit.hasMoreElements())
    {
        Ogre::ConfigFile::SettingsMultiMap* settings = selit.getNext();
        for(auto& x : *settings)
        {
            loc_type = x.first;
            name = x.second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, loc_type);
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
    main_cam_->lookAt(0, 0, -300);
    main_cam_->setPosition(0, 0, 80);
    main_cam_->setNearClipDistance(5);
    main_view_ = window_->addViewport(main_cam_);
    main_cam_->setAspectRatio(Ogre::Real(main_view_->getActualWidth()) /
                              Ogre::Real(main_view_->getActualHeight()));
    main_light_ = scene_mgr_->createLight("MainLight");
    main_light_->setPosition(20, 80, 50);

    root_->addFrameListener(this);
}

void Game::ois_init()
{
    OIS::ParamList pl;
    std::size_t whnd = 0;
    std::string whnd_str;

    window_->getCustomAttribute("WINDOW", &whnd);
    whnd_str = std::to_string(whnd);
    pl.insert(std::make_pair(std::string("WINDOW"), whnd_str));

    input_ = OIS::InputManager::createInputSystem(pl);

    keyboard_ = static_cast<OIS::Keyboard*>(input_->createInputObject(OIS::OISKeyboard, true));
    mouse_ = static_cast<OIS::Mouse*>(input_->createInputObject(OIS::OISMouse, true));

    keyboard_->setEventCallback(this);
    mouse_->setEventCallback(this);
}

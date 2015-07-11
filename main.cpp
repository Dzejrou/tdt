#include <Ogre.h>

#include <memory>
#include <exception>
#include <string>

#ifdef WIN32
#include "windows.h"
#else
#include <iostream>
#endif

#include "LppScript/LppScript.hpp"
#include "Game.hpp"

void print_msg(const std::string&, const std::string&);

// Tests:
void lua_test();
void ogre_test();

int show_msg(lpp::Script::state L)
{
	std::string s = lua_tostring(L, -1);
	print_msg(s, "Message from Lua:");
	return 0;
}

#ifdef WIN32
INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmd, int cmd_show)
#else
int main(int argc, char** argv)
#endif
{
	try
	{
        lpp::Script::get_singleton().register_function("show_msg", show_msg);
        Game game{};
        game.run();
        //lua_test();
        //ogre_test();
	}
	catch(const Ogre::Exception& ex)
	{
        print_msg(ex.getFullDescription().c_str(),
                  "Ogre Exception!");
		return 1;
	}
	catch(const lpp::Exception& ex)
	{
        print_msg(ex.what(), "Lua Exception!");
        return 1;
	}
	catch(const std::exception& ex)
	{
        print_msg(ex.what(), "Std Exception!");
        return 1;
	}
	catch(...)
	{
        print_msg("Unknown exception caught in main!", "Unknown Exception!");
        return 1;
	}

	return 0;
}

/**
 * Brief: Prints a message to the screen, either in a message box (win) or to the
 *        command line.
 * Param: The message to be printed.
 * Param: The title of the message (top bar of the message box, start of the console output).
 */
void print_msg(const std::string& msg, const std::string& title = "NULL")
{
#ifdef WIN32
    MessageBoxA(nullptr, msg.c_str(), title.c_str(), 0);
#else
    std::cout << "[" << title << "] " << msg << std::endl;
#endif
}

/**
 * Brief: Set of tests designed to make sure all of the aspects of the lpp::Script class
 *        are working properly.
 */
void lua_test()
{
    lpp::Script& script = lpp::Script::get_singleton();
    script.load("scripts/test.lua");

    std::string name = script.get<std::string>("programmer.name");
    print_msg(name, "Name:");

    int age = script.get<int>("programmer.age");
    print_msg(std::to_string(age), "Age:");

    std::string course = script.get<std::string>("course");
    print_msg(course);

    script.execute("programmer.project = 'dungeon keeper'");
    std::string project = script.get<std::string>("programmer.project");
    print_msg(project, "Project:");

    int res = script.call<int, int, int, int, int>("sum", 1, 2, 3, 4);
    print_msg(std::to_string(res), "Result of sum:");

    std::string univ = script.get<std::string>("programmer.history.university");
    print_msg(univ, "University:");

    script.register_value<bool>("lol", true);
    bool lol = script.get<bool>("lol");
    print_msg(lol ? "true" : "false", "Registered value:");

    int id = script.call<int, int, int>("get_block_id", 3, 3);
    print_msg(std::to_string(id), "Block ID at [3,3]:");

    script.call<void, const std::string&>("show_msg", "This is from a C++ function registered in Lua called from C++!");
}

void ogre_test()
{
    Ogre::String plugs = "plugins_d.cfg";
    Ogre::String res = "resources_d.cfg";

    Ogre::Root* root = new Ogre::Root(plugs);

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
            //print_msg(name, loc_type);
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, loc_type);
        }
    }

    if(!(root->restoreConfig() || root->showConfigDialog()))
    {
        print_msg("Config dialog failed.", "Ogre error:");
        return;
    }
    else
        root->initialise(false);

    auto window = root->createRenderWindow("Test.", 800, 600, false);
    window->setVisible(true);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    auto scene = root->createSceneManager(Ogre::ST_GENERIC);
    auto cam = scene->createCamera("MainCam");
    cam->lookAt(0, 0, -300);
    cam->setPosition(0, 0, 80);
    cam->setNearClipDistance(5);
    auto view = window->addViewport(cam);
    cam->setAspectRatio(Ogre::Real(view->getActualWidth()) /
                        Ogre::Real(view->getActualHeight()));

    auto light = scene->createLight("MainLight");
    //auto node = scene->createSceneNode();
    //node->attachObject(light);
    light->setPosition(20, 80, 50);
    //light->setDirection(Ogre::Vector3{0, 0, -300});
    
    //Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation("resources/meshes","FileSystem","TestMeshes");
    Ogre::Entity* sphere = scene->createEntity("ogrehead.mesh");
    auto node2 = scene->getRootSceneNode()->createChildSceneNode();
    node2->attachObject(sphere);

    scene->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
    view->setBackgroundColour(Ogre::ColourValue::Blue);

    /*
    Ogre::Plane plane{Ogre::Vector3::UNIT_Y, 0};
    Ogre::v1::MeshManager::getSingleton().createPlane(
        "ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    scene->setSkyPlane(true, plane, "Ogre");
    */
 
    root->startRendering();
}
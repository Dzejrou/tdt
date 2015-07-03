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

int show_msg(lpp::Script::state L)
{
	std::string s = lua_tostring(L, -1);
	MessageBoxA(nullptr, s.c_str(), "Message from Lua:", 0);
	return 0;
}

void print_msg(const std::string&, const std::string&);

#ifdef WIN32
INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmd, int cmd_show)
#else
int main()
#endif
{
	try
	{
		lpp::Script script{};
		script.register_function("show_msg", show_msg);
		script.load("scripts/test.lua");
		std::string name = script.get<std::string>("programmer.name");
        print_msg(name, "Name:");

		int age = script.get<int>("programmer.age");
        print_msg(std::to_string(age).c_str(), "Age:");

		script.execute("programmer.project = 'dungeon keeper'");
		std::string project = script.get<std::string>("programmer.project");
        print_msg(project.c_str(), "Projeect:");

		int res = script.call<int, int, int, int, int>("sum", 1, 2, 3, 4);
        print_msg(std::to_string(res).c_str(), "Result of sum:");

		std::string univ = script.get<std::string>("programmer.history.university");
        print_msg(univ.c_str(), "University:");

		script.register_value<bool>("lol", true);
		bool lol = script.get<bool>("lol");
        print_msg(lol ? "true" : "false", "Registered value:");
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
	}
	catch(const std::exception& ex)
	{
        print_msg(ex.what(), "Std Exception!");
	}
	catch(...)
	{
        print_msg("Unknown exception caught in main!", "Unknown Exception!");
	}

	return 0;
}

void print_msg(const std::string& msg, const std::string& title = "NULL")
{
#ifdef WIN32
    MessageBoxA(nullptr, msg.c_str(), title.c_str(), 0);
#else
    std::cout << "[" << msg << "] " << std::endl;
#endif
}
#include <Ogre.h>
#include <memory>
#include <exception>
#include "windows.h"

#include "LppScript/LppScript.hpp"

INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmd, int cmd_show)
{
	try
	{
		lpp::Script script{"scripts/test.lua"};
		std::string name = script.get<std::string>("programmer.name");
		MessageBoxA(nullptr, name.c_str(), "Name:", 0);

		int age = script.get<int>("programmer.age");
		MessageBoxA(nullptr, std::to_string(age).c_str(), "Age:", 0);

		script.excecute("programmer.project = 'dungeon keeper'");
		std::string project = script.get<std::string>("programmer.project");
		MessageBoxA(nullptr, project.c_str(), "Project:", 0);

		int res = script.call<int, int, int, int>("sum", 1, 2, 3, 4);
		MessageBoxA(nullptr, std::to_string(res).c_str(), "Result of sum:", 0);

		std::string univ = script.get<std::string>("programmer.history.university");
		MessageBoxA(nullptr, univ.c_str(), "University:", 0);
	}
	catch(const Ogre::Exception& ex)
	{
		MessageBoxA(nullptr, ex.getFullDescription().c_str(),
					"Ogre Exception!", 0);
		return 1;
	}
	catch(const lpp::Exception& ex)
	{
		MessageBoxA(nullptr, ex.what(), "Lua Exception!", 0);
	}
	catch(const std::exception& ex)
	{
		MessageBoxA(nullptr, ex.what(), "Std Exception!", 0);
	}
	catch(...)
	{
		MessageBoxA(nullptr, "Unknown exception caught in main!",
					"Unknown Exception!", 0);
	}

	return 0;
}
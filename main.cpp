#include <Ogre.h>
#include <memory>
#include <exception>
#include "windows.h"

#include "LppScript.hpp"

INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmd, int cmd_show)
{
	try
	{
		MessageBoxA(nullptr, "TODO!", "TODO!", 0);
	}
	catch(const Ogre::Exception& ex)
	{
		MessageBoxA(nullptr, ex.getFullDescription().c_str(),
					"Ogre Exception!", 0);
		return 1;
	}
	catch(const lpp::Exception& ex)
	{
		MessageBoxA(nullptr, ex.what().c_str(), "Lua Exception!", 0);
	}
	catch(const std::exception& ex)
	{
		MessageBoxA(nullptr, ex.what(), "Std Exception!", 0);
	}
	catch(...)
	{
		MessageBoxA(nullptr, "Unknown exception caught in main!", "Unknown Exception!", 0);
	}

	return 0;
}
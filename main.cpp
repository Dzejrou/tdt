#include <lua.hpp>
#include <Ogre.h>
#include "windows.h"

#include <memory>

INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmd, int cmd_show)
{
	try
	{
		MessageBoxA(nullptr, "TODO!", "TODO!", 0);
	}
	catch(Ogre::Exception& ex)
	{
		MessageBoxA(nullptr, ex.getFullDescription().c_str(),
					"Exception caught in main!", 0);
		return 1;
	}

	return 0;
}
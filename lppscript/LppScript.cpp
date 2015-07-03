#include "LppScript.hpp"
#include <sstream>

/**
 * lpp::Script definitions:
 */
lpp::Script::Script()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}
lpp::Script::Script(const std::string& fname)
{
	L = luaL_newstate();
	if(luaL_dofile(L, fname.c_str()))
		throw Exception("Error loading a script: " + fname);
	luaL_openlibs(L);
}

lpp::Script::Script(Script&& other)
{
	L = other.L;
	other.L = nullptr;
}

void lpp::Script::execute(const std::string& command)
{
	if(luaL_dostring(L, command.c_str()))
		throw Exception("[Error][Lua] Cannot execute a command in a Lua script: " + command);
}

void lpp::Script::register_function(const std::string& name, lua_CFunction fn)
{
	lua_register(L, name.c_str(), fn);
}

void lpp::Script::load(const std::string& fname)
{
	if(luaL_dofile(L, fname.c_str()))
		throw Exception("[Error][Lua] Cannot load script: " + fname);
}

std::string lpp::Script::get_field_to_stack(const std::string& name)
{
	std::istringstream iss(name);
	std::string tmp;

	// Field extraction.
	std::getline(iss, tmp, '.'); // Name of table.
	lua_getglobal(L, tmp.c_str());

	while(std::getline(iss, tmp, '.'))
	{ // Sub fields.
		lua_pushstring(L, tmp.c_str());
		lua_gettable(L, -2);
		lua_remove(L, -2);
	}
	return tmp; // Last field name.
}

/**
 * lpp::Exception definitions:
 */
const char* lpp::Exception::what() const
{
	return msg_.c_str();
}
#include "LppScript.hpp"

lpp::Script::Script(const std::string& script_name)
	: l_state{luaL_newstate()}
{
	if(luaL_dofile(l_state, script_name.c_str()))
		throw Exception{"Error: Lua script not found: " + script_name};

}

lpp::Script::~Script()
{
	lua_close(l_state);
}

/*
 * lpp::Exception definition:
 */
std::string lpp::Exception::what()
{
	return message_;
}
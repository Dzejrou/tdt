#include "LppScript.hpp"

lpp::Script::Script(const std::string& script_name)
	: l_state{luaL_newstate()}
{
	if(luaL_dofile(l_state, script_name.c_str()))
		throw Exception{"Error: Lua script not found: " + script_name};

}

lpp::Script::~Script()
{
	if(l_state)
		lua_close(l_state);
}

bool lpp::Script::errors() const
{
	return error_que_.size() > 0;
}

void lpp::Script::register_error(const std::string& err_msg)
{
	error_que_.push_back(err_msg);
}

/*
 * lpp::Exception definition:
 */
const std::string& lpp::Exception::what() const
{
	return message_;
}
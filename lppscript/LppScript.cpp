#include "LppScript.hpp"
#include <sstream>

/**
 * Static member (singleton) initialization.
 */
std::unique_ptr<lpp::Script> lpp::Script::script_{nullptr};

/**
 * lpp::Script definitions:
 */
lpp::Script::Script()
	: loaded_scripts_{}, L{nullptr}
{
	L = luaL_newstate();
	luaL_openlibs(L);
}

void lpp::Script::execute(const std::string& command)
{
	if(luaL_dostring(L, command.c_str()))
		throw Exception("[Error][Lua] Cannot execute a command in a Lua script: " + command, L);
}

void lpp::Script::register_function(const std::string& name, lua_CFunction fn)
{
	lua_register(L, name.c_str(), fn);
}

void lpp::Script::load(const std::string& fname)
{
	if(luaL_dofile(L, fname.c_str()))
		throw Exception("[Error][Lua] Cannot load script: " + fname +
						".", L);

	loaded_scripts_.emplace(fname);
}

bool lpp::Script::is_nil(const std::string& name)
{
	std::string name2{name};
	if(name.find(".") != std::string::npos)
		name2 = get_field_to_stack(name);
	else
		lua_getglobal(L, name2.c_str());

	bool res = lua_isnil(L, -1);
	lua_pop(L, 1);
	return res == 1; // Lua returns C style bool (i.e. an integer).
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

void lpp::Script::clear_stack()
{
	int n = lua_gettop(L);
	lua_pop(L, n);
}

void lpp::Script::reload_all_scripts()
{
	for(const auto& script : loaded_scripts_)
		load(script);
}

lpp::Script& lpp::Script::get_singleton()
{
	if(!script_)
		script_.reset(new Script());
	return *script_;
}

lpp::Script* lpp::Script::get_singleton_ptr()
{
	if(!script_)
		script_.reset(new Script());
	return script_.get();
}

/**
 * lpp::Exception definitions:
 */
const char* lpp::Exception::what() const
{
	return msg_.c_str();
}

const char * lpp::Exception::what_lua() const
{
	if(L_)
		return lua_tostring(L_, -1);
	else
		return "UNKNOWN LUA ERROR";
}

bool lpp::Exception::has_lua_state() const
{
	return L_ != nullptr;
}

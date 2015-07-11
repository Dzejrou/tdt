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
{
	L = luaL_newstate();
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

std::string lpp::Script::get_field_to_stack(const std::string& name, bool pass_self)
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
        if(lua_isfunction(L, -1) && pass_self) // Method.
        {
            lua_pushvalue(L, -2); // Leave the last table on top as self.
            return tmp;
        }
        else
		    lua_remove(L, -2);
	}
	return tmp; // Last field name.
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
#pragma once

#include <lua.hpp>
#include <string>

namespace lpp
{

class Script
{
	public:
		using state = lua_State*;

		Script();
		Script(const std::string&);
		Script(Script&&);
		~Script() { if(L) lua_close(L); }

		void excecute(const std::string&);
		void register_function(const std::string&, lua_CFunction);
		void load(const std::string&);

		template<typename T>
		T get(const std::string& name)
		{
			if(!L)
				throw Exception("[Error][Lua] Lua state is null.");

			std::string sub_name{name};
			if(name.find(".") != std::string::npos)
				sub_name = get_field_to_stack(name);
			else
				lua_getglobal(L, name.c_str());

			if(lua_isnil(L, -1))
				throw Exception("[Error][Lua] Variable " + name + "is not defined or nil.");
		
			return get_<T>(sub_name);
		}

		template<typename Result, typename... Args>
		Result call(const std::string& fname, Args&&... as)
		{
			lua_getglobal(L, fname.c_str());
			int arg_count = push_args<Args...>(std::forward<Args>(as)...);
			if(lua_pcall(L, arg_count, 1, 0))
				throw Exception("[Error][Lua] Error while calling a Lua function: " + fname);

			return get_<Result>();
		}

	private:
		std::string get_field_to_stack(const std::string& name);
		
		template<typename T>
		T get_(const std::string& name = "unknown")
		{ // Will have specializations.
			throw Exception("[Error][Lua] Get method for a given type is not implemented to retrieve: " + name);
		}

		template<typename Arg, typename... Args>
		int push_args(Arg a, Args&&... as)
		{
			push_arg<Arg>(a);
			return push_args(std::forward<Args>(as)...) + 1;
		}

		template<typename Arg>
		int push_args(Arg a)
		{
			push_arg<Arg>(a);
			return 1;
		}

		template<typename Arg>
		void push_arg(Arg a)
		{
			throw Exception("[Error][Lua] Trying to push an argument of an invalid type.");
		}

		state L;
};

class Exception
{
	public:
		Exception(const std::string& msg) : msg_{msg} {};
		const char* what() const;
	private:
		std::string msg_;
};



/**
 * Specializations for the method lpp::Script::get_ used to 
 * extract values form the Lua stack.
 */
template<>
inline std::string Script::get_<std::string>(const std::string& name)
{
	if(lua_isstring(L, -1))
		return std::string{lua_tostring(L, -1)};
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}

template<>
inline int Script::get_<int>(const std::string& name)
{
	if(lua_isinteger(L, -1))
		// Possible loss of data, Lua has 64 bit integers.
		return static_cast<int>(lua_tointeger(L, -1));
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}

template<>
inline double Script::get_<double>(const std::string& name)
{
	if(lua_isnumber(L, -1))
		return lua_tonumber(L, -1);
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}

template<>
inline bool Script::get_<bool>(const std::string& name)
{
	if(lua_isboolean(L, -1))
		return lua_toboolean(L, -1);
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}



/**
 * Specializations of the method lpp::Script::push_arg, which pushes a single
 * function argument onto the Lua stack.
 */
template<>
inline void Script::push_arg<int>(int arg)
{
	lua_pushinteger(L, arg);
}

template<>
inline void Script::push_arg<double>(double arg)
{
	lua_pushnumber(L, arg);
}

template<>
inline void Script::push_arg<char*>(char* arg)
{
	lua_pushstring(L, arg);
}

template<>
inline void Script::push_arg<bool>(bool arg)
{
	lua_pushboolean(L, arg);
}

} // Namespace lpp.
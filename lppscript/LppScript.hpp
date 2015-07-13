#pragma once

#include <lua.hpp>
#include <string>
#include <memory>

namespace lpp
{

/**
 * Class representing a Lua script, allows to register C++ functions, load variables, call functions,
 * execute strings containing Lua code and other functionalities.
 */
class Script
{
	public:
		using state = lua_State*;

		Script(Script&&);
		~Script() { if(L) lua_close(L); }

		void execute(const std::string&);
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
		Result call(const std::string& fname, Args... as, bool pass_self = false)
		{ // TODO: Call functions in tables!
			std::string fname2{fname};
			int self{0}; // Extra self arg.

			if(fname2.find('.') != std::string::npos)
			{
				fname2 = get_field_to_stack(fname, pass_self);
				if(pass_self) // Method.
					self = 1;
				else
					lua_remove(L, -1); // Remove parent table.
			}
			else
				lua_getglobal(L, fname2.c_str());

			int arg_count = push_args<Args...>(as...);
			lua_type(L, -(arg_count));

			if(lua_pcall(L, arg_count + self, 1, 0))
				throw Exception("[Error][Lua] Error while calling a Lua function: " + fname + "\n("
								+ lua_tostring(L, -1) + ").");

			return get_<Result>();
		}

		template<typename T>
		void register_value(const std::string& name, T val)
		{ // Deprecated?
			set(name, val)
		}

		template<typename T>
		void set(const std::string& name, T val)
		{
			execute(name + " = " + std::to_string(val));
		}

		template<typename T>
		std::vector<T> get_vector(const std::string& name)
		{
			if(!L)
					throw Exception("[Error][Lua] Lua state is null.");

			std::vector<T> tmp{};
			std::string sub_name{name};
			if(name.find(".") != std::string::npos)
				sub_name = get_field_to_stack(name);
			else
				lua_getglobal(L, name.c_str());

			if(lua_isnil(L, -1))
				return std::vector<T>{};

			lua_pushnil(L);
			while(lua_next(L, -2))
			{
				tmp.push_back(get_<T>());
				lua_pop(L, 1);
			}

			clear_stack();
			return tmp;
		}

		static Script& get_singleton();
		static Script* get_singleton_ptr();
	private:
		Script();
		std::string get_field_to_stack(const std::string&, bool = false);
		void clear_stack();

		static std::unique_ptr<Script> script_;

		template<typename T>
		T get_(const std::string& name = "unknown")
		{ // Will have specializations.
			throw Exception("[Error][Lua] Get method for a given type is not implemented to retrieve: " + name);
		}

		template<typename Arg, typename... Args>
		int push_args(Arg a, Args... as)
		{
			push_arg<Arg>(a);
			return push_args(as...) + 1;
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

	/**
	 * Exception class used to throw exception from the Script class.
	 */
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
inline float Script::get_<float>(const std::string& name)
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
		return (bool)lua_toboolean(L, -1);
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}

template<>
inline void Script::get_<void>(const std::string& name)
{
	// Note: Cannot make a partial specialization for the lpp::Script::call method, this dummy specialization
	//       will ensure that when a Lua function does not return, the lpp::Script::call won't throw.
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
inline void Script::push_arg<float>(float arg)
{
	lua_pushnumber(L, arg);
}

template<>
inline void Script::push_arg<const std::string&>(const std::string& arg)
{
	lua_pushstring(L, arg.c_str());
}

template<>
inline void Script::push_arg<bool>(bool arg)
{
	lua_pushboolean(L, arg);
}



/**
 * Specializations for the method lpp::Script::register_value, for std::string it avoids calling
 * the std::to_string function and stores bools manually (std::to_strings converts it to 0 or 1,
 * which would cause lpp::Script::get throw, because Lua would interpret it as an integer).
 */
template<>
inline void Script::register_value<const std::string&>(const std::string& name, const std::string& val)
{
	execute(name + " = '" + val + "'");
}

template<>
inline void Script::register_value<bool>(const std::string& name, bool val)
{
	execute(name + " = " + (val ? "true" : "false"));
}



} // Namespace lpp.
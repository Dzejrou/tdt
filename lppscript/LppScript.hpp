#pragma once

#include <lua.hpp>
#include <string>
#include <memory>
#include <vector>
#include <tuple>

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
		using regs = luaL_Reg;

		/**
		 * Destructor, closes the Lua virtual machine.
		 */
		~Script() { if(L) lua_close(L); }

		/**
		 * Brief: Returns the lua state representing the Lua virtual machine.
		 */
		state get_state() { return L; };

		/**
		 * Brief: Executes a given string from within Lua.
		 * Param: String containing commands to be executed.
		 */
		void execute(const std::string&);

		/**
		 * Brief: Registers a C++ function which can then be used from
		 *        within Lua.
		 * Param: Name of the function.
		 * Param: Function to be registered, it has to have the signature
		 *        int fname(lua_State*) and return the number of results
		 *        pushed onto the stack, arguments are on the stack.
		 */
		void register_function(const std::string&, lua_CFunction);

		/**
		 * Brief: Loads, compiles and executes a Lua script.
		 * Param: Name of the script file.
		 */
		void load(const std::string&);

		/**
		 * Brief: Returns true if a given value is nil, false otherwise.
		 * Param: Name of the variable containing the desired value.
		 */
		bool is_nil(const std::string&);

		/**
		 * Brief: Retrieves and returns a value from Lua.
		 * Param: Name of the variable containing the desired value.
		 */
		template<typename T>
		T get(const std::string& name)
		{
			if(!L)
				throw Exception("[Error][Lua] Lua state is null.");

			std::string sub_name{name}; // Access to values within tables.
			if(name.find(".") != std::string::npos)
				sub_name = get_field_to_stack(name);
			else
				lua_getglobal(L, name.c_str());

			if(lua_isnil(L, -1))
				throw Exception("[Error][Lua] Variable " + name + "is not defined or nil.", L);

			return get_<T>(sub_name);
		}

		/**
		 * Brief: Calls a given Lua function.
		 * Param: Name of the function.
		 * Param: Variadic list of arguments that are passed to the function.
		 */
		template<typename Result, typename... Args>
		Result call(const std::string& fname, Args... as)
		{
			// Allows to call function that are stored in tables.
			std::string fname2{fname};
			if(fname2.find('.') != std::string::npos)
				fname2 = get_field_to_stack(fname);
			else
				lua_getglobal(L, fname2.c_str());

			int arg_count = push_args<Args...>(as...);

			if(lua_pcall(L, arg_count, 1, 0))
				throw Exception("[Error][Lua] Error while calling a Lua function: " + fname + ".", L);

			return get_<Result>();
		}

		/**
		 * Brief: Sets a given variable to a given value.
		 * Param: Variable to be changed.
		 * Param: Value that the variable should be changed to.
		 */
		template<typename T>
		void set(const std::string& name, T val)
		{
			execute(name + " = " + std::to_string(val));
		}

		/**
		 * Brief: Retrieves a Lua array table (integer indexing) in the form
		 *        of a C++ vector.
		 * Param: Name of the array.
		 */
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

		/**
		 * Brief: Returns a reference to the lpp::Script singleton.
		 */
		static Script& get_singleton();

		/**
		 * Brief: Returns a pointer to the lpp::Script singleton.
		 */
		static Script* get_singleton_ptr();
	private:
		/**
		 * Constructor, kept private because of the use of the singleton pattern.
		 */
		Script();

		/**
		 * Brief: Gets a nested value (inside a table hierarchy) on top of the stack and
		 *        returns the name of the final variable (without table prefixes).
		 * Param: Full name of the variable.
		 */
		std::string get_field_to_stack(const std::string&);

		/**
		 * Brief: Pops everything off the stack.
		 */
		void clear_stack();

		/**
		 * Singleton instance.
		 */
		static std::unique_ptr<Script> script_;

		/**
		 * Brief: Returns the value stored on top of the stack.
		 */
		template<typename T>
		T get_(const std::string& name = "unknown")
		{ // Will have specializations.
			throw Exception("[Error][Lua] Get method for a given type is not implemented to retrieve: " + name);
		}

		/**
		 * Brief: Pushed a variadic list of arguments onto the stack to be passed
		 *        as arguments to a Lua function call, returns the amount of arguments
		 *        pushed onto the stack.
		 * Param: First argument in the list.
		 * Param: Tail argument list used in recursive call.
		 */
		template<typename Arg, typename... Args>
		int push_args(Arg a, Args... as)
		{
			push_arg<Arg>(a);
			return push_args(as...) + 1;
		}

		/**
		 * Brief: Bottom case of the push_args recursive call.
		 * Param: Argument to be pushed onto the stack.
		 */
		template<typename Arg>
		int push_args(Arg a)
		{
			push_arg<Arg>(a);
			return 1;
		}

		/**
		 * Brief: Pushes a single value onto the Lua stack.
		 * Param: Value to be pushed.
		 */
		template<typename Arg>
		void push_arg(Arg a)
		{
			throw Exception("[Error][Lua] Trying to push an argument of an invalid type.");
		}

		/**
		 * Lua state representing the Lua virtual machine.
		 */
		state L;
};

	/**
	 * Exception class used to throw exception from the Script class.
	 */
class Exception
{ // TODO: Add print stack, lua error etc.
	public:
		/**
		 * Constructor.
		 * Param: Message of the exception.
		 */
		Exception(const std::string& msg = "NO MSG", Script::state L = nullptr)
			: msg_{msg}, L_{L}
		{ /* DUMMY BODY */ }

		/**
		 * Brief: Returns the message of this exception.
		 */
		const char* what() const;

		/**
		 * Brief: Returns the Lua error message if possible.
		 */
		const char* what_lua() const;

		/**
		 * Brief: Returns true if a Lua state is captured by this exception.
		 */
		bool has_lua_state() const;
	private:
		/**
		 * Message the exception was called with.
		 */
		std::string msg_;

		/**
		 * Pointer to the Lua state, used for stack manipulation (like lua error retrieval).
		 */
		Script::state L_;
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
		return (int)lua_tointeger(L, -1);
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}

template<>
inline std::size_t Script::get_<std::size_t>(const std::string& name)
{
	if(lua_isinteger(L, -1))
		return (std::size_t)lua_tointeger(L, -1);
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}

template<>
inline float Script::get_<float>(const std::string& name)
{
	if(lua_isnumber(L, -1))
		return (float)lua_tonumber(L, -1);
	else
		throw Exception("[Error][Lua] Cannot retrieve a variable because of type mismatch: " + name);
}

template<>
inline bool Script::get_<bool>(const std::string& name)
{
	if(lua_isboolean(L, -1))
		return lua_toboolean(L, -1) == 1; // Small hack, lua_toboolean returns 0 or 1 (since it's a C API).
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
inline void Script::push_arg<std::size_t>(std::size_t arg)
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
inline void Script::set<const std::string&>(const std::string& name, const std::string& val)
{
	execute(name + " = '" + val + "'");
}

template<>
inline void Script::set<bool>(const std::string& name, bool val)
{
	execute(name + " = " + (val ? "true" : "false"));
}



} // Namespace lpp.
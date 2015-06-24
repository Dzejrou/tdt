#pragma once

#include <string>
#include <memory>
#include <lua.hpp>

namespace lpp
{

/**
 *
 */
class Script
{
	public:
		Script() : l_state{nullptr};
		Script(const std::string&);
		~Script();

		Script(const Script&) = delete;
		void operator=(const Script&) = delete;
	private:
		lua_State* l_state;
	
};

class Exception
{
	public:
		Exception(const std::string& msg) : message_{msg} {};
		std::string what();
	private:
		std::string message_;
};

}
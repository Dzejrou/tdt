#pragma once

#include <lua.hpp>
#include <string>

namespace lpp
{

class Script
{
	public:
		Script();
		Script(const std::string&);

	private:

};

class Exception
{
	public:
		Exception(const std::string& msg) : msg_{msg} {};
		const char* what() const;
	private:
		std::string msg_;
};

}
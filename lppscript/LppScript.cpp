#include "LppScript.hpp"


/**
 * lpp::Exception definitions:
 */
const char* lpp::Exception::what() const
{
	return msg_.c_str();
}
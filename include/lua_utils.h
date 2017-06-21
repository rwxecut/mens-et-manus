#pragma once

#include <string>
#include <stdarg.h>
#include <stdexcept>

class LuaError : public std::runtime_error {
public:
	explicit LuaError(std::string msg) : std::runtime_error(msg) {};
	explicit LuaError(char const *msg) : std::runtime_error(msg) {};
};
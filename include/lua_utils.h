#pragma once

#include <string>
#include <stdexcept>

namespace lua
{

	class LuaError : public std::runtime_error {
	public:
		explicit LuaError(std::string msg) : std::runtime_error(msg) {};
		explicit LuaError(char const *msg) : std::runtime_error(msg) {};
	};

}
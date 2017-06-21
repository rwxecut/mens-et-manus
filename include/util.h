#pragma once

#include <string>
#include <stdexcept>

namespace lua {
	class LuaError : public std::runtime_error {
	public:
		explicit LuaError(std::string msg) : std::runtime_error(msg) {};
		explicit LuaError(char const *msg) : std::runtime_error(msg) {};
	};
}

#include <sys/stat.h>

namespace file {
	bool exists(std::string fname)
	{
		struct stat buffer;
		return (stat (fname.c_str(), &buffer) == 0);
	}

	class FileNotFound : public std::runtime_error {
	public:
		explicit FileNotFound(std::string msg) : std::runtime_error(msg) {};
		explicit FileNotFound(char const *msg) : std::runtime_error(msg) {};
	};
}
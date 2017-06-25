#pragma once

#include <string>
#include <stdexcept>
#include <sstream>

namespace lua {
	class LuaError : public std::runtime_error {
	public:
		explicit LuaError (std::string const &msg) : std::runtime_error (msg) {};
		explicit LuaError (char const *msg) : std::runtime_error (msg) {};
	};
}

#include <sys/stat.h>

namespace file {
	bool exists (std::string const &fname) {
		struct stat buffer;
		return (stat (fname.c_str (), &buffer) == 0);
	}

	class FileNotFound : public std::runtime_error {

		static string fileNotFoundMsg
				(string const &fname, std::vector<string> const &dirs_searched) {
			std::stringstream msg;
			msg << "Couldn't find a " << fname << " file. Locations searched: ";
			for (auto p = dirs_searched.begin ();
			     p != dirs_searched.end (); p++)
				msg << *p << (p + 1 == dirs_searched.end () ? "." : ",") << "\n";
			return msg.str ();
		}

	public:
		explicit FileNotFound (string const &fname,
				std::vector<string> const &dirs_searched)
				: std::runtime_error (fileNotFoundMsg (fname, dirs_searched)) {};
	};
}
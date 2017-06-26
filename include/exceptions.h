#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

namespace lua {
	class LuaError : public std::runtime_error {
	public:
		explicit LuaError (std::string const &msg) : std::runtime_error (msg) {};
		explicit LuaError (char const *msg) : std::runtime_error (msg) {};
	};
}

namespace file {
	class FileNotFound : public std::runtime_error {

		static std::string fileNotFoundMsg
				(std::string const &fname,
						std::vector<std::string> const &dirs_searched) {
			std::stringstream msg;
			msg << "Couldn't find a " << fname << " file. Locations searched: ";
			for (auto p = dirs_searched.begin ();
			     p != dirs_searched.end (); p++)
				msg << *p << (p + 1 == dirs_searched.end () ? "." : ",") << "\n";
			return msg.str ();
		}

	public:
		explicit FileNotFound (std::string const &fname,
				std::vector<std::string> const &dirs_searched)
				: std::runtime_error (fileNotFoundMsg (fname, dirs_searched)) {};
	};
}

#include <SDL.h>
#include <GL/glu.h>

namespace video {
	class SDL_Error : std::runtime_error {
		std::string SDL_ErrorMsg (std::string msg) {
			std::stringstream msgStream;
			msgStream << "ERROR: " << msg << " SDL_GetError(): " << SDL_GetError ();
			return msgStream.str ();
		}

	public:
		explicit SDL_Error (int category, std::string msg)
				: std::runtime_error (SDL_ErrorMsg (msg)) {
			SDL_LogError (category, what ());
		};
	};


	class GL_Error : std::runtime_error {
		std::string GL_ErrorMsg (std::string msg) {
			std::stringstream msgStream;
			msgStream << "ERROR: " << msg
			          << " glGetError(): " << gluErrorString (glGetError ());
			return msgStream.str ();
		}

	public:
		GL_Error (std::string msg)
				: std::runtime_error (GL_ErrorMsg (msg)) {
			SDL_LogError (SDL_LOG_CATEGORY_VIDEO, what ());
		};
		GL_Error (char const *msg) : GL_Error (std::string (msg)) {};
	};
}

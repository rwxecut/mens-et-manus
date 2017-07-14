#include "exceptions.h"

#include <sstream>

namespace file {
	std::string FileNotFound::fileNotFoundMsg
			(std::string const &fname,
					std::vector<std::string> const &dirs_searched) {
		std::stringstream msg;
		msg << "Couldn't find a " << fname << " file. Locations searched: ";
		for (auto p = dirs_searched.begin ();
		     p != dirs_searched.end (); p++)
			msg << *p << (p + 1 == dirs_searched.end () ? "." : ",") << "\n";
		return msg.str ();
	}

	FileNotFound::FileNotFound (std::string const &fname,
		std::vector<std::string> const &dirs_searched)
		: std::runtime_error (fileNotFoundMsg (fname, dirs_searched)) {};
}

namespace video {
	std::string SDL_Error::SDL_ErrorMsg (std::string msg) {
			std::stringstream msgStream;
			msgStream << "ERROR: " << msg << " SDL_GetError(): " << SDL_GetError ();
			return msgStream.str ();
	}

	SDL_Error::SDL_Error (int category, std::string msg)
			: std::runtime_error (SDL_ErrorMsg (msg)) {
		SDL_LogError (category, what ());
	}

	std::string GL_Error::GL_ErrorMsg (std::string msg) {
		std::stringstream msgStream;
		msgStream << "ERROR: " << msg
		          << " glGetError(): " << gluErrorString (glGetError ());
		return msgStream.str ();
	}

	GL_Error::GL_Error (std::string msg)
			: std::runtime_error (GL_ErrorMsg (msg)) {
		SDL_LogError (SDL_LOG_CATEGORY_VIDEO, what ());
	};

	GL_Error::GL_Error (char const *msg) : GL_Error (std::string (msg)) {};
}
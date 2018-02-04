#include "exceptions.h"


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

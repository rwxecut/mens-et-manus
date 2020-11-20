#pragma once

#define SOL_CHECK_ARGUMENTS 1

#include <string>

#include "lib/sol.hpp"
#include "engine/Buffer.h"


namespace lua {
	class File {
		std::string filename;

	public:
		sol::state state;
		Buffer buffer;

		File (std::string const &filename);
		void call (const char *funcname);

		template<class Bind, typename... Args>
		void addBind (const char *name, Args &&... args) {
			state[name] = Bind (this, std::forward<Args> (args)...);
		}
	};
}

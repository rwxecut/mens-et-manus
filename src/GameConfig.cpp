#include <sstream>
#include <sys/stat.h>
#include "selene.h"
#include "GameConfig.h"
#include "util.h"

using std::string;

GameConfig::GameConfig (string fname) {
	sel::State luaconf{true};
	bool succ = false;
	for (string p : assets_dirs) {
		string fname_full = p + fname;
		if (file::exists (fname_full)) {
			files.assets_dir = fname_full;
			if (!luaconf.Load (fname_full))
				throw lua::LuaError (
						string ("Error loading configuration ") + fname_full + ".");
			else
				succ = true;
		}
	}
	if (!succ) {
		std::stringstream msg;
		msg << "Couldn't stat a config.lua file. Locations searched:\n";
		for (string p : assets_dirs) msg << p << "\n";
		throw file::FileNotFound (msg.str());
	}
}

GameConfig::GameConfig (GameConfig const &gc) {
	screen = gc.screen;
	video = gc.video;
	files = gc.files;
}

bool GameConfig::valid () const {
	//@formatter:off
	return (screen.width  > GLint(0))
	    && (screen.height > GLint(0));
	//@formatter:on
}

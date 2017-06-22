#include <sstream>
#include <sys/stat.h>
#include "selene.h"
#include "GameConfig.h"
#include "util.h"

using std::string;

std::vector<string> const GameConfig::assets_dirs  = {
		string("./"),
		string("../assets/")
};

string const GameConfig::config_fname = "mmconfig.lua";


bool GameConfig::findAssetsDir () {
	string assdir = "";
	for (string p : assets_dirs) {
		string fname = p + config_fname;
		if (file::exists (fname)) {
			files.assets_dir = p;
			return true;
		}
	}
	return false;
}

void GameConfig::loadLua (sel::State const &luaconf) {
	sel::Selector s = luaconf["screen"];
	screen.width = GLint(s["width"]);
	screen.height = GLint(s["height"]);

	s = luaconf["video"]["cam"];
	video.cam.fov = GLdouble(s["fov"]);
	video.cam.renderDistance = GLdouble(s["renderDistance"]);

	s = s["pos"];
	video.cam.pos.x = GLdouble(s["x"]);
	video.cam.pos.y = GLdouble(s["y"]);
	video.cam.pos.z = GLdouble(s["z"]);
}

GameConfig::GameConfig () {
	if (!findAssetsDir ())
		throw file::FileNotFound (config_fname, assets_dirs);
	sel::State luaconf{true};
	string fname = files.assets_dir + config_fname;
	if (!luaconf.Load (fname))
		throw lua::LuaError (
				string ("Error loading configuration from ") + fname + ".");
	loadLua (luaconf);
}

GameConfig::GameConfig (GameConfig const &gc) {
	screen = gc.screen;
	video = gc.video;
	files = gc.files;
}

bool GameConfig::valid () const {
	//@formatter:off
	return (screen.width  > 0)
	    && (screen.height > 0)
	    && (video.cam.fov > 0.0f && video.cam.fov < 180.0f);
	//@formatter:on
}

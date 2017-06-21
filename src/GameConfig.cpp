#include <lua_utils.h>
#include "selene.h"
#include "GameConfig.h"
#include "lua_utils.h"

using std::string;

GameConfig::GameConfig (char const *fname) {
	sel::State luaconf{true};
	if (!luaconf.Load (fname))
		throw lua::LuaError (string ("Error loading configuration ") + fname + ".");

	sel::Selector s = luaconf["screen"];
	screen.width = GLint(s["width"]);
	screen.height = GLint(s["height"]);

	s = luaconf["video"]["cam"];
	video.cam.fov = GLdouble(s["fov"]);

	s = s["pos"];
	video.cam.pos.x = GLdouble(s["x"]);
	video.cam.pos.y = GLdouble(s["y"]);
	video.cam.pos.z = GLdouble(s["z"]);
}

GameConfig::GameConfig (GameConfig const &gc) {
	screen = gc.screen;
	video = gc.video;
}

bool GameConfig::valid () const {
	//@formatter:off
	return (screen.width  > 0)
	    && (screen.height > 0)
		   && (video.cam.fov > 0.0f && video.cam.fov < 180.0f);
	//@formatter:on
}

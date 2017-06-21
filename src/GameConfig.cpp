#include "selene.h"
#include "GameConfig.h"
#include "lua_utils.h"

using std::string;

GameConfig::GameConfig (char const *fname) {
	sel::State luaconf{true};
	if (!luaconf.Load (fname))
		throw lua::LuaError (string ("Error loading configuration ") + fname + ".");

	screen_.width = GLint (luaconf["screen"]["width"]);
	screen_.height = GLint (luaconf["screen"]["height"]);
}

GameConfig::GameConfig (GameConfig const &gc) {
	screen_ = gc.screen;
}

bool GameConfig::valid () const {
	//@formatter:off
	return (screen.width  > GLint(0))
	    && (screen.height > GLint(0));
	//@formatter:on
}

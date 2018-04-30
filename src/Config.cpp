#include "Config.h"

#define CONFIG_PATH "../cfg/config.lua"


Config::Config () {
	logger.write ("Loading config");
	LuaFile *confFile = new LuaFile (CONFIG_PATH);
	sol::table conf = confFile->state["Config"];

	screen.width = conf["screen"]["width"];
	screen.height = conf["screen"]["height"];

	cam.moveSpeedMax = conf["cam"]["moveSpeedMax"];
	cam.moveAcceleration = conf["cam"]["moveAcceleration"];
	cam.zoomSpeed = conf["cam"]["zoomSpeed"];

	fpsMeasureInterval = conf["fpsInterval"];
}

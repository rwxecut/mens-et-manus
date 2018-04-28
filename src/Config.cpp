#include "Config.h"

#define CONFIG_PATH "../assets/config.lua"


Config::Config () {
	logger.write ("Loading config");
	LuaFile *conf = new LuaFile (CONFIG_PATH);

	screen.width = conf->state["screen"]["width"];
	screen.height = conf->state["screen"]["height"];

	cam.moveSpeedMax = conf->state["cam"]["moveSpeedMax"];
	cam.moveAcceleration = conf->state["cam"]["moveAcceleration"];
	cam.zoomSpeed = conf->state["cam"]["zoomSpeed"];

	fpsMeasureInterval = conf->state["fpsInterval"];
}

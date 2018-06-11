#include <Config.h>
#include "Config.h"

#define CONFIG_PATH "../cfg/config.lua"
#define SETTINGS_PATH "../cfg/settings.lua"
#define SETTINGS_DEFAULT_PATH "../cfg/settings_default.lua"


void Config::load () {
	loadConfig ();
	loadSettings ();
}


void Config::loadConfig () {
	logger.write ("Loading config");
	LuaFile confFile (CONFIG_PATH);
	sol::table conf = confFile.state["Config"];

	cam.moveSpeedMax = conf["cam"]["moveSpeedMax"];
	cam.moveAcceleration = conf["cam"]["moveAcceleration"];
	cam.zoomSpeed = conf["cam"]["zoomSpeed"];

	fpsMeasureInterval = conf["fpsInterval"];
}


void Config::loadSettings () {
	logger.write ("Loading settings");
	LuaFile *settingsFile = nullptr;
	if (!file::exists (SETTINGS_PATH)) {
		logger.write ("User settings not found, loading default settings");
		settingsFile = new LuaFile (SETTINGS_DEFAULT_PATH);
	}
	else
		settingsFile = new LuaFile (SETTINGS_PATH);
	sol::table settings = settingsFile->state["Settings"];

	screen.size.width = settings["resolution"]["w"];
	screen.size.height = settings["resolution"]["h"];
	screen.fullscreen = settings["fullscreen"];
}

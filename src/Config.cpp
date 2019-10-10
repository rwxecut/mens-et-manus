#include "Config.h"
#include "LuaFile.h"
#include "Logger.h"
#include "auxiliary/filesystem.h"


void Config::load () {
	loadConfig ();
	loadSettings ();
}


void Config::loadConfig () {
	logger.write ("Loading config");
	LuaFile confFile (CONFIG_PATH);
	sol::table conf = confFile.state["Config"];

	path.modfile = conf["path"]["modfile"];
	path.assets = conf["path"]["assets"];
	path.font = conf["path"]["font"];
	path.splash = conf["path"]["splash"];
	path.splashVertShader = conf["path"]["splashVertShader"];
	path.splashFragShader = conf["path"]["splashFragShader"];
	path.mainMenuGUI = conf["path"]["mainMenuGUI"];
	path.gameMenuGUI = conf["path"]["gameMenuGUI"];

	cam.moveSpeedMax = conf["cam"]["moveSpeedMax"];
	cam.moveAcceleration = conf["cam"]["moveAcceleration"];
	cam.zoomSpeed = conf["cam"]["zoomSpeed"];

	fpsMeasureInterval = conf["fpsInterval"];

	fontSize = conf["fontSize"];
}


void Config::loadSettings () {
	logger.write ("Loading settings");
	LuaFile *settingsFile = nullptr;
	if (!fs::exists (SETTINGS_PATH)) {
		logger.write ("User settings not found, loading default settings");
		settingsFile = new LuaFile (SETTINGS_DEFAULT_PATH);
	}
	else
		settingsFile = new LuaFile (SETTINGS_PATH);
	sol::table settings = settingsFile->state["Settings"];

	screen.size.width = settings["resolution"]["w"];
	screen.size.height = settings["resolution"]["h"];
	screen.aspect = (GLdouble) screen.size.width / (GLdouble) screen.size.height;
	screen.fullscreen = settings["fullscreen"];
}

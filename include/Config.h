#pragma once

#include <string>
#include <GL/gl.h>
#include "LuaFile.h"
#include "Logger.h"
#include "auxiliary/geometry.h"
#include "auxiliary/filesystem.h"


#define CONFIG_PATH "../cfg/config.lua"
#define SETTINGS_PATH "../cfg/settings.lua"
#define SETTINGS_DEFAULT_PATH "../cfg/settings_default.lua"


struct Config {
	void load ();
	void loadConfig ();
	void loadSettings ();

	struct {
		size2d<int> size;
		GLdouble aspect;
		bool fullscreen;
	} screen;

	struct {
		std::string modfile;
		std::string assets;
		std::string splash;
		std::string mainMenuGUI;
		std::string gameMenuGUI;
	} path;

	struct {
		GLdouble moveSpeedMax, moveAcceleration;
		GLdouble zoomSpeed;
	} cam;

	GLdouble fpsMeasureInterval;
};

#ifndef CONFIG_IMPLEMENT
extern Config config;
#endif

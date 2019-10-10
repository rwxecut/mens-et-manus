#pragma once

#include "lib/glad.h"
#include <string>
#include "auxiliary/geometry.h"


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
		std::string font;
		std::string splash;
		std::string splashVertShader;
		std::string splashFragShader;
		std::string mainMenuGUI;
		std::string gameMenuGUI;
	} path;

	struct {
		GLdouble moveSpeedMax, moveAcceleration;
		GLdouble zoomSpeed;
	} cam;

	GLdouble fpsMeasureInterval;

	GLfloat fontSize;
};

#ifndef CONFIG_IMPLEMENT
extern Config config;
#endif

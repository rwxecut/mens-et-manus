#pragma once

#include <vector>
#include <SDL.h>
#include "windowState.h"
#include "Logger.h"

// Routines' IDs for Lua
enum {
	finalization,
	gameRoutine,
	mainMenuRoutine
};


class Routine {
public:
	virtual void update (WindowState *winState) = 0;
	virtual void render () = 0;
	virtual void eventHandler (SDL_Event *event) = 0;
};


class RoutineHandler {

	Routine *routine;
	std::vector<Routine *> rTable;

public:
	uint8_t id;

	void assignRoutinesTable (std::vector<Routine *> routineTable);
	bool switchID ();

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};

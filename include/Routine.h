#pragma once

#include <vector>
#include <SDL.h>
#include "nuklear/nuklear_common.h"
#include "Logger.h"

// Routines' IDs for Lua
enum {
	finalization,
	gameRoutine,
	mainMenuRoutine
};


class Routine {
public:
	virtual void update (nk_context *nkContext) = 0;
	virtual void render () = 0;
	virtual void eventHandler (SDL_Event *event) = 0;
};


class RoutineHandler {

	Routine *routine;
	std::vector<Routine *> rTable;

public:
	uint8_t id;


	inline void assignRoutinesTable (std::vector<Routine *> const &routineTable) {
		rTable = routineTable;
	}


	inline bool switchID () {
		if (rTable.at (id)) {
			routine = rTable.at (id);
			return true;
		}
		return false;
	}


	inline void update (nk_context *nkContext) {
		routine->update (nkContext);
	}


	inline void render () {
		routine->render ();
	}


	inline void eventHandler (SDL_Event *event) {
		routine->eventHandler (event);
	}
};

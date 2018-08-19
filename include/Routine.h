#pragma once

#include <vector>
#include <SDL.h>

// Routines' IDs for Lua
enum {
	finalization,
	gameRoutine,
	mainMenuRoutine,
	splashRoutine
};


class Routine {
public:
	virtual void update () = 0;
	virtual void render () = 0;
	virtual void eventHandler (SDL_Event *event) = 0;

	virtual ~Routine () {};
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


	inline void update () {
		routine->update ();
	}


	inline void render () {
		routine->render ();
	}


	inline void eventHandler (SDL_Event *event) {
		routine->eventHandler (event);
	}
};

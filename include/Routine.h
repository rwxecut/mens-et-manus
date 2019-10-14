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
	bool finished = false;

	virtual ~Routine () {};
};


class RoutineHandler {

	Routine *routine;
	std::vector<Routine *> rList;

public:
	uint8_t id;


	inline void assignRoutinesList (std::vector<Routine *> const &routineList) {
		rList = routineList;
	}


	inline bool switchID () {
		if (rList.at (id)) {
			routine = rList.at (id);
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

	inline bool finished () {
		return routine->finished;
	}
};

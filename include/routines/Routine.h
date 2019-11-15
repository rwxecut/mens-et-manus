#pragma once

#include "RoutineFactory.h"
#include <vector>
#include <memory>
#include <SDL.h>


// Routines' IDs
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

	std::unique_ptr<Routine> routine;

public:
	uint8_t id = 0, new_id = 0;


	// Return false if set on finalization or has wrong ID
	inline bool switchID () {
		if (new_id != id) {
			id = new_id;
			routine.reset (newRoutine (id));
			return (routine != nullptr);
		}
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

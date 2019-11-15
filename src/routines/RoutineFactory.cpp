#include "routines/RoutineFactory.h"
#include "routines/Splash.h"
#include "routines/MainMenu.h"
#include "routines/Game.h"


Routine* newRoutine (int id) {
	switch (id) {
		case splashRoutine:
			return new Splash ();
		case mainMenuRoutine:
			return new MainMenu ();
		case gameRoutine:
			return new Game ();
		default:
			return nullptr;
	}
}

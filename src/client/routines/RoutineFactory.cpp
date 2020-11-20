#include "client/routines/RoutineFactory.h"
#include "client/routines/Splash.h"
#include "client/routines/MainMenu.h"
#include "client/routines/Game.h"


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

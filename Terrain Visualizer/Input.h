#ifndef USER_INPUT_HANDLER
#define USER_INPUT_HANDLER

#include <SDL.h>
#include "camera.h"

class Input {

	static const Uint8 *keyState;
	static Uint32 m;

public:

	static float mx, my, lx, ly, dx, dy;
	static bool lb, mb, rb;

	static camera cam;

	static void update();

	static bool key(SDL_Scancode s);

};

#endif
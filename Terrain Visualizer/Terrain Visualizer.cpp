// Terrain Visualizer.cpp : Defines the entry point for the application.
// 

#include "Terrain Visualizer.h"




int main(int argc, char* argv[])
{
	if (argc < 2) {
		throw std::exception("You forgot to use an image as an exec argument!");
	}
	std::cout << "Loading " << argv[1] << "..." << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);

	Input::update();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	SDL_Window* window;

	window = SDL_CreateWindow("Destruction", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	gladLoadGL();

	SDL_GL_SetSwapInterval(1);

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
#endif

	glViewport(0, 0, 1920, 1080);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);


	ParticleBuffer pb;

	bool loop = true;
	std::vector<SDL_Event> events;

	while (!Input::key(SDL_SCANCODE_ESCAPE) && loop) {

		SDL_PumpEvents();
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			events.push_back(e);
		}
		for (SDL_Event& ev : events) {
			if (ev.type == SDL_WINDOWEVENT) {
				switch (ev.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
					loop = false;
					break;
				default:
					break;
				}
			}
		}

		events.clear();

		Input::update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pb.update();

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);

	SDL_HideWindow(window);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;

	return 0;
}

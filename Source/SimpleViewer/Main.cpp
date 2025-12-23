#include <fmt/format.h>
#include <fstream>

#include <SDL3/SDL.h>

#include <BMPFile/BMPFile.hpp>

SDL_Window* window;
SDL_Surface* windowSurface;

const struct {int w, h;} windowSize{.w = 1195, .h = 674};

int main() {
	window = SDL_CreateWindow("Image viewer", windowSize.w, windowSize.h, SDL_WINDOW_OPENGL);
	windowSurface = SDL_GetWindowSurface(window);

	// TO DO: Create a texture and load a texture into it.
	// TO DO: Make a control system with ImGui that: allows a filename to be specified, selecting codec, loading a file, performing random function operations
	SDL_Event currentEvent;
	while (true) {
		SDL_PollEvent(&currentEvent);
		switch (currentEvent.type) {
			case SDL_EVENT_QUIT:
			goto breakLoop;
			default:
			break;
		}
		// Load image into texture
	}
	breakLoop:

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
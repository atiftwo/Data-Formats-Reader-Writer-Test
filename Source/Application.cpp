#include <fmt/format.h>
#include <fstream>

#include <SDL3/SDL.h>

#include <BMPFile/BMPFile.hpp>

SDL_Window* window;
SDL_Surface* windowSurface;

const struct {int w, h;} windowSize{.w = 640, .h = 480};

int main() {
	const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode(0);
	window = SDL_CreateWindow("Image viewer", 640, 480, SDL_WINDOW_OPENGL);
	windowSurface = SDL_GetWindowSurface(window);

	SDL_Event currentEvent;
	while (true) {
		SDL_PollEvent(&currentEvent);
		switch (currentEvent.type) {
			case SDL_EVENT_QUIT:
			goto breakLoop;
			default:
			break;
		}

		SDL_LockSurface(windowSurface);
		SDL_memset(windowSurface->pixels, 128, windowSurface->h*windowSurface->pitch);
		SDL_UnlockSurface(windowSurface);
		SDL_UpdateWindowSurface(window);
	}
	breakLoop:

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
#include "SDL.h"

int main(int argc, char *argv[])
{

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* Window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
	
	SDL_Event event;
	bool appIsRunning = true;

	while (appIsRunning) 
	{


		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) 
			{
				appIsRunning = false;
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_o:
					break;
				case SDLK_RIGHT:
					break;
				}
			}
		}
	}

	return 0;
}
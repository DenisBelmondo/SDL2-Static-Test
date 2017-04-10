#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
	unsigned int tics = 0;
	
	const unsigned int TICRATE = 1000 / 35;

	const unsigned int WIDTH = 64;
	const unsigned int HEIGHT = 64;
	
	const unsigned int SCALE_X = 4;
	const unsigned int SCALE_Y = 4;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow(
		"TESTING TESTING",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_OPENGL
	);
	
	if (window == NULL) {
		SDL_Log("Ahhh SHIT! %s\n", SDL_GetError());
		return 1;
	}
	
	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED
	);
	
	SDL_SetWindowSize(window, WIDTH * SCALE_X, HEIGHT * SCALE_Y);
	SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
	
	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGB888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH, HEIGHT
	);
	
	while(1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		
		if (tics == 0 || tics % TICRATE == 0) {
			SDL_SetRenderTarget(renderer, texture);
			
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			
			srand(clock());
			
			SDL_SetRenderDrawColor(
				renderer,
				rand() % 255,
				rand() % 255,
				rand() % 255,
				255
			);
			
			for(int i = 0; i < WIDTH; ++i) {
				for(int j = 0; j < HEIGHT; ++j) {
					if (rand() % 2 == 0) {
						SDL_RenderDrawPoint(renderer, i, j);
					}
				}
			}
			
			SDL_RenderPresent(renderer);
		} SDL_Delay(1); tics++;
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}

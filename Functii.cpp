#include"MainHeader.h"


bool init(int& latime, int& lungime)	//Initialize SDL
{
	bool success = true;	//Initialization flag
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		SDL_ShowCursor(SDL_DISABLE);//ascundere mouse in fereastra
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Create window
		Uint32 steaguri = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN;//steaguri
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, NULL, NULL, steaguri);
		if (gWindow == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);			//Create renderer for window
			if (gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				if (SDL_RenderSetVSync(gRenderer, 1)){
					printf("Vsync nu a fost pornit!\n");
					//success = false;
				}
				SDL_GetRendererOutputSize(gRenderer, &latime, &lungime);
				printf("latime: %d\nlungime: %d\n", latime, lungime);//printare marime fereastra creata
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);				//Initialize renderer color 
				int imgFlags = IMG_INIT_PNG;				//Initialize PNG loading
				if (!(IMG_Init(imgFlags) & imgFlags)){
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void close(){
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

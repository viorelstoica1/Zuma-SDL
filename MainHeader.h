#ifndef _TEST_H
#define _TEST_H

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Spritesheet.h"
#include "Textura.h"

extern SDL_Window* gWindow;//The window we'll be rendering to
extern SDL_Renderer* gRenderer;//The window renderer

//Starts up SDL and creates window
bool init(int &latime, int &lungime);

//Frees media and shuts down SDL
void close();

#endif
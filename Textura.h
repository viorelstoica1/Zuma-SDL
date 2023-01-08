#ifndef _TEXTURA_H
#define _TEXTURA_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
//#include "MainHeader.h"

class Textura{
private:
	int marime_x, marime_y;//marime textura
	SDL_Texture* tex;//pointer la textura propriu zisa
public:
	Textura(const char* s);
	~Textura();
	SDL_Texture* GetTex();
	int GetMarimeX();
	int GetMarimeY();
};

#endif
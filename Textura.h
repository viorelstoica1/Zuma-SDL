#ifndef _TEXTURA_H
#define _TEXTURA_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "GameObject.h"

extern SDL_Renderer* gRenderer;

class Textura: virtual public GameObject{
private:
	int marime_x, marime_y;//marime textura
	SDL_Texture* tex;//pointer la textura propriu zisa
public:
	Textura(const char* s, float poz_x, float poz_y, float angel) :GameObject(poz_x, poz_y, angel) {
		tex = IMG_LoadTexture(gRenderer, s);
		if (!tex) {
			printf("Nu am putut incarca textura %s!\n", s);
			marime_x = marime_y = 0;
		}
		else {
			SDL_QueryTexture(tex, NULL, NULL, &marime_x, &marime_y);
			printf("Am incarcat textura %s cu latimea %d si inaltimea %d\n", s, marime_x, marime_y);
		}
	}
	~Textura();
	SDL_Texture* GetTex();
	int GetMarimeX();
	int GetMarimeY();
	virtual int CenterX();
	int CenterY();
};

#endif
#ifndef _SPRITESHEET_H
#define _SPRITESHEET_H


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Textura.h"

class Spritesheet : public Textura {
private:
	unsigned int numar_cadre;
	unsigned int cadru_curent;
	//vector de pozitii ale cadrelor din spritesheet
	//presupune un spritesheet orizontal, cu cadre de marime egala!!
	SDL_Rect* pozitii_cadre;
public:
	Spritesheet(const char* s, unsigned int nrcadre, int poz_x, int poz_y, float angel) : Textura(s,poz_x, poz_y,angel),GameObject(poz_x,poz_y,angel) {
		numar_cadre = nrcadre;
		cadru_curent = 0;
		pozitii_cadre = new SDL_Rect[numar_cadre];
		for (unsigned int i = 0;i < numar_cadre;i++){
			pozitii_cadre[i].x = (this->GetMarimeX() / numar_cadre) * i;
			pozitii_cadre[i].y = 0;
			pozitii_cadre[i].w = this->GetMarimeX()/numar_cadre;
			pozitii_cadre[i].h = this->GetMarimeY();
		}
		printf("Am construit un spritesheet cu %d cadre\n", numar_cadre);
	}
	~Spritesheet();
	int GetMarimeSpriteX();
	int GetMarimeSpriteY();
	SDL_Rect* GetCadruCurent();
	void SetCadru(int x);
	void CresteCadru();
	void ScadeCadru();
	int CenterX();
};


#endif
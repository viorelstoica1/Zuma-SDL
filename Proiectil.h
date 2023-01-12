#ifndef _PROIECTIL_H
#define _PROIECTIL_H

#include"MovingObject.h"
#include"Textura.h"
#include"Spritesheet.h"

enum tipProiectil{
	Ball,Powerup,Bani
};

class Proiectil : public Spritesheet, public MovingObject {
private:
	tipProiectil projectil;

public:
	Proiectil(tipProiectil x,/*const char**/ SDL_Texture* s, float poz_x, float poz_y, float angel) :Spritesheet(s,8,poz_x, poz_y, angel), MovingObject(poz_x,poz_y, angel), GameObject(poz_x, poz_y, angel) {
		projectil = x;//todo printf
	};
	~Proiectil() {};
	tipProiectil GetTipProiectil();
};









#endif

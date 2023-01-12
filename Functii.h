#ifndef _FUNCTII_H
#define _FUNCTII_H

#include"GameObject.h"
struct mouse {//struct coord mouse
	int maus_x, maus_y;
};

//returneaza distanta la patrat dintre 2 puncte(pt coliziuni)
float DistantaPatrat(float xa, float xb, float ya, float yb);

//Starts up SDL and creates window
bool init(int& latime, int& lungime);

//Frees media and shuts down SDL
void close();

void Render();

void AlocareTraseuBile(GameObject* &s);

void StergereTraseu(GameObject* s);

bool DirectieColiziune(GameObject* membru, GameObject* de_introdus);

SDL_Texture* GetRandomBila(SDL_Texture** s);

void AlocareTexturi(SDL_Texture** &s);

void DealocareTexturi(SDL_Texture** &s);
#endif
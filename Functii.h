#ifndef _FUNCTII_H
#define _FUNCTII_H

#include"GameObject.h"
struct mouse {//struct coord mouse
	int maus_x, maus_y;
};
struct CuloriBile {
	SDL_Texture** TexturiBile;
	int* NumarBile;
};
extern CuloriBile* bilute;

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

SDL_Texture* GetRandomBila();

SDL_Texture* GetRandomBilaExistenta();

void AlocareTexturi();

void DealocareTexturi();

void ScadereNumarBileExistente(SDL_Texture * p);

void CresteNumarBileExistente(SDL_Texture* p);

void CitireConfig(const char* configname, int& nr_bile, float& viteza_sir_intrare, float& viteza_sir_generala, float& viteza_proiectil_tun);
#endif
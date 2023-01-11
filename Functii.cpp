#include"Functii.h"

#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include"GameObject.h"
SDL_Window* gWindow = NULL;//The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;//The window renderer
int frame = 0;
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

float DistantaPatrat(float xa,float xb, float ya, float yb){
	xa -= xb;
	ya -= yb;
	return xa * xa + ya * ya;
}

void Render() {

}
//primeste un pointer si returneaza sir de Gameobject ca traseu pt bile
void AlocareTraseuBile(GameObject* &s) {
	s = new GameObject[7000];//6682
	int i;float x, y;
	for (i = 0;i < 50;i++) {
		s[i].SetCoordX(700);
		s[i].SetCoordY(i);
		s[i].SetUnghi(1.57);
	}
	for (float unghi = 3.14;unghi > 1.57;unghi = unghi-0.01) {
		s[i].SetCoordX(cos(unghi) * 100 + 800);
		s[i].SetCoordY(sin(unghi) * 100 + 50);
		i++;
		s[i].SetUnghi(unghi - 1.57);
	}
	for (int j = 800;j < 1600;j++) {
		s[i].SetCoordX(j);
		s[i].SetCoordY(150);
		i++;
	}
	for (float unghi = 4.71;unghi < 6.28;unghi = unghi + 0.005) {
		s[i].SetCoordX(cos(unghi) * 200 + 1600);
		s[i].SetCoordY(sin(unghi) * 200 + 350);
		i++;
		s[i].SetUnghi(unghi - 4.71);
	}
	for (int j = 350;j < 750;j++) {
		s[i].SetCoordX(1800);
		s[i].SetCoordY(j);
		i++;
		s[i].SetUnghi(1.57);
	}
	for (float unghi = 0;unghi < 1.57;unghi = unghi + 0.005) {
		s[i].SetCoordX(cos(unghi) * 200 + 1600);//inmultesti cu raza cercului
		s[i].SetCoordY(sin(unghi) * 200 + 750);//si aduni cu centrul cercului
		i++;
		s[i].SetUnghi(unghi + 1.57);
	}
	for (int j = 1600;j > 800;j--) {
		s[i].SetCoordX(j);
		s[i].SetCoordY(950);
		i++;
		s[i].SetUnghi(3.14);
	}
	for (float unghi = 1.57;unghi < 3.14;unghi = unghi + 0.01) {
		s[i].SetCoordX(cos(unghi) * 100 + 800);
		s[i].SetCoordY(sin(unghi) * 100 + 850);
		i++;
		s[i].SetUnghi(unghi +1.57);
	}
	for (int j = 850;j > 500;j--) {
		s[i].SetCoordX(700);
		s[i].SetCoordY(j);
		i++;
		s[i].SetUnghi(4.71);
	}
	for (float unghi = 3.14;unghi < 6.28;unghi = unghi + 0.01) {
		s[i].SetCoordX(cos(unghi) * 100 + 800);
		s[i].SetCoordY(sin(unghi) * 100 + 500);
		i++;
		s[i].SetUnghi(unghi+1.57);
	}
	for (int j = 500;j < 750;j++) {
		s[i].SetCoordX(900);
		s[i].SetCoordY(j);
		i++;
		s[i].SetUnghi(1.57);
	}
	for (float unghi = 3.14;unghi > 1.57;unghi = unghi - 0.01) {
		s[i].SetCoordX(cos(unghi) * 100 + 1000);
		s[i].SetCoordY(sin(unghi) * 100 + 750);
		i++;
		s[i].SetUnghi(unghi-1.57);
	}
	for (int j = 1000;j < 1600;j++) {
		s[i].SetCoordX(j);
		s[i].SetCoordY(850);
		i++;
	}
	for (float unghi = 1.57;unghi > 0;unghi = unghi - 0.01) {
		s[i].SetCoordX(cos(unghi) * 100 + 1600);//inmultesti cu raza cercului
		s[i].SetCoordY(sin(unghi) * 100 + 750);//si aduni cu centrul cercului
		i++;
		s[i].SetUnghi(unghi-1.57);
	}
	for (int j = 750;j > 400;j--) {
		s[i].SetCoordX(1700);
		s[i].SetCoordY(j);
		i++;
		s[i].SetUnghi(4.71);
	}
	for (float unghi = 6.28;unghi > 4.71;unghi = unghi -0.01) {
		s[i].SetCoordX(cos(unghi) * 100 + 1600);
		s[i].SetCoordY(sin(unghi) * 100 + 400);
		i++;
		s[i].SetUnghi(unghi - 1.57);
	}
	for (int j = 1600;j > 250;j--) {
		s[i].SetCoordX(j);
		s[i].SetCoordY(300);
		i++;
		s[i].SetUnghi(3.14);
	}
	printf("Traseul are %d puncte\n", i);
}
//dealoca sirul de puncte
void StergereTraseu(GameObject* s) {
	delete[] s;
	s = 0;
}
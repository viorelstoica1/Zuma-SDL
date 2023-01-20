#include"Functii.h"

#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<cstdlib>
#include"GameObject.h"
#include <time.h>
#include<fstream>
#include<string>
#include<iostream>
SDL_Window* gWindow = NULL;//The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;//The window renderer
int frame = 0;
int nr_culori;
int latime = 0, lungime = 0;//marime ecran creat, setate de functia init
bool init(int& latime, int& lungime)	//Initialize SDL
{
	srand(time(0));
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
	int i = 0;
	for (int j = -50;j < 50;j++) {
		s[i].SetCoordX(700);
		s[i].SetCoordY(j);
		s[i].SetUnghi(1.57);
		i++;
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
//foloseste o matrice de rotatie pentru a verifica directia coliziunii la orice unghi
bool DirectieColiziune(GameObject* membru, GameObject* de_introdus) {
	float x1, x2;
	x1 = cos(membru->GetUnghi() * -1) * membru->GetCoordX() - sin(membru->GetUnghi() * -1) * membru->GetCoordY();
	x2 = cos(membru->GetUnghi() * -1) * de_introdus->GetCoordX() - sin(membru->GetUnghi() * -1) * de_introdus->GetCoordY();
	if (x1 > x2) {
		printf("Obuzul rotit are pozitia %f iar bila rotita are pozitia %f, la unghiul %f, introduc in stanga", x2, x1, membru->GetUnghi() * 180 / 3.14);
		return 0;//stanga
	}
	else {
		printf("Obuzul rotit are pozitia %f iar bila rotita are pozitia %f, la unghiul %f, introduc in dreapta", x2, x1, membru->GetUnghi() * 180 / 3.14);
		return 1;//dreapta
	}
}

SDL_Texture* GetRandomBila() {
	int aux = rand() % nr_culori;
	printf("Random: %d\n", aux);
	bilute->NumarBile[aux]++;
	return bilute->TexturiBile[aux];
}

SDL_Texture* GetRandomBilaExistenta()//pentru tun
{
	int aux = 0;
	do {
		aux = rand() % nr_culori;
	} while (bilute->NumarBile[aux] == 0);
	printf("Random: %d, %d bile\n", aux,bilute->NumarBile[aux]);
	return bilute->TexturiBile[aux];
}

void AlocareTexturi(){
	SDL_Texture* TexBilaRosie = IMG_LoadTexture(gRenderer, "grafici/Bila_Rosu_Viorel-Sheet.png");
	SDL_Texture* TexBilaNeagra = IMG_LoadTexture(gRenderer, "grafici/Bila_Negru_Viorel-Sheet.png");
	SDL_Texture* TexBilaVerde = IMG_LoadTexture(gRenderer, "grafici/Bila_Verde_Viorel-Sheet.png");
	SDL_Texture* TexBilaMov = IMG_LoadTexture(gRenderer, "grafici/Bila_Mov_Viorel-Sheet.png");
	SDL_Texture* TexBilaAlbastru = IMG_LoadTexture(gRenderer, "grafici/Bila_Albastru_Viorel-Sheet.png");
	SDL_Texture* TexBilaAlb = IMG_LoadTexture(gRenderer, "grafici/Bila_Alb_Viorel-Sheet.png");
	SDL_Texture* TexBilaGalben = IMG_LoadTexture(gRenderer, "grafici/Bila_Galben_Viorel-Sheet.png");
	SDL_Texture* TexBilaPortocaliu = IMG_LoadTexture(gRenderer, "grafici/Bila_Portocaliu_Viorel-Sheet.png");
	bilute = new CuloriBile;
	bilute->TexturiBile = new SDL_Texture*[8];
	bilute->TexturiBile[0] = TexBilaAlbastru;
	if (!bilute->TexturiBile[0])
		printf("Nu am putut incarca culoarea 0 !\n");
	bilute->TexturiBile[1] = TexBilaMov;
	if (!bilute->TexturiBile[1])
		printf("Nu am putut incarca culoarea 1\n");
	bilute->TexturiBile[2] = TexBilaNeagra;
	if (!bilute->TexturiBile[2])
		printf("Nu am putut incarca culoarea 2\n");
	bilute->TexturiBile[3] = TexBilaRosie;
	if (!bilute->TexturiBile[3])
		printf("Nu am putut incarca culoarea 3\n");
	bilute->TexturiBile[4] = TexBilaVerde;
	if (!bilute->TexturiBile[4])
		printf("Nu am putut incarca culoarea 4\n");
	bilute->TexturiBile[5] = TexBilaAlb;
	if (!bilute->TexturiBile[5])
		printf("Nu am putut incarca culoarea 5\n");
	bilute->TexturiBile[6] = TexBilaPortocaliu;
	if (!bilute->TexturiBile[6])
		printf("Nu am putut incarca culoarea 6\n");
	bilute->TexturiBile[7] = TexBilaGalben;
	if (!bilute->TexturiBile[7])
		printf("Nu am putut incarca culoarea 7\n");
	bilute->NumarBile = new int[8];
	for (int i = 0;i < 8;i++) {
		bilute->NumarBile[i] = 0;
	}
}

void DealocareTexturi(){
	for (int i = 0;i < 8;i++) {
		SDL_DestroyTexture(bilute->TexturiBile[i]);
		bilute->TexturiBile[i] = 0;
	}
	delete[] bilute->TexturiBile;
	delete[] bilute->NumarBile;
	delete bilute;
}

void CresteNumarBileExistente(SDL_Texture* p) {
	int i;
	for (i = 0;i < nr_culori;i++) {
		if (bilute->TexturiBile[i] == p) {
			bilute->NumarBile[i]++;
		}
	}
	printf("Am crescut nr de bile %d\n", i);
}

void CitireConfig(const char* configname, int& nr_bile, float& viteza_sir_intrare, float& viteza_sir_generala, float& viteza_proiectil_tun)
{
	//o linie din config
	std::string linie_config;
	// Read from the text file
	std::ifstream configu(configname);
	if (configu.is_open()) {
		printf("Am gasit configurarile!\n");
		// Use a while loop together with the getline() function to read the file line by line
		while (getline(configu, linie_config,' ') /*&& !configu.eof()*/) {
			std::cout << linie_config<<std::endl;
			if (linie_config.compare("viteza_sir_intrare") == 0) {
				configu >> viteza_sir_intrare;
				printf("Viteza de intrare citita este %f\n", viteza_sir_intrare);
				getline(configu, linie_config);
			}
			else if (linie_config.compare("viteza_sir_generala") == 0) {
				configu >> viteza_sir_generala;
				printf("Viteza de sir generala este %f\n", viteza_sir_generala);
				getline(configu, linie_config);
			}
			else if (linie_config.compare("viteza_proiectil_tun") == 0) {
				configu >> viteza_proiectil_tun;
				printf("Viteza de proiectil tun este %f\n", viteza_proiectil_tun);
				getline(configu, linie_config);
			}
			else if (linie_config.compare("nr_bile") == 0) {
				configu >> nr_bile;
				printf("Numarul de bile este %d\n", nr_bile);
				getline(configu, linie_config);
			}
			std::cout << "\nUrmatorul sir:\n";
		}

		// Close the file
		configu.close();
	}
	else {
		printf("Nu am putut incarca configurarile!\n");
	}

}

void ScadereNumarBileExistente(SDL_Texture* p){
	int i;
	for ( i = 0;i < nr_culori;i++) {
		if (bilute->TexturiBile[i] == p) {
			bilute->NumarBile[i]--;
		}
	}
	printf("Am scazut nr de bile %d\n", i);
}

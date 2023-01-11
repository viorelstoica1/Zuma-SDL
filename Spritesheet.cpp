#include"Spritesheet.h"
extern int frame;
Spritesheet::~Spritesheet()
{
	if (pozitii_cadre)
	{
		delete[] pozitii_cadre;
		pozitii_cadre = 0;
	}
	numar_cadre = 0;
	cadru_curent = 0;
}

int Spritesheet::GetMarimeSpriteX()
{
	return this->GetMarimeX()/numar_cadre;
}

int Spritesheet::GetMarimeSpriteY()
{
	return this->GetMarimeY();
}

int Spritesheet::GetNrCadre()
{
	return numar_cadre;
}

SDL_Rect* Spritesheet::GetCadruCurent()
{
	return &pozitii_cadre[cadru_curent];
}

void Spritesheet::SetCadru(int x)
{
	cadru_curent = x;
}

void Spritesheet::CresteCadru()
{
	if (cadru_curent == numar_cadre - 1)
	{
		cadru_curent = 0;
	}
	else cadru_curent++;
}

void Spritesheet::ScadeCadru()
{
	if (cadru_curent == 0)
	{
		cadru_curent = numar_cadre-1;
	}
	else cadru_curent--;
}

int Spritesheet::CenterX()
{
	return this->GetCoordX() - this->GetMarimeSpriteX()/2;
}

void Spritesheet::RenderCenter(){
	SDL_Rect poz_randat = { this->CenterX(),this->CenterY(),this->GetMarimeSpriteX(),this->GetMarimeSpriteY() };
	SDL_RenderCopy(gRenderer, this->GetTex(), this->GetCadruCurent(), &poz_randat);//Render texture to screen
}

int Spritesheet::HitboxX()
{
	return this->GetMarimeX() / numar_cadre;
}

int Spritesheet::HitboxY()
{
	return this->GetMarimeY();
}

void Spritesheet::Update(){
	this->SetCadru(frame / this->GetNrCadre());
}

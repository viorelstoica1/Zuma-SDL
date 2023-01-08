#include"Spritesheet.h"

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


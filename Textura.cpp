#include"Textura.h"

extern SDL_Renderer *gRenderer;


Textura::~Textura(){
	if (tex){
		SDL_DestroyTexture(tex);
		tex = 0;
	}
	marime_x = 0;
	marime_y = 0;
}

SDL_Texture* Textura::GetTex()
{
	return tex;
}

int Textura::GetMarimeX()
{
	return marime_x;
}

int Textura::GetMarimeY()
{
	return marime_y;
}

int Textura::CenterX()
{
	return this->GetCoordX()-this->GetMarimeX()/2;
}

int Textura::CenterY()
{
	return this->GetCoordY() - this->GetMarimeY()  / 2;
}

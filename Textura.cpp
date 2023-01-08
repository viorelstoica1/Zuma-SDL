#include"Textura.h"

extern SDL_Renderer *gRenderer;
Textura::Textura(const char* s){
	tex = IMG_LoadTexture(gRenderer, s);
	if (!tex){
		printf("Nu am putut incarca textura %s!\n", s);
		marime_x = marime_y = 0;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &marime_x, &marime_y);
		printf("Am incarcat textura %s cu latimea %d si inaltimea %d\n", s, marime_x, marime_y);
	}
}

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

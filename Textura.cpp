#include"Textura.h"

extern SDL_Renderer *gRenderer;


Textura::~Textura(){
	/*if (tex){
		SDL_DestroyTexture(tex);
		tex = 0;
	}*/
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
//"centrul" unei texturi, folosit doar la randat!!
int Textura::CenterX()
{
	return this->GetCoordX() - this->GetMarimeX()/2;
}
//"centrul" unei texturi, folosit doar la randat!!
int Textura::CenterY()
{
	return this->GetCoordY() - this->GetMarimeY()  / 2;
}

void Textura::Render(){
	SDL_Rect poz_randat = { this->GetCoordX(),this->GetCoordY(),this->GetMarimeX(),this->GetMarimeY() };
	SDL_RenderCopy(gRenderer, this->GetTex(), NULL, &poz_randat);//Render texture to screen
}

void Textura::RenderCenter(){
	SDL_Rect poz_randat = { this->CenterX(),this->CenterY(),this->GetMarimeX(),this->GetMarimeY() };
	SDL_RenderCopyEx(gRenderer, this->GetTex(), NULL, &poz_randat, this->GetUnghi() * 180 / 3.14 + 90, NULL, SDL_FLIP_NONE);
}

int Textura::HitboxX(){
	return marime_x;
}

int Textura::HitboxY(){
	return marime_y;
}

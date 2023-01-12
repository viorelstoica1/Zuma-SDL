#ifndef _BILA_H
#define _BILA_H

#include"Spritesheet.h"

enum culoare {
	Rosu,Albastru,Verde,Mov,Negru
};
class Bila : public Spritesheet {
private:
	int index;//indexul vectorului de puncte(pentru pozitie)
	float viteza;//prefer viteza asa pentru a putea itera prin vectorul de pozitii 
	culoare _culoare;//pentru a testa egalitatea intre bile
	Bila* urmatoare, *anterioara;
public:
	Bila(float vit,culoare c,int i,/*const char**/ SDL_Texture* s, unsigned int nrcadre, float poz_x, float poz_y, float angel) : Spritesheet(s, nrcadre, poz_x, poz_y, angel) , GameObject(poz_x, poz_y, angel) {
		_culoare = c;
		index = i;
		viteza = vit;
		urmatoare = anterioara = 0;
	};
	~Bila() { index = 0; };
	int GetIndex() { return index; };
	void SetIndex(int i) { index = i; };
	float GetViteza() { return viteza; };
	void SetViteza(float vit) { viteza = vit; };
	culoare GetCuloare() { return _culoare; };
	void SetBilaStanga(Bila* membru);
	void SetBilaDreapta(Bila* membru);
	Bila* GetBilaStanga();
	Bila* GetBilaDreapta();
	void CresteNumar(int i);
	void ScadeNumar(int i);
	int GetNumar();
	void SetNumar(int i);
};








#endif
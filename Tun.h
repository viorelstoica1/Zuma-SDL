#ifndef _TUN_H
#define _TUN_H

#include"Textura.h"
#include"Proiectil.h"
#include"Functii.h"
class Tun : public Textura {
private:
	Proiectil* p_curent, * p_rezerva;//doar o referinta, nu alocam memorie
	bool gata_de_tras;//1 pregatit de tras, 0 nu e gata
	int viteza_tragere;
public:
	Tun(int viteza, SDL_Texture* s, float poz_x, float poz_y, float angel) :Textura(s, poz_x, poz_y,angel) , GameObject(poz_x, poz_y, angel) {
		p_curent = 0;
		viteza_tragere = viteza;
		p_rezerva = 0;
		gata_de_tras = 1;
	}
	~Tun();
	void SetGataTras(bool x) { gata_de_tras = x; };
	bool GataDeTras() { return gata_de_tras; };
	Proiectil* GetProiectilIncarcat();
	void SetProiectilCurent(Proiectil* p);
	void SetProiectilRezerva(Proiectil* p);
	void CicleazaProiectil();
	void Update(mouse *soricel);
	void Trage(mouse* soricel);
	void TerminatTras();
	int GetVitezaTragere();
	SDL_Texture** GetListaTexturi();
	void RenderProiectile();
	void SchimbaOrdineProiectile();
};


#endif
#ifndef _TUN_H
#define _TUN_H

#include"Textura.h"
#include"Proiectil.h"

class Tun : public Textura {
private:
	Proiectil* p_curent, * p_rezerva;//doar o referinta, nu alocam memorie
	bool gata_de_tras;
public:
	Tun(const char* s, float poz_x, float poz_y, float angel) :Textura(s, poz_x, poz_y,angel) , GameObject(poz_x, poz_y, angel) {
		p_curent = 0;
		p_rezerva = 0;
		gata_de_tras = 1;
	}
	~Tun();
	void SetGataTras(bool x) { gata_de_tras = x; };
	bool GataDeTras() { return gata_de_tras; };
};


#endif
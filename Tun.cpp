#include"Tun.h"

Tun::~Tun(){
	p_curent = 0;
	p_rezerva = 0;
	gata_de_tras = 0;
}

Proiectil* Tun::GetProiectilIncarcat(){
	return p_curent;
}

void Tun::SetProiectilCurent(Proiectil* p){
	p_curent = p;
}

//void Tun::CicleazaProiectil(){
//	Proiectil* aux = p_curent;
//	p_curent = p_rezerva;
//	p_rezerva = aux;
//}

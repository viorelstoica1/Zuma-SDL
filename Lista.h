#ifndef _LISTA_H
#define _LISTA_H

#include"Bila.h"
#include"Proiectil.h"
#include"Tun.h"
class Lista {
private:
	Bila* Cap, *Coada;//doar pointeri,nu lucrez pe memorie
	int marime;//cate bile am in sir
	float viteza, acceleratie,viteza_max;//pentru miscarea bilelor
	GameObject* traseu;//vector cu traseul bilelor
public:
	Lista(GameObject* s) { traseu = s; Cap = 0; Coada = 0; marime = 0; viteza = 5;acceleratie = 0; viteza_max = 0; }
	~Lista() { traseu = 0; };
	//adauga un obiect existent
	void adaugaLaStangaListei(Bila* de_introdus);
	//adauga un obiect existent
	void adaugaDreapta(Bila* membru, Bila* de_introdus);
	void adaugaStanga(Bila* membru, Bila* de_introdus);
	//parcurge lista si verifica coliziunea pana da de una sau pana nu mai are bile
	//returneaza bila cu care a dat collide, 0 daca nu
	Bila* TestColiziune(Proiectil* obuz);
	//sterge bila data ca parametru si reface legaturile listei
	void stergeBila(Bila* membru);
	//Creeaza un obiect nou bila
	Bila* CreeazaBila(Proiectil* obuz);
	//daca adauga la stanga ret 0, la dreapta ret 1
	bool adaugaPeElement(Bila* membru, Bila* de_introdus);
	//functie stergere elemente listaa
	void StergereLista();
	void RenderList();
	void Update(Tun* Tunar);
	bool CheckColiziuneBila(Bila* membru, Proiectil* obuz);
};



#endif
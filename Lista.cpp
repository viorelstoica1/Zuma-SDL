#include"Lista.h"
#include"Functii.h"
extern int frame;
void Lista::adaugaLaStangaListei(Bila* de_introdus){
	de_introdus->SetBilaDreapta(Cap);
	if (Cap) {//daca lista nu e goala
		Cap->SetBilaStanga(de_introdus);
		Cap = de_introdus;
	}
	else{//daca lista e goala
		Cap = de_introdus;
		Coada = de_introdus;
	}
	marime++;
	printf("Am adaugat element la inceputul listei, marime: %d\n",marime);
}
//presupunem ca pointerul membru nu este zero !!
void Lista::adaugaDreapta(Bila* membru, Bila* de_introdus){
	de_introdus->SetBilaStanga(membru);
	de_introdus->SetBilaDreapta(membru->GetBilaDreapta());
	if (Coada == membru) {
		Coada = de_introdus;
	}
	else {
		membru->GetBilaDreapta()->SetBilaStanga(de_introdus);
	}
	membru->SetBilaDreapta(de_introdus);
	marime++;
}
//presupunem ca pointerul membru nu este zero !!
void Lista::adaugaStanga(Bila* membru, Bila* de_introdus){
	de_introdus->SetBilaDreapta(membru);
	de_introdus->SetBilaStanga(membru->GetBilaStanga());
	if (Cap == membru) {
		Cap = de_introdus;
	}
	else {
		membru->GetBilaStanga()->SetBilaDreapta(de_introdus);
	}
	membru->SetBilaStanga(de_introdus);
	marime++;
}
//verifica daca trebuie adaugat in stanga sau in dreapta si adauga
bool Lista::adaugaPeElement(Bila* membru, Bila* de_introdus){	
	if (de_introdus->GetCoordX() > membru->GetCoordX()) {//deocamdata las inserarea fara sa tin cont de unghi
		this->adaugaDreapta(membru, de_introdus);
		return 1;
	}
	else {
		this->adaugaStanga(membru, de_introdus);
		return 0;
	}
}

void Lista::StergereLista(){
	Bila* index = Cap;
	int x = 0;
	while (index) {
		Bila* aux = index->GetBilaDreapta();
		stergeBila(index);
		marime--;
		index = aux;
		x++;
	}
	printf("Am sters lista cu %d elemente\n",x);
}

void Lista::RenderList(){
	Bila* index = Cap;
	while (index) {
		index->RenderCenter();
		index = index->GetBilaDreapta();
	}
}

void Lista::Update(Tun* Tunar){
	Bila* index = Cap;
	bool collided = 0;
	while (index) {
		index->Update();
		index->CresteNumar(1);
		if (collided) {//nu stiu unde trebuie sincer
			index->CresteNumar(index->GetMarimeSpriteX());
		}
		index->Copiaza(&traseu[index->GetIndex()]);
		if (CheckColiziuneBila(index, Tunar->GetProiectilIncarcat())) {
			Bila* noua = this->CreeazaBila(Tunar->GetProiectilIncarcat());
			if (this->adaugaPeElement(index, noua)) {//dreapta
				//mutam noua bila la locul ei
				noua->SetIndex(index->GetIndex() + index->GetMarimeSpriteX() );
				printf("Coliziune dreapta!\n");
			}
			else {//stanga
				noua->SetIndex(index->GetIndex() + 1);//plus viteza sirului, 1 temporar
				printf("Coliziune stanga!\n");
			}
			index = noua;
			noua->Copiaza(&traseu[noua->GetIndex()]);
			Tunar->GetProiectilIncarcat()->SetCoordX(Tunar->GetCoordX());
			Tunar->GetProiectilIncarcat()->SetCoordY(Tunar->GetCoordY());
			Tunar->GetProiectilIncarcat()->SetViteza(0, 0);
			Tunar->SetGataTras(1);
			collided = 1;
		}
		//index->CresteNumar(1);//pozitia lui CresteNumar posibil inainte de coliziune
		if (index->GetIndex() > 7000) {
			index->SetIndex(0);
		}
		index = index->GetBilaDreapta();
	}
	frame++;
	if (frame >= Cap->GetNrCadre() * 8) {
		frame = 0;
	}
}
bool Lista::CheckColiziuneBila(Bila* membru, Proiectil* obuz){
	if (DistantaPatrat(obuz->GetCoordX(), membru->GetCoordX(), obuz->GetCoordY(), membru->GetCoordY()) <= pow((obuz->GetMarimeX() + (float)membru->GetMarimeSpriteX()) / 2, 2)) {
		printf("Coliziune!\n");
		return true;
	}
	return false;
}
//parcurge lista si returneaza obiectul cu care s-a facut coliziunea
Bila* Lista::TestColiziune(Proiectil* obuz){
	Bila* index = Cap;
	while (index){
		//verificare coliziune
		if (DistantaPatrat(obuz->GetCoordX(), index->GetCoordX(), obuz->GetCoordY(), index->GetCoordY()) <= pow((obuz->GetMarimeX() + (float)index->GetMarimeSpriteX())/2, 2)) {
			printf("Coliziune!\n");
			return index;
		}
		index = index->GetBilaDreapta();
	}
	return index;//returnare coliziune gasita
}

void Lista::stergeBila(Bila* membru){
	if (membru->GetBilaStanga()){
		membru->GetBilaStanga()->SetBilaDreapta(membru->GetBilaDreapta());
	}
	if (membru->GetBilaDreapta()){
		membru->GetBilaDreapta()->SetBilaStanga(membru->GetBilaStanga());
	}
	membru->SetBilaDreapta(0);
	membru->SetBilaStanga(0);
	delete membru;
	membru = 0;
}

Bila* Lista::CreeazaBila(Proiectil* obuz){
	Bila* aux = new Bila(0, Rosu, 0, "grafici/Bila_Rosu_Viorel-Sheet.png", 8, obuz->GetCoordX(), obuz->GetCoordY(),obuz->GetUnghi());
	return aux;
	printf("Am creat o bila\n");
}



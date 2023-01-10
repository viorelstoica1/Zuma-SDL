#include"Lista.h"
#include"Functii.h"

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
	membru->SetBilaDreapta(de_introdus);
	if (Coada == membru) {
		Coada = de_introdus;
	}
	marime++;
}
//presupunem ca pointerul membru nu este zero !!
void Lista::adaugaStanga(Bila* membru, Bila* de_introdus){
	de_introdus->SetBilaDreapta(membru);
	de_introdus->SetBilaStanga(membru->GetBilaStanga());
	membru->SetBilaStanga(de_introdus);
	if (Cap == membru) {
		Cap = de_introdus;
	}
	marime++;
}
//verifica daca trebuie adaugat in stanga sau in dreapta si adauga
bool Lista::adaugaPeElement(Bila* membru, Bila* de_introdus){	
	if (de_introdus->GetCoordX() > membru->GetCoordX()) {//deocamdata las inserarea fara sa tin cont de unghi
		this->adaugaDreapta(membru, de_introdus);
		return 0;
	}
	else {
		this->adaugaStanga(membru, de_introdus);
		return 1;
	}
}

void Lista::StergereLista(){
	Bila* index = Cap;
	while (index) {
		Bila* aux = index->GetBilaDreapta();
		stergeBila(index);
		marime--;
		index = aux;
	}
	printf("Am sters lista\n");
}
void Lista::RenderList(){
	Bila* index = Cap;
	while (index) {
		index->RenderCenter();
		index = index->GetBilaDreapta();
	}
}
//parcurge lista si returneaza obiectul cu care s-a facut coliziunea
Bila* Lista::TestColiziune(Proiectil* obuz)
{
	Bila* index = Cap;
	while (index){
		//verificare coliziune
		if (DistantaPatrat(obuz->GetCoordX(), index->GetCoordX(), obuz->GetCoordY(), index->GetCoordY()) <= pow((obuz->GetMarimeX() + index->GetMarimeSpriteX())/2, 2)) {
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



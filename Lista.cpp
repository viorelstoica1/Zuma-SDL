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
	de_introdus->CresteNumar(viteza);
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
	if (DirectieColiziune(membru,de_introdus)/*de_introdus->GetCoordX() > membru->GetCoordX()*/) {//deocamdata las inserarea fara sa tin cont de unghi
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
	static int de_introdus_original = de_introdus;
	static float viteza_curenta = viteza, viteza_max_curenta = viteza_max;
	Bila* index = Cap;
	bool collided = 0;
	if (index->GetIndex()>=index->GetMarimeSpriteX() && de_introdus) {
		this->adaugaLaStangaListei(this->CreeazaBila(Tunar->GetProiectilIncarcat()));
		Cap->SetTex(GetRandomBila(Tunar->GetListaTexturi()));
		Cap->CresteNumar(index->GetIndex()%index->GetMarimeSpriteX());
		de_introdus--;
	}
	while (index) {
		index->UpdateSprite();
		index->CresteNumar(viteza);
		if (collided) {//nu stiu unde trebuie sincer
			index->CresteNumar(index->GetMarimeSpriteX());
		}
		index->Copiaza(&traseu[index->GetIndex()]);
		if (CheckColiziuneBila(index, Tunar->GetProiectilIncarcat())) {
			Bila* noua = this->CreeazaBila(Tunar->GetProiectilIncarcat());
			if (this->adaugaPeElement(index, noua)) {//dreapta
				//mutam noua bila la locul ei
				noua->SetIndex(index->GetIndex() -viteza /*+ index->GetMarimeSpriteX()*/ );
				printf("Coliziune dreapta!\n");
				//index = noua;
			}
			else {//stanga
				noua->SetIndex(index->GetIndex() );//plus viteza sirului, 1 temporar
				printf("Coliziune stanga!\n");
				index->ScadeNumar(viteza);
				index = noua;
			}
			//index = index->GetBilaDreapta();
			//index = noua;
			noua->Copiaza(&traseu[noua->GetIndex()]);
			Tunar->TerminatTras();
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
	//if (de_introdus_original / 4 <= de_introdus_original - de_introdus) {//daca s-au introdus un sfert din bile
	//	acceleratie = -1;
	//}
	if (Coada->GetIndex() >= 750) {
		viteza_max_curenta = viteza_max;
	}
	if (Coada->GetIndex() >= 6000) {
		viteza_max_curenta = 1;
	}
	CalculeazaAcceleratia(viteza_curenta,viteza_max_curenta);
	viteza_curenta = viteza_curenta + acceleratie;
	viteza = viteza_curenta;
}

bool Lista::CheckColiziuneBila(Bila* membru, Proiectil* obuz){
	if (DistantaPatrat(obuz->GetCoordX(), membru->GetCoordX(), obuz->GetCoordY(), membru->GetCoordY()) <= pow((obuz->GetMarimeSpriteX() + (float)membru->GetMarimeSpriteX()) / 2, 2)) {
		return true;
	}
	return false;
}
void Lista::CalculeazaAcceleratia(float viteza_, float viteza_max_){
	if (viteza_ == viteza_max_) {
		acceleratie = 0;
	}
	else if (viteza_ < viteza_max_) {
		acceleratie = 0.2;
	}
	else acceleratie = -0.2;
}
//parcurge lista si returneaza obiectul cu care s-a facut coliziunea
Bila* Lista::TestColiziune(Proiectil* obuz){
	Bila* index = Cap;
	while (index){
		//verificare coliziune
		if (DistantaPatrat(obuz->GetCoordX(), index->GetCoordX(), obuz->GetCoordY(), index->GetCoordY()) <= pow((obuz->GetMarimeX() + (float)index->GetMarimeSpriteX())/2, 2)) {
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
	Bila* aux = new Bila(0, Rosu, 0, obuz->GetTex(), 8, obuz->GetCoordX(), obuz->GetCoordY(),obuz->GetUnghi());
	return aux;
	printf("Am creat o bila\n");
}



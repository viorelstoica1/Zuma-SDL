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


int Lista::Update(Tun* Tunar){
	static int de_introdus_original = de_introdus;
	static int winlose = 1;
	static float viteza_curenta = viteza, viteza_max_curenta = viteza_max;
	Bila* index = Cap;
	static Bila* coliziune = 0;//bila dupa care s-a facut coliziune
	bool collided = 0;
	if (!index) {
		return winlose;
	}
	//pentru inceputul nivelului
	if (index->GetIndex()>=index->GetMarimeSpriteX() && de_introdus) {
		this->adaugaLaStangaListei(CreeazaBilaRandom());
		//Cap->SetTex(GetRandomBila());
		Cap->CresteNumar(index->GetIndex()%index->GetMarimeSpriteX());
		de_introdus--;
	}
	while (index) {
		if (collided && index->GetInserare() == 0) {//nu stiu unde trebuie sincer
			index->CresteNumar(index->GetMarimeSpriteX() / 8);//10 de la numarul de cadre al animatiei de inserare
		}
		if (index->GetInserare() == 1) {
			AnimatieInserare(index);
			if (index->GetInserare() == 1) {
				collided = 1;
			}
		}
		else {
			index->Copiaza(&traseu[index->GetIndex()]);//NU MISCA ASTA
		}
		
		if (CheckColiziuneBila(index, Tunar->GetProiectilIncarcat())) {
			Bila* noua = this->CreeazaBila(Tunar->GetProiectilIncarcat());
			coliziune = noua;
			if (this->adaugaPeElement(index, noua)) {//dreapta
				noua->SetIndex(index->GetIndex()+index->GetMarimeSpriteX());
			}
			else {//stanga
				noua->SetIndex(index->GetIndex());
				index = noua;
			}

			Tunar->TerminatTras();
			//collided = 1;
			noua->SetInserare(1);
		}

		index->UpdateSprite();
		index->CresteNumar(viteza);
		index = index->GetBilaDreapta();
	}

	frame+= viteza;
	if (frame >= Cap->GetNrCadre() * 8) {
		frame = 0;
	}
	if (Coada->GetIndex() >= 750) {
		viteza_max_curenta = viteza_max;
	}
	if (Coada->GetIndex() >= 6000) {
		viteza_max_curenta = 1;
	}
	if (Coada->GetIndex() >= 6650) {
		viteza_max_curenta = 20;
	}
	if (Coada->GetIndex() >= 6700) {
		stergeBila(Coada);
		winlose = -1;
	}


	if (coliziune) {
		if (coliziune->GetInserare() == 0) {
			int nr_bile_identice = Check3Bile(coliziune);
			printf("Sunt %d bile de aceeasi culoare\n", nr_bile_identice);
			if (nr_bile_identice >= 3) {
				StergeBileIdentice(coliziune);
			}
			coliziune = 0;
		}
	}



	CalculeazaAcceleratia(viteza_curenta,viteza_max_curenta);
	viteza_curenta = viteza_curenta + acceleratie;
	viteza = viteza_curenta;
	return 0;
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
//verifica cate bile identice sunt legate de bila data parametru
int Lista::Check3Bile(Bila* membru){
	int nr = 1;
	Bila* pstanga = membru->GetBilaStanga();
	Bila* pdreapta = membru->GetBilaDreapta();
	while (pstanga) {
		if (pstanga->GetTex() != membru->GetTex()) {
			pstanga = 0;
		}
		else {
			nr++;
			pstanga = pstanga->GetBilaStanga();
		}
	}
	while (pdreapta) {
		if (pdreapta->GetTex() != membru->GetTex()) {
			pdreapta = 0;
		}
		else {
			nr++;
			pdreapta = pdreapta->GetBilaDreapta();
		}
	}
	return nr;
}
//Merge la stanga de bila data ca parametru, apoi sterge bilele identice si muta totul de dupa la stanga
void Lista::StergeBileIdentice(Bila* membru){
	int nr = 1;
	Bila* pstanga = membru->GetBilaStanga();
	Bila* pdreapta = membru->GetBilaDreapta();
	Bila* aux = 0;
	while (pstanga) {
		if (pstanga->GetTex() != membru->GetTex()) {
			pstanga = 0;
		}
		else {
			nr++;
			aux = pstanga->GetBilaStanga();
			stergeBila(pstanga);
			pstanga = aux;
		}
	}
	while (pdreapta) {
		if (pdreapta->GetTex() != membru->GetTex()) {
			pdreapta = 0;
		}
		else {
			nr++;
			aux = pdreapta->GetBilaDreapta();
			stergeBila(pdreapta);
			pdreapta = aux;
		}
	}
	pdreapta = Coada;
	while (pdreapta != membru) {
		pdreapta->ScadeNumar(pdreapta->GetMarimeSpriteX() * nr);
		pdreapta = pdreapta->GetBilaStanga();
	}
	stergeBila(membru);
	printf("Am sters %d bile\n", nr);
}
//animeaza inserarea bilei in sir
void Lista::AnimatieInserare(Bila* membru){
	static int cadre = 8;
	if (cadre == 0) {
		membru->SetInserare(0);
		cadre = 8;
	}
	else {
		float x = (traseu[membru->GetIndex()].GetCoordX() - membru->GetCoordX()) / (float)cadre;
		float y = (traseu[membru->GetIndex()].GetCoordY() - membru->GetCoordY()) / (float)cadre;
		membru->SetCoordX(membru->GetCoordX() + x);
		membru->SetCoordY(membru->GetCoordY() + y);
		cadre--;
	}
}
Bila* Lista::CreeazaBilaRandom()
{
	Bila* aux = new Bila(0, 0, GetRandomBila(), 8, 0, 0, 0);
	ScadereNumarBileExistente(aux->GetTex());
	return aux;
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
//sterge o bila din lista si reface legaturile
void Lista::stergeBila(Bila* membru){
	if (membru) {
		if (membru->GetBilaStanga()) {
			membru->GetBilaStanga()->SetBilaDreapta(membru->GetBilaDreapta());
		}
		else {
			Cap = membru->GetBilaDreapta();
		}
		if (membru->GetBilaDreapta()) {
			membru->GetBilaDreapta()->SetBilaStanga(membru->GetBilaStanga());
		}
		else {
			Coada = membru->GetBilaStanga();
		}
		//ScadereNumarBileExistente(membru->GetTex());
		membru->SetBilaDreapta(0);
		membru->SetBilaStanga(0);
		delete membru;
		membru = 0;
	}
}

Bila* Lista::CreeazaBila(Proiectil* obuz){
	Bila* aux = new Bila(0, /*Rosu,*/ 0, obuz->GetTex(), 8, obuz->GetCoordX(), obuz->GetCoordY(),obuz->GetUnghi());
	return aux;
}



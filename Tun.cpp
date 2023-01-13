#include"Tun.h"

extern int latime, lungime;
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

void Tun::SetProiectilRezerva(Proiectil* p){
	p_rezerva = p;
}

void Tun::CicleazaProiectil(){
	Proiectil* aux = p_curent;
	p_curent = p_rezerva;
	p_rezerva = aux;
	p_rezerva->SetTex(GetRandomBila(lista_texturi));
}

void Tun::Update(mouse* soricel){
	float aux = atan2((float)(soricel->maus_y - this->GetCoordY()), (float)(soricel->maus_x - this->GetCoordX()));
	if (aux < 0) {
		aux += 6.28;
	}
	if (gata_de_tras) {
		p_curent->SetCoordX(this->GetCoordX() + cos(aux) * 35);
		p_curent->SetCoordY(this->GetCoordY() + sin(aux) * 35);
		p_curent->SetUnghi(aux);
	}
	p_rezerva->SetCoordX(this->GetCoordX() - cos(aux) * 15);
	p_rezerva->SetCoordY(this->GetCoordY() - sin(aux) * 15);
	p_rezerva->SetUnghi(aux);
	this->SetUnghi(aux);//bun??
	this->GetProiectilIncarcat()->Update();
	if ((this->GetProiectilIncarcat()->GetCoordX() + this->GetProiectilIncarcat()->GetMarimeX()) < 0 || (this->GetProiectilIncarcat()->GetCoordY() + this->GetProiectilIncarcat()->GetMarimeY()) < 0 || (this->GetProiectilIncarcat()->GetCoordX() > latime) || (this->GetProiectilIncarcat()->GetCoordY() > lungime)) {//daca a iesit din ecran
		this->TerminatTras();
		printf("A iesit obuzul\n");
	}
}

void Tun::Trage(mouse* soricel){
	this->SetGataTras(0);
	printf("Unghi tragere: %f\n", this->GetUnghi());
	this->GetProiectilIncarcat()->SetViteza(cos(this->GetUnghi()) * this->GetVitezaTragere(), sin(this->GetUnghi()) * this->GetVitezaTragere());
	this->GetProiectilIncarcat()->SetUnghi(this->GetUnghi());
	printf("Proiectilul are viteza x=%.2f y=%.2f\n",this->GetProiectilIncarcat()->GetVitezaX(), this->GetProiectilIncarcat()->GetVitezaY());

}

void Tun::TerminatTras(){
	this->GetProiectilIncarcat()->SetCoordX(this->GetCoordX());
	this->GetProiectilIncarcat()->SetCoordY(this->GetCoordY());
	this->GetProiectilIncarcat()->SetViteza(0, 0);
	this->SetGataTras(1);
	this->CicleazaProiectil();
}

int Tun::GetVitezaTragere()
{
	return viteza_tragere;
}

SDL_Texture** Tun::GetListaTexturi()
{
	return lista_texturi;
}

void Tun::RenderProiectile(){
	p_curent->RenderCenter();
	p_rezerva->RenderCenter();
}

void Tun::SchimbaOrdineProiectile(){
	Proiectil* aux = p_curent;
	p_curent = p_rezerva;
	p_rezerva = aux;
}



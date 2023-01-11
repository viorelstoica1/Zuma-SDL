#include"Bila.h"


void Bila::SetBilaStanga(Bila* membru) {
	this->anterioara = membru;
}

void Bila::SetBilaDreapta(Bila* membru) {
	this->urmatoare = membru;
}

Bila* Bila::GetBilaStanga()
{
	return anterioara;
}

Bila* Bila::GetBilaDreapta()
{
	return urmatoare;
}

void Bila::CresteNumar(int i){
	index += i;
}

void Bila::ScadeNumar(int i){
	index -= i;
}

int Bila::GetNumar(){
	return index;
}

void Bila::SetNumar(int i){
	index = i;
}

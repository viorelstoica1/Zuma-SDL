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

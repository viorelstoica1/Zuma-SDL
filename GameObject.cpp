#include"GameObject.h"

GameObject::GameObject(int poz_x, int poz_y, float angel){
	x = poz_x;
	y = poz_y;
	unghi = angel;
	printf("Am construit un GameObject la pozitia x=%d  y=%d cu unghiul %.2f\n", poz_x, poz_y, angel);
}

GameObject::~GameObject(){
	x = y = unghi = 0;
}

int GameObject::GetCoordX(){
	return x;
}

int GameObject::GetCoordY(){
	return y;
}

void GameObject::SetCoordX(int _x){
	x = _x;
}

void GameObject::SetCoordY(int _y){
	y = _y;
}

float GameObject::GetUnghi(){
	return unghi;
}

void GameObject::SetUnghi(float angel){
	unghi = angel;
}

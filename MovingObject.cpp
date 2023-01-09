#include"MovingObject.h"

MovingObject::~MovingObject(){
	vit_x = vit_y = acc_x = acc_y = 0;
}

void MovingObject::Update(){
	this->SetCoordX(GetCoordX() + vit_x);
	this->SetCoordY(GetCoordY() + vit_y);
	vit_x += acc_x;
	vit_y += acc_y;
}
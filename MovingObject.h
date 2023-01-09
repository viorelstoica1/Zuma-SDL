#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H

#include"GameObject.h"
#include<stdio.h>
class MovingObject : virtual public GameObject {
private:
	float vit_x, vit_y, acc_x, acc_y;
public:
	MovingObject(float poz_x, float poz_y, float angel = 0) : GameObject(poz_x,poz_y,angel) {
		vit_x = vit_y = acc_x = acc_y = 0;//todo printf
		printf("Proiectil creat cu viteza x=%.2f y=%.2f si acceleratia x=%.2f y=%.2f\n", vit_x, vit_y, acc_x, acc_y);
	};
	MovingObject(float vitezax,float vitezay,float accelx, float accely,float poz_x, float poz_y, float angel = 0) : GameObject(poz_x, poz_y, angel) {
		vit_x = vitezax;	vit_y = vitezay;	acc_x = accelx;	acc_y = accely;//todo printf
		printf("Proiectil creat cu viteza x=%.2f y=%.2f si acceleratia x=%.2f y=%.2f\n", vit_x, vit_y, acc_x, acc_y);
	};
	~MovingObject();
	void Update();

	void SetAccel(float x, float y) { acc_x = x;	 acc_y = y; };
	void SetAccelX(float x) { acc_x = x; };
	void SetAccelY(float y) { acc_y = y; };

	void GetAccel(float& x, float& y) { x = acc_x;	y = acc_y; };
	float GetAccelX() { return acc_x; };
	float GetAccelY() { return acc_y; };

	void GetViteza(float& x, float& y) { x = vit_x;	y = vit_y; };
	float GetVitezaX() { return vit_x; };
	float GetVitezaY() { return vit_y; };

	void SetViteza(float x, float y) { vit_x = x;vit_y = y; };
	void SetVitezaX(float x) { vit_x = x; };
	void SetVitezaY(float y) { vit_y = y; };
};



#endif
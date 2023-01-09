#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H


#include <SDL.h>
#include <stdio.h>

class GameObject {
private:
	float x, y;//coordonate
	float unghi;//unghi in RADIANI
public:
	GameObject(float poz_x, float poz_y, float angel = 0);
	~GameObject();
	float GetCoordX();
	float GetCoordY();
	void SetCoordX(float _x);
	void SetCoordY(float _y);
	float GetUnghi();
	void SetUnghi(float angel);
	virtual void Update() { };
};


#endif
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H


#include <SDL.h>
#include <stdio.h>

class GameObject {
private:
	int x, y;//coordonate
	float unghi;//unghi in grade presupun
public:
	GameObject(int poz_x, int poz_y, float angel = 0);
	~GameObject();
	int GetCoordX();
	int GetCoordY();
	void SetCoordX(int _x);
	void SetCoordY(int _y);
	float GetUnghi();
	void SetUnghi(float angel);
};


#endif
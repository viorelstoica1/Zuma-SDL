#ifndef _FUNCTII_H
#define _FUNCTII_H

struct mouse {//struct coord mouse
	int maus_x, maus_y;
};

//returneaza distanta la patrat dintre 2 puncte(pt coliziuni)
float DistantaPatrat(float xa, float xb, float ya, float yb);

//Starts up SDL and creates window
bool init(int& latime, int& lungime);

//Frees media and shuts down SDL
void close();

void Render();

#endif
/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

#include"MainHeader.h"
SDL_Window* gWindow = NULL;//The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;//The window renderer

int main( int argc, char* args[] )
{
	int latime = 0, lungime = 0;//marime ecran creat, setate de functia init
	//Start up SDL and create window
	if( !init(latime,lungime) ){//latime si lungime nu sunt folositi ca parametri, returneaza marimea ecranului generat
		printf( "Failed to initialize!\n" );
	}
	else{
		int tun_x = latime / 2, tun_y = lungime - lungime / 8, frame = 0;//frame e folosit la animatii
		float unghi_tun = 0;
		Spritesheet tex_bila("grafici/Bila_Rosu_Viorel-Sheet.png", 8);
		Textura tex_crosshair("grafici/Crosshair.png");
		Textura tex_fundal("grafici/Background_1.png");
		Textura tex_Tun("grafici/Cannon.png");
		int maus_x = 0, maus_y = 0;//coordonatele mouse-ului pe fereastra, sunt setate de SDL_GetMouseState
		SDL_GetMouseState(&maus_x, &maus_y);//setare coordonate pentru crosshair inainte de randarea primului frame
		SDL_Rect poz_randat = { 0,0,0,0 };//structura intermediara folosita la toate randarile
		bool quit = false;//Main loop flag
		SDL_Event e;//Event handler
		while( !quit ){
			while( SDL_PollEvent( &e ) != 0 ){//Handle events on queue
				if( e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){//User requests quit
					quit = true;
				}
				if (e.type == SDL_MOUSEMOTION){//A miscat soricellu
					maus_x = e.motion.x;
					maus_y = e.motion.y;
				}
			}

			SDL_RenderClear( gRenderer );	//Clear screen

			poz_randat = { 0,0,latime,lungime };	//pozitia si marimea la care sa randez(x,y,w,h)
			SDL_RenderCopy( gRenderer, tex_fundal.GetTex(), NULL,&poz_randat );//Render texture to screen

			poz_randat = { maus_x-16,maus_y-16,32,32 };	//pozitia si marimea la care sa randez(x,y,w,h)
			SDL_RenderCopy(gRenderer, tex_crosshair.GetTex(), NULL, &poz_randat);//Render texture to screen

			poz_randat = { 200,200,64,64 };
			SDL_RenderCopy(gRenderer, tex_bila.GetTex(), tex_bila.GetCadruCurent(), &poz_randat);//Render texture to screen

			poz_randat = { tun_x-100,tun_y-100,200,200 };
			SDL_RenderCopyEx(gRenderer, tex_Tun.GetTex(), NULL, &poz_randat, unghi_tun*180/3.14+90, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent( gRenderer );	//Update screen
			frame++;
			if (frame >= 4){
				frame = 0;
				tex_bila.ScadeCadru();
			}

			unghi_tun = atan2(	(float)(maus_y - tun_y) , (float)(maus_x - tun_x));
		}
		SDL_ShowCursor(SDL_ENABLE);
	}
	close();
	return 0;
}

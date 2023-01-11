/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

#include"MainHeader.h"
extern SDL_Window* gWindow;//The window we'll be rendering to
extern SDL_Renderer* gRenderer;//The window renderer


int main( int argc, char* args[] )
{
	int latime = 0, lungime = 0;//marime ecran creat, setate de functia init
	//Start up SDL and create window
	if( !init(latime,lungime) ){//latime si lungime nu sunt folositi ca parametri, returneaza marimea ecranului generat
		printf( "Failed to initialize!\n" );
	}
	else {
		GameObject* s = 0;
		AlocareTraseuBile(s);
		int viteza = 15;//coordonatele mouse-ului pe fereastra, sunt setate de SDL_GetMouseState
		mouse soricel{0, 0};//struct coord mouse
		SDL_GetMouseState(&soricel.maus_x, &soricel.maus_y);//setare coordonate pentru crosshair inainte de randarea primului frame
		int frame = 0;//frame e folosit la animatii
		float aux;//folosit la unghi
		Bila* biluta1 = new Bila(0,Rosu,0,"grafici/Bila_Rosu_Viorel-Sheet.png", 8,latime/2,200,0);
		Textura tex_crosshair("grafici/Crosshair.png",soricel.maus_x,soricel.maus_y,0);
		Textura tex_fundal("grafici/Background_1.png",0,0,0);
		Tun Tunar("grafici/Cannon.png",latime/2,lungime-lungime/2,0);
		Proiectil obuz(Ball,"grafici/Bila_Rosu_Viorel32.png", Tunar.GetCoordX(), Tunar.GetCoordY(), 0);
		SDL_Rect poz_randat = { 0,0,0,0 };//structura intermediara folosita la toate randarile

		Tunar.SetProiectilCurent(&obuz);
		Lista ListaBile(s);
		ListaBile.adaugaLaStangaListei(biluta1);
		bool quit = false;//Main loop flag
		SDL_Event e;//Event handler
		while( !quit ){
			while( SDL_PollEvent( &e ) != 0 ){//Handle events on queue
				if( e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){//User requests quit
					quit = true;
				}
				if (e.type == SDL_MOUSEMOTION){//A miscat soricellu
					soricel.maus_x = e.motion.x;
					soricel.maus_y = e.motion.y;
					tex_crosshair.SetCoordX(soricel.maus_x);
					tex_crosshair.SetCoordY(soricel.maus_y);
				}
				if (e.type == SDL_MOUSEBUTTONDOWN && Tunar.GataDeTras())//click? cred?
				{
					Tunar.SetGataTras(0);
					printf("Unghi tragere: %f\n", Tunar.GetUnghi());
					obuz.SetViteza(cos(Tunar.GetUnghi())*viteza, sin(Tunar.GetUnghi())*viteza);
					obuz.SetUnghi(Tunar.GetUnghi());
					printf("Proiectilul are viteza x=%.2f y=%.2f\n", obuz.GetVitezaX(), obuz.GetVitezaY());
				}
			}
			aux = atan2((float)(soricel.maus_y - Tunar.GetCoordY()), (float)(soricel.maus_x - Tunar.GetCoordX()));
			if (aux < 0){
				aux += 6.28;
			}
			Tunar.SetUnghi(aux);//bun??
			obuz.Update();
			if ((obuz.GetCoordX() + obuz.GetMarimeX())<0	||	((obuz.GetCoordY() + obuz.GetMarimeY())<0) || (obuz.GetCoordX() > latime) || (obuz.GetCoordY() > lungime)){//daca a iesit din ecran
				obuz.SetCoordX(Tunar.GetCoordX());
				obuz.SetCoordY(Tunar.GetCoordY());
				obuz.SetViteza(0, 0);
				Tunar.SetGataTras(1);
				printf("A iesit obuzul\n");
			}

			ListaBile.Update(&Tunar);
			SDL_RenderClear(gRenderer);	//Clear screen
			tex_fundal.Render();
			ListaBile.RenderList();
			obuz.RenderCenter();
			tex_crosshair.Render();
			Tunar.RenderCenter();
			SDL_RenderPresent(gRenderer);	//Update screen
		}
		SDL_ShowCursor(SDL_ENABLE);
		ListaBile.StergereLista();
		StergereTraseu(s);
	}
	close();

	return 0;
}

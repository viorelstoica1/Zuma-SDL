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
		int maus_x = 0, maus_y = 0,viteza = 10;//coordonatele mouse-ului pe fereastra, sunt setate de SDL_GetMouseState
		SDL_GetMouseState(&maus_x, &maus_y);//setare coordonate pentru crosshair inainte de randarea primului frame
		int frame = 0;//frame e folosit la animatii
		float aux;
		Spritesheet tex_bila("grafici/Bila_Rosu_Viorel-Sheet.png", 8,200,200,0);
		Textura tex_crosshair("grafici/Crosshair.png",maus_x,maus_y,0);
		Textura tex_fundal("grafici/Background_1.png",0,0,0);
		Tun Tunar("grafici/Cannon.png",latime/2,lungime-lungime/8,0);
		Proiectil obuz(Bila,"grafici/Bila_Rosu_Viorel32.png", Tunar.GetCoordX(), Tunar.GetCoordY(), 0);
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
				if (e.type == SDL_MOUSEBUTTONDOWN && Tunar.GataDeTras())//click? cred?
				{
					Tunar.SetGataTras(0);
					printf("Unghi tragere: %f\n", Tunar.GetUnghi());
					obuz.SetViteza(cos(Tunar.GetUnghi())*viteza, sin(Tunar.GetUnghi())*viteza);
					printf("Proiectilul are viteza x=%.2f y=%.2f\n", obuz.GetVitezaX(), obuz.GetVitezaY());
				}
			}
			frame++;
			if (frame >= 4){
				frame = 0;
				tex_bila.ScadeCadru();
			}
			aux = atan2((float)(maus_y - Tunar.GetCoordY()), (float)(maus_x - Tunar.GetCoordX()));
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
			SDL_RenderClear(gRenderer);	//Clear screen

			poz_randat = { (int)tex_fundal.GetCoordX(),(int)tex_fundal.GetCoordY(),tex_fundal.GetMarimeX(),tex_fundal.GetMarimeY() };	//pozitia si marimea la care sa randez(x,y,w,h)
			SDL_RenderCopy(gRenderer, tex_fundal.GetTex(), NULL, &poz_randat);//Render texture to screen

			poz_randat = { maus_x - 8,maus_y - 8,tex_crosshair.GetMarimeX(),tex_crosshair.GetMarimeY() };	//pozitia si marimea la care sa randez(x,y,w,h)
			SDL_RenderCopy(gRenderer, tex_crosshair.GetTex(), NULL, &poz_randat);//Render texture to screen

			poz_randat = { tex_bila.CenterX(),tex_bila.CenterY(),tex_bila.GetMarimeSpriteX(),tex_bila.GetMarimeSpriteY() };
			SDL_RenderCopy(gRenderer, tex_bila.GetTex(), tex_bila.GetCadruCurent(), &poz_randat);//Render texture to screen

			poz_randat = { obuz.CenterX(),obuz.CenterY(),obuz.GetMarimeX(),obuz.GetMarimeY() };
			SDL_RenderCopy(gRenderer, obuz.GetTex(), NULL, &poz_randat);//Render texture to screen

			poz_randat = { Tunar.CenterX(),Tunar.CenterY(),Tunar.GetMarimeX(),Tunar.GetMarimeY() };
			SDL_RenderCopyEx(gRenderer, Tunar.GetTex(), NULL, &poz_randat, Tunar.GetUnghi() * 180 / 3.14 + 90, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(gRenderer);	//Update screen
		}
		SDL_ShowCursor(SDL_ENABLE);
	}
	close();

	return 0;
}

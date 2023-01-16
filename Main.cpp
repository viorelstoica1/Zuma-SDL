#include"MainHeader.h"
extern SDL_Window* gWindow;//The window we'll be rendering to
extern SDL_Renderer* gRenderer;//The window renderer
extern int latime, lungime;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init(latime,lungime) ){//latime si lungime nu sunt folositi ca parametri, returneaza marimea ecranului generat
		printf( "Failed to initialize!\n" );
	}
	else {
		GameObject* Traseu = 0;
		AlocareTraseuBile(Traseu);
		SDL_Texture** TexturiBile = 0;
		AlocareTexturi(TexturiBile);
		int gamestate = 0;//statusul jocului, 1 castigat, 0 ongoing, -1 pierdut
		mouse soricel{ 0, 0 };	//coordonatele mouse-ului pe fereastra, sunt setate de SDL_GetMouseState
		SDL_Texture* TexCrosshair = IMG_LoadTexture(gRenderer, "grafici/Crosshair.png");
		SDL_Texture* TexFundal = IMG_LoadTexture(gRenderer, "grafici/Background_1.png");
		SDL_Texture* TexTun = IMG_LoadTexture(gRenderer, "grafici/Cannon_no_shade.png");
		SDL_Texture* Tun_fundal = IMG_LoadTexture(gRenderer, "grafici/Cannon.png");

		SDL_GetMouseState(&soricel.maus_x, &soricel.maus_y);//setare coordonate pentru crosshair inainte de randarea primului frame
		Bila* biluta1 = new Bila(0,/*Rosu,*/0,GetRandomBila(TexturiBile), 8,latime/2,200,0);
		Textura Crosshair(TexCrosshair,soricel.maus_x,soricel.maus_y,0);
		Textura tex_fundal(TexFundal,0,0,0);
		Tun Tunar(15,TexturiBile, TexTun,latime/2+latime/8,lungime-lungime/2,0);
		Textura FundalTun(Tun_fundal, Tunar.GetCoordX(), Tunar.GetCoordY(), Tunar.GetUnghi());
		Proiectil obuz(Ball, GetRandomBila(TexturiBile), Tunar.GetCoordX(), Tunar.GetCoordY(), 0);
		Proiectil rezerva(Ball, GetRandomBila(TexturiBile), Tunar.GetCoordX(), Tunar.GetCoordY(), 0);

		Tunar.SetProiectilCurent(&obuz);
		Tunar.SetProiectilRezerva(&rezerva);
		Lista ListaBile(Traseu,20, 20, 1.75);
		ListaBile.adaugaLaStangaListei(biluta1);
		bool quit = false;//Main loop flag
		SDL_Event e;//Event handler
		while( !quit ){
			while( SDL_PollEvent( &e ) != 0 ){//Handle events on queue
				if( e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){//User requests quit
					quit = true;
				}
				if (e.type == SDL_MOUSEMOTION){//A miscat soricelu
					soricel.maus_x = e.motion.x;
					soricel.maus_y = e.motion.y;
					Crosshair.SetCoordX(soricel.maus_x - Crosshair.GetMarimeX()/2);
					Crosshair.SetCoordY(soricel.maus_y);
				}
				if (e.type == SDL_MOUSEBUTTONDOWN && Tunar.GataDeTras()) {//click? cred?
					if (e.button.button == SDL_BUTTON_LEFT) {
						Tunar.Trage(&soricel);
					}
					else if (e.button.button == SDL_BUTTON_RIGHT) {
						Tunar.SchimbaOrdineProiectile();
					}
				}
			}
			Tunar.Update(&soricel);
			gamestate = ListaBile.Update(&Tunar);
			if (gamestate) {
				if (gamestate == 1) {
					printf("Joc castigat\n");
				}
				else {
					printf("Joc pierdut\n");
				}
			}
			SDL_RenderClear(gRenderer);	//Clear screen
			tex_fundal.Render();
			FundalTun.SetUnghi(Tunar.GetUnghi());
			FundalTun.RenderCenter();
			ListaBile.RenderList();
			Tunar.RenderProiectile();
			Crosshair.Render();
			Tunar.RenderCenter();
			SDL_RenderPresent(gRenderer);	//Update screen
		}
		SDL_ShowCursor(SDL_ENABLE);
		ListaBile.StergereLista();
		StergereTraseu(Traseu);
		DealocareTexturi(TexturiBile);
		SDL_DestroyTexture(TexCrosshair);
		SDL_DestroyTexture(TexFundal);
		SDL_DestroyTexture(TexTun);
		SDL_DestroyTexture(Tun_fundal);
	}
	close();

	return 0;
}

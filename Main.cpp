#include"MainHeader.h"
extern SDL_Window* gWindow;//The window we'll be rendering to
extern SDL_Renderer* gRenderer;//The window renderer
extern int latime, lungime;
int scena = 0;//0 meniu, 1 controale, 2 joc
CuloriBile* bilute;
extern int nr_culori;
int main( int argc, char* args[] )
{
	srand(time(NULL));
	//Start up SDL and create window
	if( !init(latime,lungime) ){//latime si lungime nu sunt folositi ca parametri, returneaza marimea ecranului generat
		printf( "Failed to initialize!\n" );
	}
	else {
		SDL_Texture* TexMeniu = IMG_LoadTexture(gRenderer, "grafici/Meniu.png");
		SDL_Texture* TexWin = IMG_LoadTexture(gRenderer, "grafici/Win.png");
		SDL_Texture* TexLose = IMG_LoadTexture(gRenderer, "grafici/Lose.png");
		SDL_Texture* TexControale = IMG_LoadTexture(gRenderer, "grafici/Controale.png");
		SDL_Texture* TexCrosshair = IMG_LoadTexture(gRenderer, "grafici/Crosshair.png");
		SDL_Texture* TexFundal = IMG_LoadTexture(gRenderer, "grafici/Background_1.png");
		SDL_Texture* TexTun = IMG_LoadTexture(gRenderer, "grafici/Cannon_no_shade.png");
		SDL_Texture* Tun_fundal = IMG_LoadTexture(gRenderer, "grafici/Cannon.png");
		Textura Controale(TexControale, 0, 0, 0);
		Textura Meniu(TexMeniu, 0, 0, 0);
		SDL_Event e;//Event handler
		mouse soricel{ 0, 0 };	//coordonatele mouse-ului pe fereastra, sunt setate de SDL_GetMouseState
		bool iesire_program = 0;
		Meniu.Render();
		SDL_RenderPresent(gRenderer);	//Update screen
		while (!iesire_program) {

			switch (scena)
			{
			case 0://meniu
				SDL_RenderClear(gRenderer);
				Meniu.SetTex(TexMeniu);
				Meniu.Render();
				SDL_RenderPresent(gRenderer);	//Update screen
				SDL_ShowCursor(SDL_ENABLE);
				while (SDL_PollEvent(&e) != 0) {//Handle events on queue
					if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {//User requests quit
						iesire_program = true;
					}
					if (e.type == SDL_MOUSEMOTION) {//A miscat soricelu
						soricel.maus_x = e.motion.x;
						soricel.maus_y = e.motion.y;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {//click? cred?
						if (e.button.button == SDL_BUTTON_LEFT) {
							if (soricel.maus_x >= 200 && soricel.maus_x <= 400 && soricel.maus_y >= 400 && soricel.maus_y <= 500) {
								//buton usor
								nr_culori = 4;
								scena = 2;
							}
							else if (soricel.maus_x >= 800 && soricel.maus_x <= 1100 && soricel.maus_y >= 400 && soricel.maus_y <= 500) {
								//buton mediu
								nr_culori = 6;
								scena = 2;
							}
							else if (soricel.maus_x >= 1500 && soricel.maus_x <= 1700 && soricel.maus_y >= 400 && soricel.maus_y <= 500) {
								//buton greu
								nr_culori = 8;
								scena = 2;
							}
							else if (soricel.maus_x >= 800 && soricel.maus_x <= 1100 && soricel.maus_y >= 720 && soricel.maus_y <= 820) {
								//buton controale
								scena = 1;
							}
							else if (soricel.maus_x >= 800 && soricel.maus_x <= 1100 && soricel.maus_y >= 900 && soricel.maus_y <= 960) {
								//buton iesire
								iesire_program = true;
							}
						}

					}
				}
				break;
			case 1://controale
				SDL_RenderClear(gRenderer);
				Controale.Render();
				SDL_RenderPresent(gRenderer);	//Update screen
				SDL_ShowCursor(SDL_ENABLE);
				while (SDL_PollEvent(&e) != 0) {//Handle events on queue
					if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {//User requests quit
						scena = 0;
					}
					if (e.type == SDL_MOUSEMOTION) {//A miscat soricelu
						soricel.maus_x = e.motion.x;
						soricel.maus_y = e.motion.y;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {//click? cred?
						if (e.button.button == SDL_BUTTON_LEFT) {
							if (soricel.maus_x >= 800 && soricel.maus_x <= 1000 && soricel.maus_y >= 720 && soricel.maus_y <= 820) {
								//buton meniu
								scena = 0;
							}
						}
					}
				}

				break;
			case 2://joc
			{
				SDL_ShowCursor(SDL_DISABLE);
				GameObject* Traseu = 0;
				AlocareTraseuBile(Traseu);
				AlocareTexturi();
				int gamestate = 0;//statusul jocului, 1 castigat, 0 ongoing, -1 pierdut

				SDL_GetMouseState(&soricel.maus_x, &soricel.maus_y);//setare coordonate pentru crosshair inainte de randarea primului frame
				Bila* biluta1 = new Bila(0, 0, GetRandomBila(), 8, latime / 2, 200, 0);
				Lista ListaBile(Traseu, 75, 20, 2);
				ListaBile.adaugaLaStangaListei(biluta1);
				Textura Crosshair(TexCrosshair, soricel.maus_x, soricel.maus_y, 0);
				Textura tex_fundal(TexFundal, 0, 0, 0);
				Tun Tunar(15, TexTun, latime / 2 + latime / 8, lungime - lungime / 2, 0);
				Textura FundalTun(Tun_fundal, Tunar.GetCoordX(), Tunar.GetCoordY(), Tunar.GetUnghi());
				Proiectil obuz(Ball, GetRandomBilaExistenta(), Tunar.GetCoordX(), Tunar.GetCoordY(), 0);
				Proiectil rezerva(Ball, GetRandomBilaExistenta(), Tunar.GetCoordX(), Tunar.GetCoordY(), 0);

				Tunar.SetProiectilCurent(&obuz);
				Tunar.SetProiectilRezerva(&rezerva);

				bool quit = false;//Main loop flag
				while (!quit) {
					while (SDL_PollEvent(&e) != 0) {//Handle events on queue
						if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {//User requests quit
							quit = true;
						}
						if (e.type == SDL_MOUSEMOTION) {//A miscat soricelu
							soricel.maus_x = e.motion.x;
							soricel.maus_y = e.motion.y;
							Crosshair.SetCoordX(soricel.maus_x - Crosshair.GetMarimeX() / 2);
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
						quit = true;
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
				if (scena != 3 && scena != 4) {
					scena = 0;
				}
				SDL_ShowCursor(SDL_ENABLE);
				ListaBile.StergereLista();
				StergereTraseu(Traseu);
				DealocareTexturi();

				break;
			}
			case 3://win
				SDL_RenderClear(gRenderer);
				Meniu.SetTex(TexWin);
				Meniu.Render();
				SDL_RenderPresent(gRenderer);	//Update screen
				SDL_ShowCursor(SDL_ENABLE);
				while (SDL_PollEvent(&e) != 0) {//Handle events on queue
					if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {//User requests quit
						scena = 0;
					}
					if (e.type == SDL_MOUSEMOTION) {//A miscat soricelu
						soricel.maus_x = e.motion.x;
						soricel.maus_y = e.motion.y;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {//click? cred?
						if (e.button.button == SDL_BUTTON_LEFT) {
							if (soricel.maus_x >= 800 && soricel.maus_x <= 1000 && soricel.maus_y >= 720 && soricel.maus_y <= 820) {
								//buton meniu
								scena = 0;
							}
						}
					}
				}
				break;
			case 4://lose
				SDL_RenderClear(gRenderer);
				Meniu.SetTex(TexLose);
				Meniu.Render();
				SDL_RenderPresent(gRenderer);	//Update screen
				SDL_ShowCursor(SDL_ENABLE);
				while (SDL_PollEvent(&e) != 0) {//Handle events on queue
					if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {//User requests quit
						scena = 0;
					}
					if (e.type == SDL_MOUSEMOTION) {//A miscat soricelu
						soricel.maus_x = e.motion.x;
						soricel.maus_y = e.motion.y;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {//click? cred?
						if (e.button.button == SDL_BUTTON_LEFT) {
							if (soricel.maus_x >= 800 && soricel.maus_x <= 1000 && soricel.maus_y >= 720 && soricel.maus_y <= 820) {
								//buton meniu
								scena = 0;
							}
						}
					}
				}
				break;
			}
		}
		SDL_DestroyTexture(TexCrosshair);
		SDL_DestroyTexture(TexFundal);
		SDL_DestroyTexture(TexTun);
		SDL_DestroyTexture(Tun_fundal);
		SDL_DestroyTexture(TexMeniu);

	}
	close();

	return 0;
}

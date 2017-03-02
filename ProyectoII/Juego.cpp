#include "Juego.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Error.h"
#include "Menu.h"

using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 

//Constructora
Juego::Juego()
{
	srand(SDL_GetTicks());//Inicializamos los números aleatorios de manera que cada vez se van modificando
	exit = false;
	pWin = nullptr;
	pRenderer = nullptr;
	colorWin = { 0, 0, 0, 255 };

	//Rectángulo de la ventana
	winRect = { 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT };

	initSDL();//Inicializamos el renderizador

	initMedia();

	vectorEstados.push_back(new Menu(this));//Primer estado de la pila
	//vectorEstados.push_back(new Mundo(this));//Primer estado de la pila

}

//Destructora
Juego::~Juego()
{
	freeMedia();

	//Liberamos el renderizador
	closeSDL();
}

/*Arranca el bucle principal y controla si acaba la ejecución*/
void Juego::run()
{
	// La necesitaremos con un valor menor 
	Uint32 MSxUpdate = 5;
	Uint32 MSxInput = 1;

	SDL_ShowWindow(pWin);
	Uint32 lastUpdate = SDL_GetTicks(); //tiempo transcurrido desde el ultimo update()
	Uint32 lastInput = SDL_GetTicks(); //tiempo transcurrido desde el ultimo update()

	render();
	handle_event();
	while (!exit)
	{
		if (SDL_GetTicks() - lastUpdate >= MSxUpdate)//Se pide la hora y se compara con la última 
		{
			topEstado()->update();

			lastUpdate = SDL_GetTicks();
		}

		render();


		//Mix_PlayChannel( -1, pChunk,3 ); 

		if (SDL_GetTicks() - lastInput >= MSxInput)
		{
			handle_event();

			lastInput = SDL_GetTicks();
		}
	}
	//render();
	SDL_HideWindow(pWin);
	//GAME OVER

	// La necesitaremos con un valor menor 
	SDL_Delay(1000); //cin.get();
}


//Inicializa el renderizador, en caso de error muestra un mensaje y deja los atributos nulos
void Juego::initSDL()
{

	//Inicializa y detecta si hay error
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		string errorSDL = SDL_GetError();
		Error errorE("SDL no se puede iniciar! SDL_Error: " + errorSDL);
		throw(errorE);
	}
	else
	{
		TTF_Init();

		Mix_Init(27);//Iniciamos el mixer
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		//NO SABEMOS QUE HACE ESTA MIERDA, A LO MEJOR ES IMPORTANTE
		/*
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		*/


		//Creamos la ventana con unas dimensiones específicas y al principio se encuentra escondida
		pWin = SDL_CreateWindow("Nombre del juego", winRect.x, winRect.y, winRect.w, winRect.h, SDL_WINDOW_HIDDEN);

		//Caso de error en el que no se crea la ventana
		if (pWin == nullptr)
		{
			string errorSDL = SDL_GetError();
			Error errorE("La ventana no pudo crearse!SDL_Error: " + errorSDL);
			throw(errorE);
		}
		else
		{
			//Obtenemos la superficie de la ventana:
			pRenderer = SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED);
			if (pRenderer == nullptr)
			{
				string errorSDL = SDL_GetError();
				Error errorE("El renderer no pudo crearse! SDL_Error: " + errorSDL);
				throw(errorE);
			}
			SDL_SetRenderDrawColor(pRenderer, colorWin.r, colorWin.g, colorWin.b, colorWin.a); //Ponemos color al fondo de la ventana
			//Caso de error en el que no se crea el renderizador

		}
	}

}

//Libera los atributos inicIados en initSDL
void Juego::closeSDL()
{
	SDL_DestroyRenderer(pRenderer);
	pRenderer = nullptr;

	SDL_DestroyWindow(pWin);
	pWin = nullptr;

	SDL_Quit();
}

//SE PUEDE METER INIT Y FREE EN EL PADRE
void Juego::initMedia()
{
	//TEXTURAS

	vector <string>nombArchTex = { "..\\bmps\\globo.png",  "..\\bmps\\play.png",
		"..\\bmps\\menu.png", "..\\bmps\\exit.png", "..\\bmps\\tiles3.png" };

	for (int i = 0; i < Texturas_t_SIZE - 1; i++)
	{
		texturas[i] = new TexturasSDL;
		texturas[i]->load(pRenderer, nombArchTex[i]);
	}
	//Fondo de la ventana

	recortarTiles();


	//FUENTE

	string archFont = { "..\\bmps\\font.ttf" };

	fuente.load(archFont);

	texturas[TFuente] = new TexturasSDL;

	//Efecto
	/*string archAudioWav = { "..\\sounds\\Efectos-de-sonido-Explosion-de-un-globo.wav" };
	efectos[EGlobo] = new Efecto();
	efectos[EGlobo]->load(archAudioWav);*/

	//Música
	/*string archAudioMp3 = { "..\\sounds\\22-tachimi-circus.wav" };
	musica[MPlay] = new Musica();
	musica[MPlay]->load(archAudioMp3);*/

}

void Juego::freeMedia()
{

	//TEXTURAS
	for (int i = 0; i < Texturas_t_SIZE - 1; i++)
	{
		delete(texturas[i]);
		texturas[i] = nullptr;
	}

	//MÚSICA

	Mix_Quit();

	//FUENTE

	fuente.close();

	delete(textFuente);
	textFuente = nullptr;

	TTF_Quit();

}

void Juego::render()
{
	//Limpiar el buffer
	SDL_RenderClear(pRenderer);

	topEstado()->draw();

	//Intercambiar buffer y mostrar
	SDL_RenderPresent(pRenderer);
}

void Juego::changeState(EstadoJuego *estado){
	popState();
	pushState(estado);
}

void Juego::pushState(EstadoJuego * nuevoEstado){
	vectorEstados.push_back(nuevoEstado);//Añadimos el nuevo estado
}

void Juego::popState(){
	delete(topEstado());
	vectorEstados.pop_back();//Eliminamos el último estado de la pila
}

void Juego::goToPausa(EstadoJuego *estado){
	vectorEstados.push_back(estado);//Añadimos el estado Pausa sin eliminar el estado actual (Play)
}

// tendrás que añadir atributos para la posición del ratón(que deben actualizarse en onClick)
void Juego::getMousePos(int & mpx, int & mpy) const
{
	mpx = posMouseX;
	mpy = posMouseY;
}

// Comprueba si hay un evento en la cola de eventos y procesa el metodo correspondiente
void Juego::handle_event(){
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0 ) {
		if (e.type == SDL_QUIT)
		{
			exit = true;//X para salir
		}

		if (e.button.button == SDL_BUTTON_LEFT)
		{
			posMouseX = e.button.x;
			posMouseY = e.button.y;
		}

	}

	topEstado()->onInput(e);

}


//---------------------------------------------
void Juego::recortarTiles()
{
	gTileClips[TILE_0].x = 0;
	gTileClips[TILE_0].y = 0;
	gTileClips[TILE_0].w = TILE_WIDTH;
	gTileClips[TILE_0].h = TILE_HEIGHT;

	gTileClips[TILE_1].x = 0;
	gTileClips[TILE_1].y = 32;
	gTileClips[TILE_1].w = TILE_WIDTH;
	gTileClips[TILE_1].h = TILE_HEIGHT;

	gTileClips[TILE_2].x = 0;
	gTileClips[TILE_2].y = 64;
	gTileClips[TILE_2].w = TILE_WIDTH;
	gTileClips[TILE_2].h = TILE_HEIGHT;

	gTileClips[TILE_3].x = 32;
	gTileClips[TILE_3].y = 0;
	gTileClips[TILE_3].w = TILE_WIDTH;
	gTileClips[TILE_3].h = TILE_HEIGHT;

	gTileClips[TILE_4].x = 32;
	gTileClips[TILE_4].y = 32;
	gTileClips[TILE_4].w = TILE_WIDTH;
	gTileClips[TILE_4].h = TILE_HEIGHT;

	gTileClips[TILE_5].x = 32;
	gTileClips[TILE_5].y = 64;
	gTileClips[TILE_5].w = TILE_WIDTH;
	gTileClips[TILE_5].h = TILE_HEIGHT;

	gTileClips[TILE_6].x = 64;
	gTileClips[TILE_6].y = 0;
	gTileClips[TILE_6].w = TILE_WIDTH;
	gTileClips[TILE_6].h = TILE_HEIGHT;

	gTileClips[TILE_7].x = 64;
	gTileClips[TILE_7].y = 32;
	gTileClips[TILE_7].w = TILE_WIDTH;
	gTileClips[TILE_7].h = TILE_HEIGHT;

	gTileClips[TILE_8].x = 64;
	gTileClips[TILE_8].y = 64;
	gTileClips[TILE_8].w = TILE_WIDTH;
	gTileClips[TILE_8].h = TILE_HEIGHT;

	gTileClips[TILE_9].x = 96;
	gTileClips[TILE_9].y = 0;
	gTileClips[TILE_9].w = TILE_WIDTH;
	gTileClips[TILE_9].h = TILE_HEIGHT;

	gTileClips[TILE_10].x = 96;
	gTileClips[TILE_10].y = 32;
	gTileClips[TILE_10].w = TILE_WIDTH;
	gTileClips[TILE_10].h = TILE_HEIGHT;

	gTileClips[TILE_11].x = 96;
	gTileClips[TILE_11].y = 64;
	gTileClips[TILE_11].w = TILE_WIDTH;
	gTileClips[TILE_11].h = TILE_HEIGHT;
}
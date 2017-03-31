#include "Juego.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Error.h"
#include "MenuInicio.h"
#include "GameOver.h"
#include "Pausa.h"
#include "Mundo.h"

using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librer�a estandar 

//Constructora
Juego::Juego()
{
	srand(SDL_GetTicks());//Inicializamos los n�meros aleatorios de manera que cada vez se van modificando
	exit = false;
	pWin = nullptr;
	pRenderer = nullptr;
	colorWin = { 0, 0, 0, 255 };
	borraEstado = false;
	indiceMapas = 0;

	//Rect�ngulo de la ventana
	winRect = { 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT };

	initSDL();//Inicializamos el renderizador

	nombreMapas = { "..\\bmps\\lazy.map", "..\\bmps\\lazy2.map" };

	initMedia();

	for (int i = 0; i < TAMA�O_LLAVES; i++)
		llavesCogidas[i] = false;

	estadoEnum = MInicio;
	vectorEstados.push_back(new MenuInicio(this));//Primer estado de la pila
	//vectorEstados.push_back(new Mundo(this));//Primer estado de la pila

}

//Destructora
Juego::~Juego()
{
	freeMedia();

	//Liberamos el renderizador
	closeSDL();
}

void Juego::gestionaEstados(Estados_t estado){
	EstadoJuego *aux; //Estado auxiliar que va a ser el estado a crear
	bool pausa = false;

	switch (estado){
		//Menus
	case MInicio:
		aux = new MenuInicio(this);
		break;

	case MGameOver:
		aux = new GameOver(this);
		break;

	case MPausa:
		aux = new Pausa(this);
		pausa = true;
		break;

		//Mundos
	case MundoReal:
		aux = new Mundo(this,nombreMapas[indiceMapas]);
		indiceMapas++;
		break;

	default:
		aux = new MenuInicio(this);
		break;
	
	}

	if (!pausa)
		changeState(aux);
	else
		goToPausa(aux);

	pausa = false;
	borraEstado = false;

}

/*Arranca el bucle principal y controla si acaba la ejecuci�n*/
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
		if (borraEstado)
			gestionaEstados(estadoEnum);

		if (SDL_GetTicks() - lastUpdate >= MSxUpdate)//Se pide la hora y se compara con la �ltima 
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


		//Creamos la ventana con unas dimensiones espec�ficas y al principio se encuentra escondida
		pWin = SDL_CreateWindow("Nombre del juego", winRect.x, winRect.y, winRect.w, winRect.h, SDL_WINDOW_HIDDEN);
		//SDL_SetWindowFullscreen(pWin, SDL_WINDOW_FULLSCREEN);

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
		"..\\bmps\\menu.png", "..\\bmps\\exit.png", "..\\bmps\\tiles3.png", "..\\bmps\\llave.png","..\\bmps\\informe.png", "..\\bmps\\informe.png"  };

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

	//M�sica
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

	//M�SICA

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
	vectorEstados.push_back(nuevoEstado);//A�adimos el nuevo estado
}

void Juego::popState(){
	delete(topEstado());
	vectorEstados.pop_back();//Eliminamos el �ltimo estado de la pila
}

void Juego::goToPausa(EstadoJuego *estado){
	vectorEstados.push_back(estado);//A�adimos el estado Pausa sin eliminar el estado actual (Play)
}

// tendr�s que a�adir atributos para la posici�n del rat�n(que deben actualizarse en onClick)
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
	gTileClips[0].x = 0;
	gTileClips[0].y = 0;
	gTileClips[0].w = TILE_WIDTH;
	gTileClips[0].h = TILE_HEIGHT;

	gTileClips[1].x = 0;
	gTileClips[1].y = 32;
	gTileClips[1].w = TILE_WIDTH;
	gTileClips[1].h = TILE_HEIGHT;

	gTileClips[2].x = 0;
	gTileClips[2].y = 64;
	gTileClips[2].w = TILE_WIDTH;
	gTileClips[2].h = TILE_HEIGHT;

	gTileClips[3].x = 32;
	gTileClips[3].y = 0;
	gTileClips[3].w = TILE_WIDTH;
	gTileClips[3].h = TILE_HEIGHT;

	gTileClips[4].x = 32;
	gTileClips[4].y = 32;
	gTileClips[4].w = TILE_WIDTH;
	gTileClips[4].h = TILE_HEIGHT;

	gTileClips[5].x = 32;
	gTileClips[5].y = 64;
	gTileClips[5].w = TILE_WIDTH;
	gTileClips[5].h = TILE_HEIGHT;

	gTileClips[6].x = 64;
	gTileClips[6].y = 0;
	gTileClips[6].w = TILE_WIDTH;
	gTileClips[6].h = TILE_HEIGHT;

	gTileClips[7].x = 64;
	gTileClips[7].y = 32;
	gTileClips[7].w = TILE_WIDTH;
	gTileClips[7].h = TILE_HEIGHT;

	gTileClips[8].x = 64;
	gTileClips[8].y = 64;
	gTileClips[8].w = TILE_WIDTH;
	gTileClips[8].h = TILE_HEIGHT;

	gTileClips[9].x = 96;
	gTileClips[9].y = 0;
	gTileClips[9].w = TILE_WIDTH;
	gTileClips[9].h = TILE_HEIGHT;

	gTileClips[10].x = 96;
	gTileClips[10].y = 32;
	gTileClips[10].w = TILE_WIDTH;
	gTileClips[10].h = TILE_HEIGHT;

	gTileClips[11].x = 96;
	gTileClips[11].y = 64;
	gTileClips[11].w = TILE_WIDTH;
	gTileClips[11].h = TILE_HEIGHT;
}
#include "Juego.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Error.h"
#include "MenuInicio.h"
#include "GameOver.h"
#include "Pausa.h"
#include "Mundo.h"

using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 

//Constructora
Juego::Juego()
{
	srand(SDL_GetTicks());//Inicializamos los números aleatorios de manera que cada vez se van modificando
	exit = false;
	pWin = nullptr;
	pRenderer = nullptr;
	colorWin = { 0, 0, 0, 255 };
	borraEstado = false;
	

	//Rectángulo de la ventana
	winRect = { 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT };

	initSDL();//Inicializamos el renderizador

	nombreMapas = { "..\\bmps\\hab.map", "..\\bmps\\hab2.map" };

	initMedia();

	estadoEnum = MInicio;
	vectorEstados.push_back(new MenuInicio(this));//Primer estado de la pila
	//vectorEstados.push_back(new Mundo(this));//Primer estado de la pila

}

//Paso de niveles

string Juego::SelectorDeNiveles() {
	int nivel = getNivel();
	return nombreMapas[indiceMapas+nivel];

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
		aux = new Mundo(this,SelectorDeNiveles());
		
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
		if (borraEstado)
			gestionaEstados(estadoEnum);

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
		"..\\bmps\\menu.png", "..\\bmps\\exit.png", "..\\bmps\\TILESETnew.png" };

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

	gTileClips[TILE_1].x = 32;
	gTileClips[TILE_1].y = 0;
	gTileClips[TILE_1].w = TILE_WIDTH;
	gTileClips[TILE_1].h = TILE_HEIGHT;

	gTileClips[TILE_2].x = 64;
	gTileClips[TILE_2].y = 0;
	gTileClips[TILE_2].w = TILE_WIDTH;
	gTileClips[TILE_2].h = TILE_HEIGHT;

	gTileClips[TILE_3].x = 96;
	gTileClips[TILE_3].y = 0;
	gTileClips[TILE_3].w = TILE_WIDTH;
	gTileClips[TILE_3].h = TILE_HEIGHT;

	gTileClips[TILE_4].x = 128;
	gTileClips[TILE_4].y = 0;
	gTileClips[TILE_4].w = TILE_WIDTH;
	gTileClips[TILE_4].h = TILE_HEIGHT;

	gTileClips[TILE_5].x = 160;
	gTileClips[TILE_5].y = 0;
	gTileClips[TILE_5].w = TILE_WIDTH;
	gTileClips[TILE_5].h = TILE_HEIGHT;

	gTileClips[TILE_6].x = 192;
	gTileClips[TILE_6].y = 0;
	gTileClips[TILE_6].w = TILE_WIDTH;
	gTileClips[TILE_6].h = TILE_HEIGHT;

	gTileClips[TILE_7].x = 224;
	gTileClips[TILE_7].y = 0;
	gTileClips[TILE_7].w = TILE_WIDTH;
	gTileClips[TILE_7].h = TILE_HEIGHT;

	gTileClips[TILE_8].x = 256;
	gTileClips[TILE_8].y = 0;
	gTileClips[TILE_8].w = TILE_WIDTH;
	gTileClips[TILE_8].h = TILE_HEIGHT;

	gTileClips[TILE_9].x = 288;
	gTileClips[TILE_9].y = 0;
	gTileClips[TILE_9].w = TILE_WIDTH;
	gTileClips[TILE_9].h = TILE_HEIGHT;

	gTileClips[TILE_10].x = 320;
	gTileClips[TILE_10].y = 0;
	gTileClips[TILE_10].w = TILE_WIDTH;
	gTileClips[TILE_10].h = TILE_HEIGHT;

	gTileClips[TILE_11].x = 352;
	gTileClips[TILE_11].y = 0;
	gTileClips[TILE_11].w = TILE_WIDTH;
	gTileClips[TILE_11].h = TILE_HEIGHT;

	gTileClips[TILE_12].x = 0;
	gTileClips[TILE_12].y = 32;
	gTileClips[TILE_12].w = TILE_WIDTH;
	gTileClips[TILE_12].h = TILE_HEIGHT;

	/*gTileClips[TILE_13].x = 32;  // tiles en blanco
	gTileClips[TILE_13].y = 32;
	gTileClips[TILE_13].w = TILE_WIDTH;
	gTileClips[TILE_13].h = TILE_HEIGHT;
	*/
	gTileClips[TILE_14].x = 64;
	gTileClips[TILE_14].y = 32;
	gTileClips[TILE_14].w = TILE_WIDTH;
	gTileClips[TILE_14].h = TILE_HEIGHT;

	gTileClips[TILE_15].x = 96;
	gTileClips[TILE_15].y = 32;
	gTileClips[TILE_15].w = TILE_WIDTH;
	gTileClips[TILE_15].h = TILE_HEIGHT;

	gTileClips[TILE_16].x = 128;
	gTileClips[TILE_16].y = 32;
	gTileClips[TILE_16].w = TILE_WIDTH;
	gTileClips[TILE_16].h = TILE_HEIGHT;

	gTileClips[TILE_17].x = 160;
	gTileClips[TILE_17].y = 32;
	gTileClips[TILE_17].w = TILE_WIDTH;
	gTileClips[TILE_17].h = TILE_HEIGHT;

	gTileClips[TILE_18].x = 192;
	gTileClips[TILE_18].y = 32;
	gTileClips[TILE_18].w = TILE_WIDTH;
	gTileClips[TILE_18].h = TILE_HEIGHT;

	gTileClips[TILE_19].x = 224;
	gTileClips[TILE_19].y = 32;
	gTileClips[TILE_19].w = TILE_WIDTH;
	gTileClips[TILE_19].h = TILE_HEIGHT;

	gTileClips[TILE_20].x = 256;
	gTileClips[TILE_20].y = 32;
	gTileClips[TILE_20].w = TILE_WIDTH;
	gTileClips[TILE_20].h = TILE_HEIGHT;

	gTileClips[TILE_21].x = 288;
	gTileClips[TILE_21].y = 32;
	gTileClips[TILE_21].w = TILE_WIDTH;
	gTileClips[TILE_21].h = TILE_HEIGHT;

	gTileClips[TILE_22].x = 320;
	gTileClips[TILE_22].y = 32;
	gTileClips[TILE_22].w = TILE_WIDTH;
	gTileClips[TILE_22].h = TILE_HEIGHT;

	gTileClips[TILE_23].x = 352;
	gTileClips[TILE_23].y = 32;
	gTileClips[TILE_23].w = TILE_WIDTH;
	gTileClips[TILE_23].h = TILE_HEIGHT;

	gTileClips[TILE_24].x = 0;
	gTileClips[TILE_24].y = 64;
	gTileClips[TILE_24].w = TILE_WIDTH;
	gTileClips[TILE_24].h = TILE_HEIGHT;

	/*gTileClips[TILE_25].x = 32; // tiles en blanco
	gTileClips[TILE_25].y = 0;
	gTileClips[TILE_25].w = TILE_WIDTH;
	gTileClips[TILE_25].h = TILE_HEIGHT;
	*/
	gTileClips[TILE_26].x = 64;
	gTileClips[TILE_26].y = 64;
	gTileClips[TILE_26].w = TILE_WIDTH;
	gTileClips[TILE_26].h = TILE_HEIGHT;

	gTileClips[TILE_27].x = 96;
	gTileClips[TILE_27].y = 64;
	gTileClips[TILE_27].w = TILE_WIDTH;
	gTileClips[TILE_27].h = TILE_HEIGHT;

	gTileClips[TILE_28].x = 128;
	gTileClips[TILE_28].y = 64;
	gTileClips[TILE_28].w = TILE_WIDTH;
	gTileClips[TILE_28].h = TILE_HEIGHT;

	gTileClips[TILE_29].x = 160;
	gTileClips[TILE_29].y = 64;
	gTileClips[TILE_29].w = TILE_WIDTH;
	gTileClips[TILE_29].h = TILE_HEIGHT;

	gTileClips[TILE_30].x = 192;
	gTileClips[TILE_30].y = 64;
	gTileClips[TILE_30].w = TILE_WIDTH;
	gTileClips[TILE_30].h = TILE_HEIGHT;

	gTileClips[TILE_31].x = 224;
	gTileClips[TILE_31].y = 64;
	gTileClips[TILE_31].w = TILE_WIDTH;
	gTileClips[TILE_31].h = TILE_HEIGHT;

	gTileClips[TILE_32].x = 256;
	gTileClips[TILE_32].y = 64;
	gTileClips[TILE_32].w = TILE_WIDTH;
	gTileClips[TILE_32].h = TILE_HEIGHT;

	gTileClips[TILE_33].x = 288;
	gTileClips[TILE_33].y = 64;
	gTileClips[TILE_33].w = TILE_WIDTH;
	gTileClips[TILE_33].h = TILE_HEIGHT;

	gTileClips[TILE_34].x = 320;
	gTileClips[TILE_34].y = 64;
	gTileClips[TILE_34].w = TILE_WIDTH;
	gTileClips[TILE_34].h = TILE_HEIGHT;

	gTileClips[TILE_35].x = 352;
	gTileClips[TILE_35].y = 64;
	gTileClips[TILE_35].w = TILE_WIDTH;
	gTileClips[TILE_35].h = TILE_HEIGHT;

	gTileClips[TILE_36].x = 0;
	gTileClips[TILE_36].y = 96;
	gTileClips[TILE_36].w = TILE_WIDTH;
	gTileClips[TILE_36].h = TILE_HEIGHT;

	gTileClips[TILE_37].x = 32;
	gTileClips[TILE_37].y = 96;
	gTileClips[TILE_37].w = TILE_WIDTH;
	gTileClips[TILE_37].h = TILE_HEIGHT;

	gTileClips[TILE_38].x = 64;
	gTileClips[TILE_38].y = 96;
	gTileClips[TILE_38].w = TILE_WIDTH;
	gTileClips[TILE_38].h = TILE_HEIGHT;

	gTileClips[TILE_39].x = 96;
	gTileClips[TILE_39].y = 96;
	gTileClips[TILE_39].w = TILE_WIDTH;
	gTileClips[TILE_39].h = TILE_HEIGHT;

	gTileClips[TILE_40].x = 128;
	gTileClips[TILE_40].y = 96;
	gTileClips[TILE_40].w = TILE_WIDTH;
	gTileClips[TILE_40].h = TILE_HEIGHT;

	gTileClips[TILE_41].x = 160;
	gTileClips[TILE_41].y = 96;
	gTileClips[TILE_41].w = TILE_WIDTH;
	gTileClips[TILE_41].h = TILE_HEIGHT;

	gTileClips[TILE_42].x = 192;
	gTileClips[TILE_42].y = 96;
	gTileClips[TILE_42].w = TILE_WIDTH;
	gTileClips[TILE_42].h = TILE_HEIGHT;

	gTileClips[TILE_43].x = 224;
	gTileClips[TILE_43].y = 96;
	gTileClips[TILE_43].w = TILE_WIDTH;
	gTileClips[TILE_43].h = TILE_HEIGHT;

	gTileClips[TILE_44].x = 256;
	gTileClips[TILE_44].y = 96;
	gTileClips[TILE_44].w = TILE_WIDTH;
	gTileClips[TILE_44].h = TILE_HEIGHT;
	/*
	gTileClips[TILE_45].x = 288;
	gTileClips[TILE_45].y = 96;
	gTileClips[TILE_45].w = TILE_WIDTH;
	gTileClips[TILE_45].h = TILE_HEIGHT;
	gTileClips[TILE_46].x = 320;
	gTileClips[TILE_46].y = 96;
	gTileClips[TILE_46].w = TILE_WIDTH;
	gTileClips[TILE_47].h = TILE_HEIGHT;
	gTileClips[TILE_47].x = 352;
	gTileClips[TILE_47].y = 96;
	gTileClips[TILE_47].w = TILE_WIDTH;                   // tiles en blanco
	gTileClips[TILE_47].h = TILE_HEIGHT;
	gTileClips[TILE_48].x = 0;
	gTileClips[TILE_48].y = 128;
	gTileClips[TILE_48].w = TILE_WIDTH;
	gTileClips[TILE_48].h = TILE_HEIGHT;
	*/
	gTileClips[TILE_49].x = 32;
	gTileClips[TILE_49].y = 128;
	gTileClips[TILE_49].w = TILE_WIDTH;
	gTileClips[TILE_49].h = TILE_HEIGHT;

	gTileClips[TILE_50].x = 64;
	gTileClips[TILE_50].y = 128;
	gTileClips[TILE_50].w = TILE_WIDTH;
	gTileClips[TILE_50].h = TILE_HEIGHT;

	gTileClips[TILE_51].x = 96;
	gTileClips[TILE_51].y = 128;
	gTileClips[TILE_51].w = TILE_WIDTH;
	gTileClips[TILE_51].h = TILE_HEIGHT;

	gTileClips[TILE_52].x = 128;
	gTileClips[TILE_52].y = 128;
	gTileClips[TILE_52].w = TILE_WIDTH;
	gTileClips[TILE_52].h = TILE_HEIGHT;

	gTileClips[TILE_53].x = 160;
	gTileClips[TILE_53].y = 128;
	gTileClips[TILE_53].w = TILE_WIDTH;
	gTileClips[TILE_53].h = TILE_HEIGHT;

	gTileClips[TILE_54].x = 192;
	gTileClips[TILE_54].y = 128;
	gTileClips[TILE_54].w = TILE_WIDTH;
	gTileClips[TILE_54].h = TILE_HEIGHT;

	gTileClips[TILE_55].x = 224;
	gTileClips[TILE_55].y = 128;
	gTileClips[TILE_55].w = TILE_WIDTH;
	gTileClips[TILE_55].h = TILE_HEIGHT;

	gTileClips[TILE_56].x = 256;
	gTileClips[TILE_56].y = 128;
	gTileClips[TILE_56].w = TILE_WIDTH;
	gTileClips[TILE_56].h = TILE_HEIGHT;
	/*
	gTileClips[TILE_57].x = 288;
	gTileClips[TILE_57].y = 128;
	gTileClips[TILE_57].w = TILE_WIDTH;
	gTileClips[TILE_57].h = TILE_HEIGHT;
	gTileClips[TILE_58].x = 320;
	gTileClips[TILE_58].y = 128;
	gTileClips[TILE_58].w = TILE_WIDTH;                 // tiles en blanco
	gTileClips[TILE_58].h = TILE_HEIGHT;
	gTileClips[TILE_59].x = 352;
	gTileClips[TILE_59].y = 128;
	gTileClips[TILE_59].w = TILE_WIDTH;
	gTileClips[TILE_59].h = TILE_HEIGHT;
	*/
	gTileClips[TILE_60].x = 0;
	gTileClips[TILE_60].y = 160;
	gTileClips[TILE_60].w = TILE_WIDTH;
	gTileClips[TILE_60].h = TILE_HEIGHT;

	gTileClips[TILE_61].x = 32;
	gTileClips[TILE_61].y = 160;
	gTileClips[TILE_61].w = TILE_WIDTH;
	gTileClips[TILE_61].h = TILE_HEIGHT;

	gTileClips[TILE_62].x = 64;
	gTileClips[TILE_62].y = 160;
	gTileClips[TILE_62].w = TILE_WIDTH;
	gTileClips[TILE_62].h = TILE_HEIGHT;

	gTileClips[TILE_63].x = 96;
	gTileClips[TILE_63].y = 160;
	gTileClips[TILE_63].w = TILE_WIDTH;
	gTileClips[TILE_63].h = TILE_HEIGHT;

	gTileClips[TILE_64].x = 128;
	gTileClips[TILE_64].y = 160;
	gTileClips[TILE_64].w = TILE_WIDTH;
	gTileClips[TILE_64].h = TILE_HEIGHT;

	gTileClips[TILE_65].x = 160;
	gTileClips[TILE_65].y = 160;
	gTileClips[TILE_65].w = TILE_WIDTH;
	gTileClips[TILE_65].h = TILE_HEIGHT;

	gTileClips[TILE_66].x = 192;
	gTileClips[TILE_66].y = 160;
	gTileClips[TILE_66].w = TILE_WIDTH;
	gTileClips[TILE_66].h = TILE_HEIGHT;

	gTileClips[TILE_67].x = 224;
	gTileClips[TILE_67].y = 160;
	gTileClips[TILE_67].w = TILE_WIDTH;
	gTileClips[TILE_67].h = TILE_HEIGHT;

	gTileClips[TILE_68].x = 256;
	gTileClips[TILE_68].y = 160;
	gTileClips[TILE_68].w = TILE_WIDTH;
	gTileClips[TILE_68].h = TILE_HEIGHT;
	/*
	gTileClips[TILE_69].x = 288;
	gTileClips[TILE_69].y = 160;
	gTileClips[TILE_69].w = TILE_WIDTH;
	gTileClips[TILE_69].h = TILE_HEIGHT;
	gTileClips[TILE_70].x = 320;
	gTileClips[TILE_70].y = 160;
	gTileClips[TILE_70].w = TILE_WIDTH;                        // tiles en blanco
	gTileClips[TILE_70].h = TILE_HEIGHT;
	gTileClips[TILE_71].x = 352;
	gTileClips[TILE_71].y = 160;
	gTileClips[TILE_71].w = TILE_WIDTH;
	gTileClips[TILE_71].h = TILE_HEIGHT;
	*/
	gTileClips[TILE_72].x = 0;
	gTileClips[TILE_72].y = 192;
	gTileClips[TILE_72].w = TILE_WIDTH;
	gTileClips[TILE_72].h = TILE_HEIGHT;

	gTileClips[TILE_73].x = 32;
	gTileClips[TILE_73].y = 192;
	gTileClips[TILE_73].w = TILE_WIDTH;
	gTileClips[TILE_73].h = TILE_HEIGHT;

	gTileClips[TILE_74].x = 64;
	gTileClips[TILE_74].y = 192;
	gTileClips[TILE_74].w = TILE_WIDTH;
	gTileClips[TILE_74].h = TILE_HEIGHT;

	gTileClips[TILE_75].x = 96;
	gTileClips[TILE_75].y = 192;
	gTileClips[TILE_75].w = TILE_WIDTH;
	gTileClips[TILE_75].h = TILE_HEIGHT;

	gTileClips[TILE_76].x = 128;
	gTileClips[TILE_76].y = 192;
	gTileClips[TILE_76].w = TILE_WIDTH;
	gTileClips[TILE_76].h = TILE_HEIGHT;

	gTileClips[TILE_77].x = 160;
	gTileClips[TILE_77].y = 192;
	gTileClips[TILE_77].w = TILE_WIDTH;
	gTileClips[TILE_77].h = TILE_HEIGHT;

	gTileClips[TILE_78].x = 192;
	gTileClips[TILE_78].y = 192;
	gTileClips[TILE_78].w = TILE_WIDTH;
	gTileClips[TILE_78].h = TILE_HEIGHT;

	gTileClips[TILE_79].x = 224;
	gTileClips[TILE_79].y = 192;
	gTileClips[TILE_79].w = TILE_WIDTH;
	gTileClips[TILE_79].h = TILE_HEIGHT;

	gTileClips[TILE_80].x = 256;
	gTileClips[TILE_80].y = 192;
	gTileClips[TILE_80].w = TILE_WIDTH;
	gTileClips[TILE_80].h = TILE_HEIGHT;
	/*
	gTileClips[TILE_81].x = 288;
	gTileClips[TILE_81].y = 192;
	gTileClips[TILE_81].w = TILE_WIDTH;
	gTileClips[TILE_81].h = TILE_HEIGHT;
	gTileClips[TILE_82].x = 320;
	gTileClips[TILE_82].y = 192;
	gTileClips[TILE_82].w = TILE_WIDTH;            // tiles en blanco
	gTileClips[TILE_82].h = TILE_HEIGHT;
	gTileClips[TILE_83].x = 352;
	gTileClips[TILE_83].y = 192;
	gTileClips[TILE_83].w = TILE_WIDTH;
	gTileClips[TILE_83].h = TILE_HEIGHT;
	*/
	gTileClips[TILE_84].x = 0;
	gTileClips[TILE_84].y = 224;
	gTileClips[TILE_84].w = TILE_WIDTH;
	gTileClips[TILE_84].h = TILE_HEIGHT;

	gTileClips[TILE_85].x = 32;
	gTileClips[TILE_85].y = 224;
	gTileClips[TILE_85].w = TILE_WIDTH;
	gTileClips[TILE_85].h = TILE_HEIGHT;

	gTileClips[TILE_86].x = 64;
	gTileClips[TILE_86].y = 224;
	gTileClips[TILE_86].w = TILE_WIDTH;
	gTileClips[TILE_86].h = TILE_HEIGHT;

	gTileClips[TILE_87].x = 96;
	gTileClips[TILE_87].y = 224;
	gTileClips[TILE_87].w = TILE_WIDTH;
	gTileClips[TILE_87].h = TILE_HEIGHT;

	gTileClips[TILE_88].x = 128;
	gTileClips[TILE_88].y = 224;
	gTileClips[TILE_88].w = TILE_WIDTH;
	gTileClips[TILE_88].h = TILE_HEIGHT;

	gTileClips[TILE_89].x = 160;
	gTileClips[TILE_89].y = 224;
	gTileClips[TILE_89].w = TILE_WIDTH;
	gTileClips[TILE_89].h = TILE_HEIGHT;

	gTileClips[TILE_90].x = 192;
	gTileClips[TILE_90].y = 224;
	gTileClips[TILE_90].w = TILE_WIDTH;
	gTileClips[TILE_90].h = TILE_HEIGHT;

	gTileClips[TILE_91].x = 224;
	gTileClips[TILE_91].y = 224;
	gTileClips[TILE_91].w = TILE_WIDTH;
	gTileClips[TILE_91].h = TILE_HEIGHT;

	gTileClips[TILE_92].x = 256;
	gTileClips[TILE_92].y = 224;
	gTileClips[TILE_92].w = TILE_WIDTH;
	gTileClips[TILE_92].h = TILE_HEIGHT;
	/*
	gTileClips[TILE_93].x = 288;
	gTileClips[TILE_93].y = 224;
	gTileClips[TILE_93].w = TILE_WIDTH;
	gTileClips[TILE_93].h = TILE_HEIGHT;
	gTileClips[TILE_94].x = 320;
	gTileClips[TILE_94].y = 224;
	gTileClips[TILE_94].w = TILE_WIDTH;
	gTileClips[TILE_94].h = TILE_HEIGHT;
	gTileClips[TILE_95].x = 352;
	gTileClips[TILE_95].y = 224;
	gTileClips[TILE_95].w = TILE_WIDTH;
	gTileClips[TILE_95].h = TILE_HEIGHT;
	gTileClips[TILE_96].x = 0;
	gTileClips[TILE_96].y = 256;
	gTileClips[TILE_96].w = TILE_WIDTH;
	gTileClips[TILE_96].h = TILE_HEIGHT;         // tiles en blanco
	gTileClips[TILE_97].x = 32;
	gTileClips[TILE_97].y = 256;
	gTileClips[TILE_97].w = TILE_WIDTH;
	gTileClips[TILE_97].h = TILE_HEIGHT;
	gTileClips[TILE_98].x = 64;
	gTileClips[TILE_98].y = 256;
	gTileClips[TILE_98].w = TILE_WIDTH;
	gTileClips[TILE_98].h = TILE_HEIGHT;
	*/
	gTileClips[TILE_99].x = 96;
	gTileClips[TILE_99].y = 256;
	gTileClips[TILE_99].w = TILE_WIDTH;
	gTileClips[TILE_99].h = TILE_HEIGHT;

	gTileClips[TILE_100].x = 128;
	gTileClips[TILE_100].y = 256;
	gTileClips[TILE_100].w = TILE_WIDTH;
	gTileClips[TILE_100].h = TILE_HEIGHT;

	gTileClips[TILE_101].x = 160;
	gTileClips[TILE_101].y = 256;
	gTileClips[TILE_101].w = TILE_WIDTH;
	gTileClips[TILE_101].h = TILE_HEIGHT;

	gTileClips[TILE_102].x = 192;
	gTileClips[TILE_102].y = 256;
	gTileClips[TILE_102].w = TILE_WIDTH;
	gTileClips[TILE_102].h = TILE_HEIGHT;

	gTileClips[TILE_103].x = 224;
	gTileClips[TILE_103].y = 256;
	gTileClips[TILE_103].w = TILE_WIDTH;
	gTileClips[TILE_103].h = TILE_HEIGHT;

	gTileClips[TILE_104].x = 256;
	gTileClips[TILE_104].y = 256;
	gTileClips[TILE_104].w = TILE_WIDTH;
	gTileClips[TILE_104].h = TILE_HEIGHT;
}
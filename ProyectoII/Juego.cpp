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

	nombreMapas = { "..\\bmps\\pasillo.csv", "..\\bmps\\hab.csv", "..\\bmps\\hab2.csv", "..\\bmps\\hab3.csv", "..\\bmps\\hab4.csv",
	"..\\bmps\\baño.map", "..\\bmps\\haboscura.csv", "..\\bmps\\hab2oscuro.csv", "..\\bmps\\bañooscuro.csv" };

	initMedia();

	for (int i = 0; i < TAMAÑO_LLAVES; i++)
		llavesCogidas[i] = false;

	estadoEnum = MInicio;
	vectorEstados.push_back(new MenuInicio(this));//Primer estado de la pila
	//vectorEstados.push_back(new Mundo(this));//Primer estado de la pila

}

//Paso de niveles

string Juego::SelectorDeNiveles() {
	int nivel = getNivel();
	indiceMapas += nivel;
	return nombreMapas[indiceMapas];

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
		"..\\bmps\\menu.png", "..\\bmps\\exit.png", "..\\bmps\\tilesdef.png", "..\\bmps\\llave.png",
		"..\\bmps\\informe.png", "..\\bmps\\informe.png" };

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

	gTileClips[TILE_12].x = 384;
	gTileClips[TILE_12].y = 0;
	gTileClips[TILE_12].w = TILE_WIDTH;
	gTileClips[TILE_12].h = TILE_HEIGHT;

	gTileClips[TILE_13].x = 416;
	gTileClips[TILE_13].y = 0;
	gTileClips[TILE_13].w = TILE_WIDTH;
	gTileClips[TILE_13].h = TILE_HEIGHT;

	gTileClips[TILE_14].x = 448;
	gTileClips[TILE_14].y = 0;
	gTileClips[TILE_14].w = TILE_WIDTH;
	gTileClips[TILE_14].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_15].x = 0;
	gTileClips[TILE_15].y = 32;
	gTileClips[TILE_15].w = TILE_WIDTH;
	gTileClips[TILE_15].h = TILE_HEIGHT;

	gTileClips[TILE_16].x = 32;
	gTileClips[TILE_16].y = 32;
	gTileClips[TILE_16].w = TILE_WIDTH;
	gTileClips[TILE_16].h = TILE_HEIGHT;

	gTileClips[TILE_17].x = 64;
	gTileClips[TILE_17].y = 32;
	gTileClips[TILE_17].w = TILE_WIDTH;
	gTileClips[TILE_17].h = TILE_HEIGHT;

	gTileClips[TILE_18].x = 96;
	gTileClips[TILE_18].y = 32;
	gTileClips[TILE_18].w = TILE_WIDTH;
	gTileClips[TILE_18].h = TILE_HEIGHT;

	gTileClips[TILE_19].x = 128;
	gTileClips[TILE_19].y = 32;
	gTileClips[TILE_19].w = TILE_WIDTH;
	gTileClips[TILE_19].h = TILE_HEIGHT;

	gTileClips[TILE_20].x = 160;
	gTileClips[TILE_20].y = 32;
	gTileClips[TILE_20].w = TILE_WIDTH;
	gTileClips[TILE_20].h = TILE_HEIGHT;

	gTileClips[TILE_21].x = 192;
	gTileClips[TILE_21].y = 32;
	gTileClips[TILE_21].w = TILE_WIDTH;
	gTileClips[TILE_21].h = TILE_HEIGHT;

	gTileClips[TILE_22].x = 224;
	gTileClips[TILE_22].y = 32;
	gTileClips[TILE_22].w = TILE_WIDTH;
	gTileClips[TILE_22].h = TILE_HEIGHT;

	gTileClips[TILE_23].x = 256;
	gTileClips[TILE_23].y = 32;
	gTileClips[TILE_23].w = TILE_WIDTH;
	gTileClips[TILE_23].h = TILE_HEIGHT;

	gTileClips[TILE_24].x = 288;
	gTileClips[TILE_24].y = 32;
	gTileClips[TILE_24].w = TILE_WIDTH;
	gTileClips[TILE_24].h = TILE_HEIGHT;

	gTileClips[TILE_25].x = 320;
	gTileClips[TILE_25].y = 32;
	gTileClips[TILE_25].w = TILE_WIDTH;
	gTileClips[TILE_25].h = TILE_HEIGHT;

	gTileClips[TILE_26].x = 352;
	gTileClips[TILE_26].y = 32;
	gTileClips[TILE_26].w = TILE_WIDTH;
	gTileClips[TILE_26].h = TILE_HEIGHT;

	gTileClips[TILE_27].x = 384;
	gTileClips[TILE_27].y = 32;
	gTileClips[TILE_27].w = TILE_WIDTH;
	gTileClips[TILE_27].h = TILE_HEIGHT;

	gTileClips[TILE_28].x = 416;
	gTileClips[TILE_28].y = 32;
	gTileClips[TILE_28].w = TILE_WIDTH;
	gTileClips[TILE_28].h = TILE_HEIGHT;

	gTileClips[TILE_29].x = 448;
	gTileClips[TILE_29].y = 32;
	gTileClips[TILE_29].w = TILE_WIDTH;
	gTileClips[TILE_29].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_30].x = 0;
	gTileClips[TILE_30].y = 64;
	gTileClips[TILE_30].w = TILE_WIDTH;
	gTileClips[TILE_30].h = TILE_HEIGHT;

	gTileClips[TILE_31].x = 32;
	gTileClips[TILE_31].y = 64;
	gTileClips[TILE_31].w = TILE_WIDTH;
	gTileClips[TILE_31].h = TILE_HEIGHT;

	gTileClips[TILE_32].x = 64;
	gTileClips[TILE_32].y = 64;
	gTileClips[TILE_32].w = TILE_WIDTH;
	gTileClips[TILE_32].h = TILE_HEIGHT;

	gTileClips[TILE_33].x = 96;
	gTileClips[TILE_33].y = 64;
	gTileClips[TILE_33].w = TILE_WIDTH;
	gTileClips[TILE_33].h = TILE_HEIGHT;

	gTileClips[TILE_34].x = 128;
	gTileClips[TILE_34].y = 64;
	gTileClips[TILE_34].w = TILE_WIDTH;
	gTileClips[TILE_34].h = TILE_HEIGHT;

	gTileClips[TILE_35].x = 160;
	gTileClips[TILE_35].y = 64;
	gTileClips[TILE_35].w = TILE_WIDTH;
	gTileClips[TILE_35].h = TILE_HEIGHT;

	gTileClips[TILE_36].x = 192;
	gTileClips[TILE_36].y = 64;
	gTileClips[TILE_36].w = TILE_WIDTH;
	gTileClips[TILE_36].h = TILE_HEIGHT;

	gTileClips[TILE_37].x = 224;
	gTileClips[TILE_37].y = 64;
	gTileClips[TILE_37].w = TILE_WIDTH;
	gTileClips[TILE_37].h = TILE_HEIGHT;

	gTileClips[TILE_38].x = 256;
	gTileClips[TILE_38].y = 64;
	gTileClips[TILE_38].w = TILE_WIDTH;
	gTileClips[TILE_38].h = TILE_HEIGHT;

	gTileClips[TILE_39].x = 288;
	gTileClips[TILE_39].y = 64;
	gTileClips[TILE_39].w = TILE_WIDTH;
	gTileClips[TILE_39].h = TILE_HEIGHT;

	gTileClips[TILE_40].x = 320;
	gTileClips[TILE_40].y = 64;
	gTileClips[TILE_40].w = TILE_WIDTH;
	gTileClips[TILE_40].h = TILE_HEIGHT;

	gTileClips[TILE_41].x = 352;
	gTileClips[TILE_41].y = 64;
	gTileClips[TILE_41].w = TILE_WIDTH;
	gTileClips[TILE_41].h = TILE_HEIGHT;

	gTileClips[TILE_42].x = 384;
	gTileClips[TILE_42].y = 64;
	gTileClips[TILE_42].w = TILE_WIDTH;
	gTileClips[TILE_42].h = TILE_HEIGHT;

	gTileClips[TILE_43].x = 416;
	gTileClips[TILE_43].y = 64;
	gTileClips[TILE_43].w = TILE_WIDTH;
	gTileClips[TILE_43].h = TILE_HEIGHT;

	gTileClips[TILE_44].x = 448;
	gTileClips[TILE_44].y = 64;
	gTileClips[TILE_44].w = TILE_WIDTH;
	gTileClips[TILE_44].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_45].x = 0;
	gTileClips[TILE_45].y = 96;
	gTileClips[TILE_45].w = TILE_WIDTH;
	gTileClips[TILE_45].h = TILE_HEIGHT;

	gTileClips[TILE_46].x = 32;
	gTileClips[TILE_46].y = 96;
	gTileClips[TILE_46].w = TILE_WIDTH;
	gTileClips[TILE_46].h = TILE_HEIGHT;

	gTileClips[TILE_47].x = 64;
	gTileClips[TILE_47].y = 96;
	gTileClips[TILE_47].w = TILE_WIDTH;
	gTileClips[TILE_47].h = TILE_HEIGHT;

	gTileClips[TILE_48].x = 96;
	gTileClips[TILE_48].y = 96;
	gTileClips[TILE_48].w = TILE_WIDTH;
	gTileClips[TILE_48].h = TILE_HEIGHT;

	gTileClips[TILE_49].x = 128;
	gTileClips[TILE_49].y = 96;
	gTileClips[TILE_49].w = TILE_WIDTH;
	gTileClips[TILE_49].h = TILE_HEIGHT;

	gTileClips[TILE_50].x = 160;
	gTileClips[TILE_50].y = 96;
	gTileClips[TILE_50].w = TILE_WIDTH;
	gTileClips[TILE_50].h = TILE_HEIGHT;

	gTileClips[TILE_51].x = 192;
	gTileClips[TILE_51].y = 96;
	gTileClips[TILE_51].w = TILE_WIDTH;
	gTileClips[TILE_51].h = TILE_HEIGHT;

	gTileClips[TILE_52].x = 224;
	gTileClips[TILE_52].y = 96;
	gTileClips[TILE_52].w = TILE_WIDTH;
	gTileClips[TILE_52].h = TILE_HEIGHT;

	gTileClips[TILE_53].x = 256;
	gTileClips[TILE_53].y = 96;
	gTileClips[TILE_53].w = TILE_WIDTH;
	gTileClips[TILE_53].h = TILE_HEIGHT;

	gTileClips[TILE_54].x = 288;
	gTileClips[TILE_54].y = 96;
	gTileClips[TILE_54].w = TILE_WIDTH;
	gTileClips[TILE_54].h = TILE_HEIGHT;

	gTileClips[TILE_55].x = 320;
	gTileClips[TILE_55].y = 96;
	gTileClips[TILE_55].w = TILE_WIDTH;
	gTileClips[TILE_55].h = TILE_HEIGHT;

	gTileClips[TILE_56].x = 352;
	gTileClips[TILE_56].y = 96;
	gTileClips[TILE_56].w = TILE_WIDTH;
	gTileClips[TILE_56].h = TILE_HEIGHT;

	gTileClips[TILE_57].x = 384;
	gTileClips[TILE_57].y = 96;
	gTileClips[TILE_57].w = TILE_WIDTH;
	gTileClips[TILE_57].h = TILE_HEIGHT;

	gTileClips[TILE_58].x = 416;
	gTileClips[TILE_58].y = 96;
	gTileClips[TILE_58].w = TILE_WIDTH;
	gTileClips[TILE_58].h = TILE_HEIGHT;

	gTileClips[TILE_59].x = 448;
	gTileClips[TILE_59].y = 96;
	gTileClips[TILE_59].w = TILE_WIDTH;
	gTileClips[TILE_59].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_60].x = 0;
	gTileClips[TILE_60].y = 128;
	gTileClips[TILE_60].w = TILE_WIDTH;
	gTileClips[TILE_60].h = TILE_HEIGHT;

	gTileClips[TILE_61].x = 32;
	gTileClips[TILE_61].y = 128;
	gTileClips[TILE_61].w = TILE_WIDTH;
	gTileClips[TILE_61].h = TILE_HEIGHT;

	gTileClips[TILE_62].x = 64;
	gTileClips[TILE_62].y = 128;
	gTileClips[TILE_62].w = TILE_WIDTH;
	gTileClips[TILE_62].h = TILE_HEIGHT;

	gTileClips[TILE_63].x = 96;
	gTileClips[TILE_63].y = 128;
	gTileClips[TILE_63].w = TILE_WIDTH;
	gTileClips[TILE_63].h = TILE_HEIGHT;

	gTileClips[TILE_64].x = 128;
	gTileClips[TILE_64].y = 128;
	gTileClips[TILE_64].w = TILE_WIDTH;
	gTileClips[TILE_64].h = TILE_HEIGHT;

	gTileClips[TILE_65].x = 160;
	gTileClips[TILE_65].y = 128;
	gTileClips[TILE_65].w = TILE_WIDTH;
	gTileClips[TILE_65].h = TILE_HEIGHT;

	gTileClips[TILE_66].x = 192;
	gTileClips[TILE_66].y = 128;
	gTileClips[TILE_66].w = TILE_WIDTH;
	gTileClips[TILE_66].h = TILE_HEIGHT;

	gTileClips[TILE_67].x = 224;
	gTileClips[TILE_67].y = 128;
	gTileClips[TILE_67].w = TILE_WIDTH;
	gTileClips[TILE_67].h = TILE_HEIGHT;

	gTileClips[TILE_68].x = 256;
	gTileClips[TILE_68].y = 128;
	gTileClips[TILE_68].w = TILE_WIDTH;
	gTileClips[TILE_68].h = TILE_HEIGHT;

	gTileClips[TILE_69].x = 288;
	gTileClips[TILE_69].y = 128;
	gTileClips[TILE_69].w = TILE_WIDTH;
	gTileClips[TILE_69].h = TILE_HEIGHT;

	gTileClips[TILE_70].x = 320;
	gTileClips[TILE_70].y = 128;
	gTileClips[TILE_70].w = TILE_WIDTH;
	gTileClips[TILE_70].h = TILE_HEIGHT;

	gTileClips[TILE_71].x = 352;
	gTileClips[TILE_71].y = 128;
	gTileClips[TILE_71].w = TILE_WIDTH;
	gTileClips[TILE_71].h = TILE_HEIGHT;

	gTileClips[TILE_72].x = 384;
	gTileClips[TILE_72].y = 128;
	gTileClips[TILE_72].w = TILE_WIDTH;
	gTileClips[TILE_72].h = TILE_HEIGHT;

	gTileClips[TILE_73].x = 416;
	gTileClips[TILE_73].y = 128;
	gTileClips[TILE_73].w = TILE_WIDTH;
	gTileClips[TILE_73].h = TILE_HEIGHT;

	gTileClips[TILE_74].x = 448;
	gTileClips[TILE_74].y = 128;
	gTileClips[TILE_74].w = TILE_WIDTH;
	gTileClips[TILE_74].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_75].x = 0;
	gTileClips[TILE_75].y = 160;
	gTileClips[TILE_75].w = TILE_WIDTH;
	gTileClips[TILE_75].h = TILE_HEIGHT;

	gTileClips[TILE_76].x = 32;
	gTileClips[TILE_76].y = 160;
	gTileClips[TILE_76].w = TILE_WIDTH;
	gTileClips[TILE_76].h = TILE_HEIGHT;

	gTileClips[TILE_77].x = 64;
	gTileClips[TILE_77].y = 160;
	gTileClips[TILE_77].w = TILE_WIDTH;
	gTileClips[TILE_77].h = TILE_HEIGHT;

	gTileClips[TILE_78].x = 96;
	gTileClips[TILE_78].y = 160;
	gTileClips[TILE_78].w = TILE_WIDTH;
	gTileClips[TILE_78].h = TILE_HEIGHT;

	gTileClips[TILE_79].x = 128;
	gTileClips[TILE_79].y = 160;
	gTileClips[TILE_79].w = TILE_WIDTH;
	gTileClips[TILE_79].h = TILE_HEIGHT;

	gTileClips[TILE_80].x = 160;
	gTileClips[TILE_80].y = 160;
	gTileClips[TILE_80].w = TILE_WIDTH;
	gTileClips[TILE_80].h = TILE_HEIGHT;

	gTileClips[TILE_81].x = 192;
	gTileClips[TILE_81].y = 160;
	gTileClips[TILE_81].w = TILE_WIDTH;
	gTileClips[TILE_81].h = TILE_HEIGHT;

	gTileClips[TILE_82].x = 224;
	gTileClips[TILE_82].y = 160;
	gTileClips[TILE_82].w = TILE_WIDTH;
	gTileClips[TILE_82].h = TILE_HEIGHT;

	gTileClips[TILE_83].x = 256;
	gTileClips[TILE_83].y = 160;
	gTileClips[TILE_83].w = TILE_WIDTH;
	gTileClips[TILE_83].h = TILE_HEIGHT;

	gTileClips[TILE_84].x = 288;
	gTileClips[TILE_84].y = 160;
	gTileClips[TILE_84].w = TILE_WIDTH;
	gTileClips[TILE_84].h = TILE_HEIGHT;

	gTileClips[TILE_85].x = 320;
	gTileClips[TILE_85].y = 160;
	gTileClips[TILE_85].w = TILE_WIDTH;
	gTileClips[TILE_85].h = TILE_HEIGHT;

	gTileClips[TILE_86].x = 352;
	gTileClips[TILE_86].y = 160;
	gTileClips[TILE_86].w = TILE_WIDTH;
	gTileClips[TILE_86].h = TILE_HEIGHT;

	gTileClips[TILE_87].x = 384;
	gTileClips[TILE_87].y = 160;
	gTileClips[TILE_87].w = TILE_WIDTH;
	gTileClips[TILE_87].h = TILE_HEIGHT;

	gTileClips[TILE_88].x = 416;
	gTileClips[TILE_88].y = 160;
	gTileClips[TILE_88].w = TILE_WIDTH;
	gTileClips[TILE_88].h = TILE_HEIGHT;

	gTileClips[TILE_89].x = 448;
	gTileClips[TILE_89].y = 160;
	gTileClips[TILE_89].w = TILE_WIDTH;
	gTileClips[TILE_89].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_90].x = 0;
	gTileClips[TILE_90].y = 192;
	gTileClips[TILE_90].w = TILE_WIDTH;
	gTileClips[TILE_90].h = TILE_HEIGHT;

	gTileClips[TILE_91].x = 32;
	gTileClips[TILE_91].y = 192;
	gTileClips[TILE_91].w = TILE_WIDTH;
	gTileClips[TILE_91].h = TILE_HEIGHT;

	gTileClips[TILE_92].x = 64;
	gTileClips[TILE_92].y = 192;
	gTileClips[TILE_92].w = TILE_WIDTH;
	gTileClips[TILE_92].h = TILE_HEIGHT;

	gTileClips[TILE_93].x = 96;
	gTileClips[TILE_93].y = 192;
	gTileClips[TILE_93].w = TILE_WIDTH;
	gTileClips[TILE_93].h = TILE_HEIGHT;

	gTileClips[TILE_94].x = 128;
	gTileClips[TILE_94].y = 192;
	gTileClips[TILE_94].w = TILE_WIDTH;
	gTileClips[TILE_94].h = TILE_HEIGHT;

	gTileClips[TILE_95].x = 160;
	gTileClips[TILE_95].y = 192;
	gTileClips[TILE_95].w = TILE_WIDTH;
	gTileClips[TILE_95].h = TILE_HEIGHT;

	gTileClips[TILE_96].x = 192;
	gTileClips[TILE_96].y = 192;
	gTileClips[TILE_96].w = TILE_WIDTH;
	gTileClips[TILE_96].h = TILE_HEIGHT;

	gTileClips[TILE_97].x = 224;
	gTileClips[TILE_97].y = 192;
	gTileClips[TILE_97].w = TILE_WIDTH;
	gTileClips[TILE_97].h = TILE_HEIGHT;

	gTileClips[TILE_98].x = 256;
	gTileClips[TILE_98].y = 192;
	gTileClips[TILE_98].w = TILE_WIDTH;
	gTileClips[TILE_98].h = TILE_HEIGHT;

	gTileClips[TILE_99].x = 288;
	gTileClips[TILE_99].y = 192;
	gTileClips[TILE_99].w = TILE_WIDTH;
	gTileClips[TILE_99].h = TILE_HEIGHT;

	gTileClips[TILE_100].x = 320;
	gTileClips[TILE_100].y = 192;
	gTileClips[TILE_100].w = TILE_WIDTH;
	gTileClips[TILE_100].h = TILE_HEIGHT;

	gTileClips[TILE_101].x = 352;
	gTileClips[TILE_101].y = 192;
	gTileClips[TILE_101].w = TILE_WIDTH;
	gTileClips[TILE_101].h = TILE_HEIGHT;

	gTileClips[TILE_102].x = 384;
	gTileClips[TILE_102].y = 192;
	gTileClips[TILE_102].w = TILE_WIDTH;
	gTileClips[TILE_102].h = TILE_HEIGHT;

	gTileClips[TILE_103].x = 416;
	gTileClips[TILE_103].y = 192;
	gTileClips[TILE_103].w = TILE_WIDTH;
	gTileClips[TILE_103].h = TILE_HEIGHT;

	gTileClips[TILE_104].x = 448;
	gTileClips[TILE_104].y = 192;
	gTileClips[TILE_104].w = TILE_WIDTH;
	gTileClips[TILE_104].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_105].x = 0;
	gTileClips[TILE_105].y = 224;
	gTileClips[TILE_105].w = TILE_WIDTH;
	gTileClips[TILE_105].h = TILE_HEIGHT;

	gTileClips[TILE_106].x = 32;
	gTileClips[TILE_106].y = 224;
	gTileClips[TILE_106].w = TILE_WIDTH;
	gTileClips[TILE_106].h = TILE_HEIGHT;

	gTileClips[TILE_107].x = 64;
	gTileClips[TILE_107].y = 224;
	gTileClips[TILE_107].w = TILE_WIDTH;
	gTileClips[TILE_107].h = TILE_HEIGHT;

	gTileClips[TILE_108].x = 96;
	gTileClips[TILE_108].y = 224;
	gTileClips[TILE_108].w = TILE_WIDTH;
	gTileClips[TILE_108].h = TILE_HEIGHT;

	gTileClips[TILE_109].x = 128;
	gTileClips[TILE_109].y = 224;
	gTileClips[TILE_109].w = TILE_WIDTH;
	gTileClips[TILE_109].h = TILE_HEIGHT;

	gTileClips[TILE_110].x = 160;
	gTileClips[TILE_110].y = 224;
	gTileClips[TILE_110].w = TILE_WIDTH;
	gTileClips[TILE_110].h = TILE_HEIGHT;

	gTileClips[TILE_111].x = 192;
	gTileClips[TILE_111].y = 224;
	gTileClips[TILE_111].w = TILE_WIDTH;
	gTileClips[TILE_111].h = TILE_HEIGHT;

	gTileClips[TILE_112].x = 224;
	gTileClips[TILE_112].y = 224;
	gTileClips[TILE_112].w = TILE_WIDTH;
	gTileClips[TILE_112].h = TILE_HEIGHT;

	gTileClips[TILE_113].x = 256;
	gTileClips[TILE_113].y = 224;
	gTileClips[TILE_113].w = TILE_WIDTH;
	gTileClips[TILE_113].h = TILE_HEIGHT;

	gTileClips[TILE_114].x = 288;
	gTileClips[TILE_114].y = 224;
	gTileClips[TILE_114].w = TILE_WIDTH;
	gTileClips[TILE_114].h = TILE_HEIGHT;

	gTileClips[TILE_115].x = 320;
	gTileClips[TILE_115].y = 224;
	gTileClips[TILE_115].w = TILE_WIDTH;
	gTileClips[TILE_115].h = TILE_HEIGHT;

	gTileClips[TILE_116].x = 352;
	gTileClips[TILE_116].y = 224;
	gTileClips[TILE_116].w = TILE_WIDTH;
	gTileClips[TILE_116].h = TILE_HEIGHT;

	gTileClips[TILE_117].x = 384;
	gTileClips[TILE_117].y = 224;
	gTileClips[TILE_117].w = TILE_WIDTH;
	gTileClips[TILE_117].h = TILE_HEIGHT;

	gTileClips[TILE_118].x = 416;
	gTileClips[TILE_118].y = 224;
	gTileClips[TILE_118].w = TILE_WIDTH;
	gTileClips[TILE_118].h = TILE_HEIGHT;

	gTileClips[TILE_119].x = 448;
	gTileClips[TILE_119].y = 224;
	gTileClips[TILE_119].w = TILE_WIDTH;
	gTileClips[TILE_119].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_120].x = 0;
	gTileClips[TILE_120].y = 256;
	gTileClips[TILE_120].w = TILE_WIDTH;
	gTileClips[TILE_120].h = TILE_HEIGHT;

	gTileClips[TILE_121].x = 32;
	gTileClips[TILE_121].y = 256;
	gTileClips[TILE_121].w = TILE_WIDTH;
	gTileClips[TILE_121].h = TILE_HEIGHT;

	gTileClips[TILE_122].x = 64;
	gTileClips[TILE_122].y = 256;
	gTileClips[TILE_122].w = TILE_WIDTH;
	gTileClips[TILE_122].h = TILE_HEIGHT;

	gTileClips[TILE_123].x = 96;
	gTileClips[TILE_123].y = 256;
	gTileClips[TILE_123].w = TILE_WIDTH;
	gTileClips[TILE_123].h = TILE_HEIGHT;

	gTileClips[TILE_124].x = 128;
	gTileClips[TILE_124].y = 256;
	gTileClips[TILE_124].w = TILE_WIDTH;
	gTileClips[TILE_124].h = TILE_HEIGHT;

	gTileClips[TILE_125].x = 160;
	gTileClips[TILE_125].y = 256;
	gTileClips[TILE_125].w = TILE_WIDTH;
	gTileClips[TILE_125].h = TILE_HEIGHT;

	gTileClips[TILE_126].x = 192;
	gTileClips[TILE_126].y = 256;
	gTileClips[TILE_126].w = TILE_WIDTH;
	gTileClips[TILE_126].h = TILE_HEIGHT;

	gTileClips[TILE_127].x = 224;
	gTileClips[TILE_127].y = 256;
	gTileClips[TILE_127].w = TILE_WIDTH;
	gTileClips[TILE_127].h = TILE_HEIGHT;

	gTileClips[TILE_128].x = 256;
	gTileClips[TILE_128].y = 256;
	gTileClips[TILE_128].w = TILE_WIDTH;
	gTileClips[TILE_128].h = TILE_HEIGHT;

	gTileClips[TILE_129].x = 288;
	gTileClips[TILE_129].y = 256;
	gTileClips[TILE_129].w = TILE_WIDTH;
	gTileClips[TILE_129].h = TILE_HEIGHT;

	gTileClips[TILE_130].x = 320;
	gTileClips[TILE_130].y = 256;
	gTileClips[TILE_130].w = TILE_WIDTH;
	gTileClips[TILE_130].h = TILE_HEIGHT;

	gTileClips[TILE_131].x = 352;
	gTileClips[TILE_131].y = 256;
	gTileClips[TILE_131].w = TILE_WIDTH;
	gTileClips[TILE_131].h = TILE_HEIGHT;

	gTileClips[TILE_132].x = 384;
	gTileClips[TILE_132].y = 256;
	gTileClips[TILE_132].w = TILE_WIDTH;
	gTileClips[TILE_132].h = TILE_HEIGHT;

	gTileClips[TILE_133].x = 416;
	gTileClips[TILE_133].y = 256;
	gTileClips[TILE_133].w = TILE_WIDTH;
	gTileClips[TILE_133].h = TILE_HEIGHT;

	gTileClips[TILE_134].x = 448;
	gTileClips[TILE_134].y = 256;
	gTileClips[TILE_134].w = TILE_WIDTH;
	gTileClips[TILE_134].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_135].x = 0;
	gTileClips[TILE_135].y = 288;
	gTileClips[TILE_135].w = TILE_WIDTH;
	gTileClips[TILE_135].h = TILE_HEIGHT;

	gTileClips[TILE_136].x = 32;
	gTileClips[TILE_136].y = 288;
	gTileClips[TILE_136].w = TILE_WIDTH;
	gTileClips[TILE_136].h = TILE_HEIGHT;

	gTileClips[TILE_137].x = 64;
	gTileClips[TILE_137].y = 288;
	gTileClips[TILE_137].w = TILE_WIDTH;
	gTileClips[TILE_137].h = TILE_HEIGHT;

	gTileClips[TILE_138].x = 96;
	gTileClips[TILE_138].y = 288;
	gTileClips[TILE_138].w = TILE_WIDTH;
	gTileClips[TILE_138].h = TILE_HEIGHT;

	gTileClips[TILE_139].x = 128;
	gTileClips[TILE_139].y = 288;
	gTileClips[TILE_139].w = TILE_WIDTH;
	gTileClips[TILE_139].h = TILE_HEIGHT;

	gTileClips[TILE_140].x = 160;
	gTileClips[TILE_140].y = 288;
	gTileClips[TILE_140].w = TILE_WIDTH;
	gTileClips[TILE_140].h = TILE_HEIGHT;

	gTileClips[TILE_141].x = 192;
	gTileClips[TILE_141].y = 288;
	gTileClips[TILE_141].w = TILE_WIDTH;
	gTileClips[TILE_141].h = TILE_HEIGHT;

	gTileClips[TILE_142].x = 224;
	gTileClips[TILE_142].y = 288;
	gTileClips[TILE_142].w = TILE_WIDTH;
	gTileClips[TILE_142].h = TILE_HEIGHT;

	gTileClips[TILE_143].x = 256;
	gTileClips[TILE_143].y = 288;
	gTileClips[TILE_143].w = TILE_WIDTH;
	gTileClips[TILE_143].h = TILE_HEIGHT;

	gTileClips[TILE_144].x = 288;
	gTileClips[TILE_144].y = 288;
	gTileClips[TILE_144].w = TILE_WIDTH;
	gTileClips[TILE_144].h = TILE_HEIGHT;

	gTileClips[TILE_145].x = 320;
	gTileClips[TILE_145].y = 288;
	gTileClips[TILE_145].w = TILE_WIDTH;
	gTileClips[TILE_145].h = TILE_HEIGHT;

	gTileClips[TILE_146].x = 352;
	gTileClips[TILE_146].y = 288;
	gTileClips[TILE_146].w = TILE_WIDTH;
	gTileClips[TILE_146].h = TILE_HEIGHT;

	gTileClips[TILE_147].x = 384;
	gTileClips[TILE_147].y = 288;
	gTileClips[TILE_147].w = TILE_WIDTH;
	gTileClips[TILE_147].h = TILE_HEIGHT;

	gTileClips[TILE_148].x = 416;
	gTileClips[TILE_148].y = 288;
	gTileClips[TILE_148].w = TILE_WIDTH;
	gTileClips[TILE_148].h = TILE_HEIGHT;

	gTileClips[TILE_149].x = 448;
	gTileClips[TILE_149].y = 288;
	gTileClips[TILE_149].w = TILE_WIDTH;
	gTileClips[TILE_149].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_150].x = 0;
	gTileClips[TILE_150].y = 320;
	gTileClips[TILE_150].w = TILE_WIDTH;
	gTileClips[TILE_150].h = TILE_HEIGHT;

	gTileClips[TILE_151].x = 32;
	gTileClips[TILE_151].y = 320;
	gTileClips[TILE_151].w = TILE_WIDTH;
	gTileClips[TILE_151].h = TILE_HEIGHT;

	gTileClips[TILE_152].x = 64;
	gTileClips[TILE_152].y = 320;
	gTileClips[TILE_152].w = TILE_WIDTH;
	gTileClips[TILE_152].h = TILE_HEIGHT;

	gTileClips[TILE_153].x = 96;
	gTileClips[TILE_153].y = 320;
	gTileClips[TILE_153].w = TILE_WIDTH;
	gTileClips[TILE_153].h = TILE_HEIGHT;

	gTileClips[TILE_154].x = 128;
	gTileClips[TILE_154].y = 320;
	gTileClips[TILE_154].w = TILE_WIDTH;
	gTileClips[TILE_154].h = TILE_HEIGHT;

	gTileClips[TILE_155].x = 160;
	gTileClips[TILE_155].y = 320;
	gTileClips[TILE_155].w = TILE_WIDTH;
	gTileClips[TILE_155].h = TILE_HEIGHT;

	gTileClips[TILE_156].x = 192;
	gTileClips[TILE_156].y = 320;
	gTileClips[TILE_156].w = TILE_WIDTH;
	gTileClips[TILE_156].h = TILE_HEIGHT;

	gTileClips[TILE_157].x = 224;
	gTileClips[TILE_157].y = 320;
	gTileClips[TILE_157].w = TILE_WIDTH;
	gTileClips[TILE_157].h = TILE_HEIGHT;

	gTileClips[TILE_158].x = 256;
	gTileClips[TILE_158].y = 320;
	gTileClips[TILE_158].w = TILE_WIDTH;
	gTileClips[TILE_158].h = TILE_HEIGHT;

	gTileClips[TILE_159].x = 288;
	gTileClips[TILE_159].y = 320;
	gTileClips[TILE_159].w = TILE_WIDTH;
	gTileClips[TILE_159].h = TILE_HEIGHT;

	gTileClips[TILE_160].x = 320;
	gTileClips[TILE_160].y = 320;
	gTileClips[TILE_160].w = TILE_WIDTH;
	gTileClips[TILE_160].h = TILE_HEIGHT;

	gTileClips[TILE_161].x = 352;
	gTileClips[TILE_161].y = 320;
	gTileClips[TILE_161].w = TILE_WIDTH;
	gTileClips[TILE_161].h = TILE_HEIGHT;

	gTileClips[TILE_162].x = 384;
	gTileClips[TILE_162].y = 320;
	gTileClips[TILE_162].w = TILE_WIDTH;
	gTileClips[TILE_162].h = TILE_HEIGHT;

	gTileClips[TILE_163].x = 416;
	gTileClips[TILE_163].y = 320;
	gTileClips[TILE_163].w = TILE_WIDTH;
	gTileClips[TILE_163].h = TILE_HEIGHT;

	gTileClips[TILE_164].x = 448;
	gTileClips[TILE_164].y = 320;
	gTileClips[TILE_164].w = TILE_WIDTH;
	gTileClips[TILE_164].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_165].x = 0;
	gTileClips[TILE_165].y = 352;
	gTileClips[TILE_165].w = TILE_WIDTH;
	gTileClips[TILE_165].h = TILE_HEIGHT;

	gTileClips[TILE_166].x = 32;
	gTileClips[TILE_166].y = 352;
	gTileClips[TILE_166].w = TILE_WIDTH;
	gTileClips[TILE_166].h = TILE_HEIGHT;

	gTileClips[TILE_167].x = 64;
	gTileClips[TILE_167].y = 352;
	gTileClips[TILE_167].w = TILE_WIDTH;
	gTileClips[TILE_167].h = TILE_HEIGHT;

	gTileClips[TILE_168].x = 96;
	gTileClips[TILE_168].y = 352;
	gTileClips[TILE_168].w = TILE_WIDTH;
	gTileClips[TILE_168].h = TILE_HEIGHT;

	gTileClips[TILE_169].x = 128;
	gTileClips[TILE_169].y = 352;
	gTileClips[TILE_169].w = TILE_WIDTH;
	gTileClips[TILE_169].h = TILE_HEIGHT;

	gTileClips[TILE_170].x = 160;
	gTileClips[TILE_170].y = 352;
	gTileClips[TILE_170].w = TILE_WIDTH;
	gTileClips[TILE_170].h = TILE_HEIGHT;

	gTileClips[TILE_171].x = 192;
	gTileClips[TILE_171].y = 352;
	gTileClips[TILE_171].w = TILE_WIDTH;
	gTileClips[TILE_171].h = TILE_HEIGHT;

	gTileClips[TILE_172].x = 224;
	gTileClips[TILE_172].y = 352;
	gTileClips[TILE_172].w = TILE_WIDTH;
	gTileClips[TILE_172].h = TILE_HEIGHT;

	gTileClips[TILE_173].x = 256;
	gTileClips[TILE_173].y = 352;
	gTileClips[TILE_173].w = TILE_WIDTH;
	gTileClips[TILE_173].h = TILE_HEIGHT;

	gTileClips[TILE_174].x = 288;
	gTileClips[TILE_174].y = 352;
	gTileClips[TILE_174].w = TILE_WIDTH;
	gTileClips[TILE_174].h = TILE_HEIGHT;

	gTileClips[TILE_175].x = 320;
	gTileClips[TILE_175].y = 352;
	gTileClips[TILE_175].w = TILE_WIDTH;
	gTileClips[TILE_175].h = TILE_HEIGHT;

	gTileClips[TILE_176].x = 352;
	gTileClips[TILE_176].y = 352;
	gTileClips[TILE_176].w = TILE_WIDTH;
	gTileClips[TILE_176].h = TILE_HEIGHT;

	gTileClips[TILE_177].x = 384;
	gTileClips[TILE_177].y = 352;
	gTileClips[TILE_177].w = TILE_WIDTH;
	gTileClips[TILE_177].h = TILE_HEIGHT;

	gTileClips[TILE_178].x = 416;
	gTileClips[TILE_178].y = 352;
	gTileClips[TILE_178].w = TILE_WIDTH;
	gTileClips[TILE_178].h = TILE_HEIGHT;

	gTileClips[TILE_179].x = 448;
	gTileClips[TILE_179].y = 352;
	gTileClips[TILE_179].w = TILE_WIDTH;
	gTileClips[TILE_179].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_180].x = 0;
	gTileClips[TILE_180].y = 384;
	gTileClips[TILE_180].w = TILE_WIDTH;
	gTileClips[TILE_180].h = TILE_HEIGHT;

	gTileClips[TILE_181].x = 32;
	gTileClips[TILE_181].y = 384;
	gTileClips[TILE_181].w = TILE_WIDTH;
	gTileClips[TILE_181].h = TILE_HEIGHT;

	gTileClips[TILE_182].x = 64;
	gTileClips[TILE_182].y = 384;
	gTileClips[TILE_182].w = TILE_WIDTH;
	gTileClips[TILE_182].h = TILE_HEIGHT;

	gTileClips[TILE_183].x = 96;
	gTileClips[TILE_183].y = 384;
	gTileClips[TILE_183].w = TILE_WIDTH;
	gTileClips[TILE_183].h = TILE_HEIGHT;

	gTileClips[TILE_184].x = 128;
	gTileClips[TILE_184].y = 384;
	gTileClips[TILE_184].w = TILE_WIDTH;
	gTileClips[TILE_184].h = TILE_HEIGHT;

	gTileClips[TILE_185].x = 160;
	gTileClips[TILE_185].y = 384;
	gTileClips[TILE_185].w = TILE_WIDTH;
	gTileClips[TILE_185].h = TILE_HEIGHT;

	gTileClips[TILE_186].x = 192;
	gTileClips[TILE_186].y = 384;
	gTileClips[TILE_186].w = TILE_WIDTH;
	gTileClips[TILE_186].h = TILE_HEIGHT;

	gTileClips[TILE_187].x = 224;
	gTileClips[TILE_187].y = 384;
	gTileClips[TILE_187].w = TILE_WIDTH;
	gTileClips[TILE_187].h = TILE_HEIGHT;

	gTileClips[TILE_188].x = 256;
	gTileClips[TILE_188].y = 384;
	gTileClips[TILE_188].w = TILE_WIDTH;
	gTileClips[TILE_188].h = TILE_HEIGHT;

	gTileClips[TILE_189].x = 288;
	gTileClips[TILE_189].y = 384;
	gTileClips[TILE_189].w = TILE_WIDTH;
	gTileClips[TILE_189].h = TILE_HEIGHT;

	gTileClips[TILE_190].x = 320;
	gTileClips[TILE_190].y = 384;
	gTileClips[TILE_190].w = TILE_WIDTH;
	gTileClips[TILE_190].h = TILE_HEIGHT;

	gTileClips[TILE_191].x = 352;
	gTileClips[TILE_191].y = 384;
	gTileClips[TILE_191].w = TILE_WIDTH;
	gTileClips[TILE_191].h = TILE_HEIGHT;

	gTileClips[TILE_192].x = 384;
	gTileClips[TILE_192].y = 384;
	gTileClips[TILE_192].w = TILE_WIDTH;
	gTileClips[TILE_192].h = TILE_HEIGHT;

	gTileClips[TILE_193].x = 416;
	gTileClips[TILE_193].y = 384;
	gTileClips[TILE_193].w = TILE_WIDTH;
	gTileClips[TILE_193].h = TILE_HEIGHT;

	gTileClips[TILE_194].x = 448;
	gTileClips[TILE_194].y = 384;
	gTileClips[TILE_194].w = TILE_WIDTH;
	gTileClips[TILE_194].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_195].x = 0;
	gTileClips[TILE_195].y = 416;
	gTileClips[TILE_195].w = TILE_WIDTH;
	gTileClips[TILE_195].h = TILE_HEIGHT;

	gTileClips[TILE_196].x = 32;
	gTileClips[TILE_196].y = 416;
	gTileClips[TILE_196].w = TILE_WIDTH;
	gTileClips[TILE_196].h = TILE_HEIGHT;

	gTileClips[TILE_197].x = 64;
	gTileClips[TILE_197].y = 416;
	gTileClips[TILE_197].w = TILE_WIDTH;
	gTileClips[TILE_197].h = TILE_HEIGHT;

	gTileClips[TILE_198].x = 96;
	gTileClips[TILE_198].y = 416;
	gTileClips[TILE_198].w = TILE_WIDTH;
	gTileClips[TILE_198].h = TILE_HEIGHT;

	gTileClips[TILE_199].x = 128;
	gTileClips[TILE_199].y = 416;
	gTileClips[TILE_199].w = TILE_WIDTH;
	gTileClips[TILE_199].h = TILE_HEIGHT;

	gTileClips[TILE_200].x = 160;
	gTileClips[TILE_200].y = 416;
	gTileClips[TILE_200].w = TILE_WIDTH;
	gTileClips[TILE_200].h = TILE_HEIGHT;

	gTileClips[TILE_201].x = 192;
	gTileClips[TILE_201].y = 416;
	gTileClips[TILE_201].w = TILE_WIDTH;
	gTileClips[TILE_201].h = TILE_HEIGHT;

	gTileClips[TILE_202].x = 224;
	gTileClips[TILE_202].y = 416;
	gTileClips[TILE_202].w = TILE_WIDTH;
	gTileClips[TILE_202].h = TILE_HEIGHT;

	gTileClips[TILE_203].x = 256;
	gTileClips[TILE_203].y = 416;
	gTileClips[TILE_203].w = TILE_WIDTH;
	gTileClips[TILE_203].h = TILE_HEIGHT;

	gTileClips[TILE_204].x = 288;
	gTileClips[TILE_204].y = 416;
	gTileClips[TILE_204].w = TILE_WIDTH;
	gTileClips[TILE_204].h = TILE_HEIGHT;

	gTileClips[TILE_205].x = 320;
	gTileClips[TILE_205].y = 416;
	gTileClips[TILE_205].w = TILE_WIDTH;
	gTileClips[TILE_205].h = TILE_HEIGHT;

	gTileClips[TILE_206].x = 352;
	gTileClips[TILE_206].y = 416;
	gTileClips[TILE_206].w = TILE_WIDTH;
	gTileClips[TILE_206].h = TILE_HEIGHT;

	gTileClips[TILE_207].x = 384;
	gTileClips[TILE_207].y = 416;
	gTileClips[TILE_207].w = TILE_WIDTH;
	gTileClips[TILE_207].h = TILE_HEIGHT;

	gTileClips[TILE_208].x = 416;
	gTileClips[TILE_208].y = 416;
	gTileClips[TILE_208].w = TILE_WIDTH;
	gTileClips[TILE_208].h = TILE_HEIGHT;

	gTileClips[TILE_209].x = 448;
	gTileClips[TILE_209].y = 416;
	gTileClips[TILE_209].w = TILE_WIDTH;
	gTileClips[TILE_209].h = TILE_HEIGHT;
	//------------------------------------------------

	gTileClips[TILE_210].x = 0;
	gTileClips[TILE_210].y = 448;
	gTileClips[TILE_210].w = TILE_WIDTH;
	gTileClips[TILE_210].h = TILE_HEIGHT;

	gTileClips[TILE_211].x = 32;
	gTileClips[TILE_211].y = 448;
	gTileClips[TILE_211].w = TILE_WIDTH;
	gTileClips[TILE_211].h = TILE_HEIGHT;

	gTileClips[TILE_212].x = 64;
	gTileClips[TILE_212].y = 448;
	gTileClips[TILE_212].w = TILE_WIDTH;
	gTileClips[TILE_212].h = TILE_HEIGHT;

	gTileClips[TILE_213].x = 96;
	gTileClips[TILE_213].y = 448;
	gTileClips[TILE_213].w = TILE_WIDTH;
	gTileClips[TILE_213].h = TILE_HEIGHT;

	gTileClips[TILE_214].x = 128;
	gTileClips[TILE_214].y = 448;
	gTileClips[TILE_214].w = TILE_WIDTH;
	gTileClips[TILE_214].h = TILE_HEIGHT;

	gTileClips[TILE_215].x = 160;
	gTileClips[TILE_215].y = 448;
	gTileClips[TILE_215].w = TILE_WIDTH;
	gTileClips[TILE_215].h = TILE_HEIGHT;

	gTileClips[TILE_216].x = 192;
	gTileClips[TILE_216].y = 448;
	gTileClips[TILE_216].w = TILE_WIDTH;
	gTileClips[TILE_216].h = TILE_HEIGHT;

	gTileClips[TILE_217].x = 224;
	gTileClips[TILE_217].y = 448;
	gTileClips[TILE_217].w = TILE_WIDTH;
	gTileClips[TILE_217].h = TILE_HEIGHT;

	gTileClips[TILE_218].x = 256;
	gTileClips[TILE_218].y = 448;
	gTileClips[TILE_218].w = TILE_WIDTH;
	gTileClips[TILE_218].h = TILE_HEIGHT;

	gTileClips[TILE_219].x = 288;
	gTileClips[TILE_219].y = 448;
	gTileClips[TILE_219].w = TILE_WIDTH;
	gTileClips[TILE_219].h = TILE_HEIGHT;

	gTileClips[TILE_220].x = 320;
	gTileClips[TILE_220].y = 448;
	gTileClips[TILE_220].w = TILE_WIDTH;
	gTileClips[TILE_220].h = TILE_HEIGHT;

	gTileClips[TILE_221].x = 352;
	gTileClips[TILE_221].y = 448;
	gTileClips[TILE_221].w = TILE_WIDTH;
	gTileClips[TILE_221].h = TILE_HEIGHT;

	gTileClips[TILE_222].x = 384;
	gTileClips[TILE_222].y = 448;
	gTileClips[TILE_222].w = TILE_WIDTH;
	gTileClips[TILE_222].h = TILE_HEIGHT;

	gTileClips[TILE_223].x = 416;
	gTileClips[TILE_223].y = 448;
	gTileClips[TILE_223].w = TILE_WIDTH;
	gTileClips[TILE_223].h = TILE_HEIGHT;

	gTileClips[TILE_224].x = 448;
	gTileClips[TILE_224].y = 448;
	gTileClips[TILE_224].w = TILE_WIDTH;
	gTileClips[TILE_244].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_225].x = 0;
	gTileClips[TILE_225].y = 480;
	gTileClips[TILE_225].w = TILE_WIDTH;
	gTileClips[TILE_225].h = TILE_HEIGHT;

	gTileClips[TILE_226].x = 32;
	gTileClips[TILE_226].y = 480;
	gTileClips[TILE_226].w = TILE_WIDTH;
	gTileClips[TILE_226].h = TILE_HEIGHT;

	gTileClips[TILE_227].x = 64;
	gTileClips[TILE_227].y = 480;
	gTileClips[TILE_227].w = TILE_WIDTH;
	gTileClips[TILE_227].h = TILE_HEIGHT;

	gTileClips[TILE_228].x = 96;
	gTileClips[TILE_228].y = 480;
	gTileClips[TILE_228].w = TILE_WIDTH;
	gTileClips[TILE_228].h = TILE_HEIGHT;

	gTileClips[TILE_229].x = 128;
	gTileClips[TILE_229].y = 480;
	gTileClips[TILE_229].w = TILE_WIDTH;
	gTileClips[TILE_229].h = TILE_HEIGHT;

	gTileClips[TILE_230].x = 160;
	gTileClips[TILE_230].y = 480;
	gTileClips[TILE_230].w = TILE_WIDTH;
	gTileClips[TILE_230].h = TILE_HEIGHT;

	gTileClips[TILE_231].x = 192;
	gTileClips[TILE_231].y = 480;
	gTileClips[TILE_231].w = TILE_WIDTH;
	gTileClips[TILE_231].h = TILE_HEIGHT;

	gTileClips[TILE_232].x = 224;
	gTileClips[TILE_232].y = 480;
	gTileClips[TILE_232].w = TILE_WIDTH;
	gTileClips[TILE_232].h = TILE_HEIGHT;

	gTileClips[TILE_233].x = 256;
	gTileClips[TILE_233].y = 480;
	gTileClips[TILE_233].w = TILE_WIDTH;
	gTileClips[TILE_233].h = TILE_HEIGHT;

	gTileClips[TILE_234].x = 288;
	gTileClips[TILE_234].y = 480;
	gTileClips[TILE_234].w = TILE_WIDTH;
	gTileClips[TILE_234].h = TILE_HEIGHT;

	gTileClips[TILE_235].x = 320;
	gTileClips[TILE_235].y = 480;
	gTileClips[TILE_235].w = TILE_WIDTH;
	gTileClips[TILE_235].h = TILE_HEIGHT;

	gTileClips[TILE_236].x = 352;
	gTileClips[TILE_236].y = 480;
	gTileClips[TILE_236].w = TILE_WIDTH;
	gTileClips[TILE_236].h = TILE_HEIGHT;

	gTileClips[TILE_237].x = 384;
	gTileClips[TILE_237].y = 480;
	gTileClips[TILE_237].w = TILE_WIDTH;
	gTileClips[TILE_237].h = TILE_HEIGHT;

	gTileClips[TILE_238].x = 416;
	gTileClips[TILE_238].y = 480;
	gTileClips[TILE_238].w = TILE_WIDTH;
	gTileClips[TILE_238].h = TILE_HEIGHT;

	gTileClips[TILE_239].x = 448;
	gTileClips[TILE_239].y = 480;
	gTileClips[TILE_239].w = TILE_WIDTH;
	gTileClips[TILE_239].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_240].x = 0;
	gTileClips[TILE_240].y = 512;
	gTileClips[TILE_240].w = TILE_WIDTH;
	gTileClips[TILE_240].h = TILE_HEIGHT;

	gTileClips[TILE_241].x = 32;
	gTileClips[TILE_241].y = 512;
	gTileClips[TILE_241].w = TILE_WIDTH;
	gTileClips[TILE_241].h = TILE_HEIGHT;

	gTileClips[TILE_242].x = 64;
	gTileClips[TILE_242].y = 512;
	gTileClips[TILE_242].w = TILE_WIDTH;
	gTileClips[TILE_242].h = TILE_HEIGHT;

	gTileClips[TILE_243].x = 96;
	gTileClips[TILE_243].y = 512;
	gTileClips[TILE_243].w = TILE_WIDTH;
	gTileClips[TILE_243].h = TILE_HEIGHT;

	gTileClips[TILE_244].x = 128;
	gTileClips[TILE_244].y = 512;
	gTileClips[TILE_244].w = TILE_WIDTH;
	gTileClips[TILE_244].h = TILE_HEIGHT;

	gTileClips[TILE_245].x = 160;
	gTileClips[TILE_245].y = 512;
	gTileClips[TILE_245].w = TILE_WIDTH;
	gTileClips[TILE_245].h = TILE_HEIGHT;

	gTileClips[TILE_246].x = 192;
	gTileClips[TILE_246].y = 512;
	gTileClips[TILE_246].w = TILE_WIDTH;
	gTileClips[TILE_246].h = TILE_HEIGHT;

	gTileClips[TILE_247].x = 224;
	gTileClips[TILE_247].y = 512;
	gTileClips[TILE_247].w = TILE_WIDTH;
	gTileClips[TILE_247].h = TILE_HEIGHT;

	gTileClips[TILE_248].x = 256;
	gTileClips[TILE_248].y = 512;
	gTileClips[TILE_248].w = TILE_WIDTH;
	gTileClips[TILE_248].h = TILE_HEIGHT;

	gTileClips[TILE_249].x = 288;
	gTileClips[TILE_249].y = 512;
	gTileClips[TILE_249].w = TILE_WIDTH;
	gTileClips[TILE_249].h = TILE_HEIGHT;

	gTileClips[TILE_250].x = 320;
	gTileClips[TILE_250].y = 512;
	gTileClips[TILE_250].w = TILE_WIDTH;
	gTileClips[TILE_250].h = TILE_HEIGHT;

	gTileClips[TILE_251].x = 352;
	gTileClips[TILE_251].y = 512;
	gTileClips[TILE_251].w = TILE_WIDTH;
	gTileClips[TILE_251].h = TILE_HEIGHT;

	gTileClips[TILE_252].x = 384;
	gTileClips[TILE_252].y = 512;
	gTileClips[TILE_252].w = TILE_WIDTH;
	gTileClips[TILE_252].h = TILE_HEIGHT;

	gTileClips[TILE_253].x = 416;
	gTileClips[TILE_253].y = 512;
	gTileClips[TILE_253].w = TILE_WIDTH;
	gTileClips[TILE_253].h = TILE_HEIGHT;

	gTileClips[TILE_254].x = 448;
	gTileClips[TILE_254].y = 512;
	gTileClips[TILE_254].w = TILE_WIDTH;
	gTileClips[TILE_254].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_255].x = 0;
	gTileClips[TILE_255].y = 544;
	gTileClips[TILE_255].w = TILE_WIDTH;
	gTileClips[TILE_255].h = TILE_HEIGHT;

	gTileClips[TILE_256].x = 32;
	gTileClips[TILE_256].y = 544;
	gTileClips[TILE_256].w = TILE_WIDTH;
	gTileClips[TILE_256].h = TILE_HEIGHT;

	gTileClips[TILE_257].x = 64;
	gTileClips[TILE_257].y = 544;
	gTileClips[TILE_257].w = TILE_WIDTH;
	gTileClips[TILE_257].h = TILE_HEIGHT;

	gTileClips[TILE_258].x = 96;
	gTileClips[TILE_258].y = 544;
	gTileClips[TILE_258].w = TILE_WIDTH;
	gTileClips[TILE_258].h = TILE_HEIGHT;

	gTileClips[TILE_259].x = 128;
	gTileClips[TILE_259].y = 544;
	gTileClips[TILE_259].w = TILE_WIDTH;
	gTileClips[TILE_259].h = TILE_HEIGHT;

	gTileClips[TILE_260].x = 160;
	gTileClips[TILE_260].y = 544;
	gTileClips[TILE_260].w = TILE_WIDTH;
	gTileClips[TILE_260].h = TILE_HEIGHT;

	gTileClips[TILE_261].x = 192;
	gTileClips[TILE_261].y = 544;
	gTileClips[TILE_261].w = TILE_WIDTH;
	gTileClips[TILE_261].h = TILE_HEIGHT;

	gTileClips[TILE_262].x = 224;
	gTileClips[TILE_262].y = 544;
	gTileClips[TILE_262].w = TILE_WIDTH;
	gTileClips[TILE_262].h = TILE_HEIGHT;

	gTileClips[TILE_263].x = 256;
	gTileClips[TILE_263].y = 544;
	gTileClips[TILE_263].w = TILE_WIDTH;
	gTileClips[TILE_263].h = TILE_HEIGHT;

	gTileClips[TILE_264].x = 288;
	gTileClips[TILE_264].y = 544;
	gTileClips[TILE_264].w = TILE_WIDTH;
	gTileClips[TILE_264].h = TILE_HEIGHT;

	gTileClips[TILE_265].x = 320;
	gTileClips[TILE_265].y = 544;
	gTileClips[TILE_265].w = TILE_WIDTH;
	gTileClips[TILE_265].h = TILE_HEIGHT;

	gTileClips[TILE_266].x = 352;
	gTileClips[TILE_266].y = 544;
	gTileClips[TILE_266].w = TILE_WIDTH;
	gTileClips[TILE_266].h = TILE_HEIGHT;

	gTileClips[TILE_267].x = 384;
	gTileClips[TILE_267].y = 544;
	gTileClips[TILE_267].w = TILE_WIDTH;
	gTileClips[TILE_267].h = TILE_HEIGHT;

	gTileClips[TILE_268].x = 416;
	gTileClips[TILE_268].y = 544;
	gTileClips[TILE_268].w = TILE_WIDTH;
	gTileClips[TILE_268].h = TILE_HEIGHT;

	gTileClips[TILE_269].x = 448;
	gTileClips[TILE_269].y = 544;
	gTileClips[TILE_269].w = TILE_WIDTH;
	gTileClips[TILE_269].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_270].x = 0;
	gTileClips[TILE_270].y = 576;
	gTileClips[TILE_270].w = TILE_WIDTH;
	gTileClips[TILE_270].h = TILE_HEIGHT;

	gTileClips[TILE_271].x = 32;
	gTileClips[TILE_271].y = 576;
	gTileClips[TILE_271].w = TILE_WIDTH;
	gTileClips[TILE_271].h = TILE_HEIGHT;

	gTileClips[TILE_272].x = 64;
	gTileClips[TILE_272].y = 576;
	gTileClips[TILE_272].w = TILE_WIDTH;
	gTileClips[TILE_272].h = TILE_HEIGHT;

	gTileClips[TILE_273].x = 96;
	gTileClips[TILE_273].y = 576;
	gTileClips[TILE_273].w = TILE_WIDTH;
	gTileClips[TILE_273].h = TILE_HEIGHT;

	gTileClips[TILE_274].x = 128;
	gTileClips[TILE_274].y = 576;
	gTileClips[TILE_274].w = TILE_WIDTH;
	gTileClips[TILE_274].h = TILE_HEIGHT;

	gTileClips[TILE_275].x = 160;
	gTileClips[TILE_275].y = 576;
	gTileClips[TILE_275].w = TILE_WIDTH;
	gTileClips[TILE_275].h = TILE_HEIGHT;

	gTileClips[TILE_276].x = 192;
	gTileClips[TILE_276].y = 576;
	gTileClips[TILE_276].w = TILE_WIDTH;
	gTileClips[TILE_276].h = TILE_HEIGHT;

	gTileClips[TILE_277].x = 224;
	gTileClips[TILE_277].y = 576;
	gTileClips[TILE_277].w = TILE_WIDTH;
	gTileClips[TILE_277].h = TILE_HEIGHT;

	gTileClips[TILE_278].x = 256;
	gTileClips[TILE_278].y = 576;
	gTileClips[TILE_278].w = TILE_WIDTH;
	gTileClips[TILE_278].h = TILE_HEIGHT;

	gTileClips[TILE_279].x = 288;
	gTileClips[TILE_279].y = 576;
	gTileClips[TILE_279].w = TILE_WIDTH;
	gTileClips[TILE_279].h = TILE_HEIGHT;

	gTileClips[TILE_280].x = 320;
	gTileClips[TILE_280].y = 576;
	gTileClips[TILE_280].w = TILE_WIDTH;
	gTileClips[TILE_280].h = TILE_HEIGHT;

	gTileClips[TILE_281].x = 352;
	gTileClips[TILE_281].y = 576;
	gTileClips[TILE_281].w = TILE_WIDTH;
	gTileClips[TILE_281].h = TILE_HEIGHT;

	gTileClips[TILE_282].x = 384;
	gTileClips[TILE_282].y = 576;
	gTileClips[TILE_282].w = TILE_WIDTH;
	gTileClips[TILE_282].h = TILE_HEIGHT;

	gTileClips[TILE_283].x = 416;
	gTileClips[TILE_283].y = 576;
	gTileClips[TILE_283].w = TILE_WIDTH;
	gTileClips[TILE_283].h = TILE_HEIGHT;

	gTileClips[TILE_284].x = 448;
	gTileClips[TILE_284].y = 576;
	gTileClips[TILE_284].w = TILE_WIDTH;
	gTileClips[TILE_284].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_285].x = 0;
	gTileClips[TILE_285].y = 608;
	gTileClips[TILE_285].w = TILE_WIDTH;
	gTileClips[TILE_285].h = TILE_HEIGHT;

	gTileClips[TILE_286].x = 32;
	gTileClips[TILE_286].y = 608;
	gTileClips[TILE_286].w = TILE_WIDTH;
	gTileClips[TILE_286].h = TILE_HEIGHT;

	gTileClips[TILE_287].x = 64;
	gTileClips[TILE_287].y = 608;
	gTileClips[TILE_287].w = TILE_WIDTH;
	gTileClips[TILE_287].h = TILE_HEIGHT;

	gTileClips[TILE_288].x = 96;
	gTileClips[TILE_288].y = 608;
	gTileClips[TILE_288].w = TILE_WIDTH;
	gTileClips[TILE_288].h = TILE_HEIGHT;

	gTileClips[TILE_289].x = 128;
	gTileClips[TILE_289].y = 608;
	gTileClips[TILE_289].w = TILE_WIDTH;
	gTileClips[TILE_289].h = TILE_HEIGHT;

	gTileClips[TILE_290].x = 160;
	gTileClips[TILE_290].y = 608;
	gTileClips[TILE_290].w = TILE_WIDTH;
	gTileClips[TILE_290].h = TILE_HEIGHT;

	gTileClips[TILE_291].x = 192;
	gTileClips[TILE_291].y = 608;
	gTileClips[TILE_291].w = TILE_WIDTH;
	gTileClips[TILE_291].h = TILE_HEIGHT;

	gTileClips[TILE_292].x = 224;
	gTileClips[TILE_292].y = 608;
	gTileClips[TILE_292].w = TILE_WIDTH;
	gTileClips[TILE_292].h = TILE_HEIGHT;

	gTileClips[TILE_293].x = 256;
	gTileClips[TILE_293].y = 608;
	gTileClips[TILE_293].w = TILE_WIDTH;
	gTileClips[TILE_293].h = TILE_HEIGHT;

	gTileClips[TILE_294].x = 288;
	gTileClips[TILE_294].y = 608;
	gTileClips[TILE_294].w = TILE_WIDTH;
	gTileClips[TILE_294].h = TILE_HEIGHT;

	gTileClips[TILE_295].x = 320;
	gTileClips[TILE_295].y = 608;
	gTileClips[TILE_295].w = TILE_WIDTH;
	gTileClips[TILE_295].h = TILE_HEIGHT;

	gTileClips[TILE_296].x = 352;
	gTileClips[TILE_296].y = 608;
	gTileClips[TILE_296].w = TILE_WIDTH;
	gTileClips[TILE_296].h = TILE_HEIGHT;

	gTileClips[TILE_297].x = 384;
	gTileClips[TILE_297].y = 608;
	gTileClips[TILE_297].w = TILE_WIDTH;
	gTileClips[TILE_297].h = TILE_HEIGHT;

	gTileClips[TILE_298].x = 416;
	gTileClips[TILE_298].y = 608;
	gTileClips[TILE_298].w = TILE_WIDTH;
	gTileClips[TILE_298].h = TILE_HEIGHT;

	gTileClips[TILE_299].x = 448;
	gTileClips[TILE_299].y = 608;
	gTileClips[TILE_299].w = TILE_WIDTH;
	gTileClips[TILE_299].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_300].x = 0;
	gTileClips[TILE_300].y = 640;
	gTileClips[TILE_300].w = TILE_WIDTH;
	gTileClips[TILE_300].h = TILE_HEIGHT;

	gTileClips[TILE_301].x = 32;
	gTileClips[TILE_301].y = 640;
	gTileClips[TILE_301].w = TILE_WIDTH;
	gTileClips[TILE_301].h = TILE_HEIGHT;

	gTileClips[TILE_302].x = 64;
	gTileClips[TILE_302].y = 640;
	gTileClips[TILE_302].w = TILE_WIDTH;
	gTileClips[TILE_302].h = TILE_HEIGHT;

	gTileClips[TILE_303].x = 96;
	gTileClips[TILE_303].y = 640;
	gTileClips[TILE_303].w = TILE_WIDTH;
	gTileClips[TILE_303].h = TILE_HEIGHT;

	gTileClips[TILE_304].x = 128;
	gTileClips[TILE_304].y = 640;
	gTileClips[TILE_304].w = TILE_WIDTH;
	gTileClips[TILE_304].h = TILE_HEIGHT;

	gTileClips[TILE_305].x = 160;
	gTileClips[TILE_305].y = 640;
	gTileClips[TILE_305].w = TILE_WIDTH;
	gTileClips[TILE_305].h = TILE_HEIGHT;

	gTileClips[TILE_306].x = 192;
	gTileClips[TILE_306].y = 640;
	gTileClips[TILE_306].w = TILE_WIDTH;
	gTileClips[TILE_306].h = TILE_HEIGHT;

	gTileClips[TILE_307].x = 224;
	gTileClips[TILE_307].y = 640;
	gTileClips[TILE_307].w = TILE_WIDTH;
	gTileClips[TILE_307].h = TILE_HEIGHT;

	gTileClips[TILE_308].x = 256;
	gTileClips[TILE_308].y = 640;
	gTileClips[TILE_308].w = TILE_WIDTH;
	gTileClips[TILE_308].h = TILE_HEIGHT;

	gTileClips[TILE_309].x = 288;
	gTileClips[TILE_309].y = 640;
	gTileClips[TILE_309].w = TILE_WIDTH;
	gTileClips[TILE_309].h = TILE_HEIGHT;

	gTileClips[TILE_310].x = 320;
	gTileClips[TILE_310].y = 640;
	gTileClips[TILE_310].w = TILE_WIDTH;
	gTileClips[TILE_310].h = TILE_HEIGHT;

	gTileClips[TILE_311].x = 352;
	gTileClips[TILE_311].y = 640;
	gTileClips[TILE_311].w = TILE_WIDTH;
	gTileClips[TILE_311].h = TILE_HEIGHT;

	gTileClips[TILE_312].x = 384;
	gTileClips[TILE_312].y = 640;
	gTileClips[TILE_312].w = TILE_WIDTH;
	gTileClips[TILE_312].h = TILE_HEIGHT;

	gTileClips[TILE_313].x = 416;
	gTileClips[TILE_313].y = 640;
	gTileClips[TILE_313].w = TILE_WIDTH;
	gTileClips[TILE_313].h = TILE_HEIGHT;

	gTileClips[TILE_314].x = 448;
	gTileClips[TILE_314].y = 640;
	gTileClips[TILE_314].w = TILE_WIDTH;
	gTileClips[TILE_314].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_315].x = 0;
	gTileClips[TILE_315].y = 672;
	gTileClips[TILE_315].w = TILE_WIDTH;
	gTileClips[TILE_315].h = TILE_HEIGHT;

	gTileClips[TILE_316].x = 32;
	gTileClips[TILE_316].y = 672;
	gTileClips[TILE_316].w = TILE_WIDTH;
	gTileClips[TILE_316].h = TILE_HEIGHT;

	gTileClips[TILE_317].x = 64;
	gTileClips[TILE_317].y = 672;
	gTileClips[TILE_317].w = TILE_WIDTH;
	gTileClips[TILE_317].h = TILE_HEIGHT;

	gTileClips[TILE_318].x = 96;
	gTileClips[TILE_318].y = 672;
	gTileClips[TILE_318].w = TILE_WIDTH;
	gTileClips[TILE_318].h = TILE_HEIGHT;

	gTileClips[TILE_319].x = 128;
	gTileClips[TILE_319].y = 672;
	gTileClips[TILE_319].w = TILE_WIDTH;
	gTileClips[TILE_319].h = TILE_HEIGHT;

	gTileClips[TILE_320].x = 160;
	gTileClips[TILE_320].y = 672;
	gTileClips[TILE_320].w = TILE_WIDTH;
	gTileClips[TILE_320].h = TILE_HEIGHT;

	gTileClips[TILE_321].x = 192;
	gTileClips[TILE_321].y = 672;
	gTileClips[TILE_321].w = TILE_WIDTH;
	gTileClips[TILE_321].h = TILE_HEIGHT;

	gTileClips[TILE_322].x = 224;
	gTileClips[TILE_322].y = 672;
	gTileClips[TILE_322].w = TILE_WIDTH;
	gTileClips[TILE_322].h = TILE_HEIGHT;

	gTileClips[TILE_323].x = 256;
	gTileClips[TILE_323].y = 672;
	gTileClips[TILE_323].w = TILE_WIDTH;
	gTileClips[TILE_323].h = TILE_HEIGHT;

	gTileClips[TILE_324].x = 288;
	gTileClips[TILE_324].y = 672;
	gTileClips[TILE_324].w = TILE_WIDTH;
	gTileClips[TILE_324].h = TILE_HEIGHT;

	gTileClips[TILE_325].x = 320;
	gTileClips[TILE_325].y = 672;
	gTileClips[TILE_325].w = TILE_WIDTH;
	gTileClips[TILE_325].h = TILE_HEIGHT;

	gTileClips[TILE_326].x = 352;
	gTileClips[TILE_326].y = 672;
	gTileClips[TILE_326].w = TILE_WIDTH;
	gTileClips[TILE_326].h = TILE_HEIGHT;

	gTileClips[TILE_327].x = 384;
	gTileClips[TILE_327].y = 672;
	gTileClips[TILE_327].w = TILE_WIDTH;
	gTileClips[TILE_327].h = TILE_HEIGHT;

	gTileClips[TILE_328].x = 416;
	gTileClips[TILE_328].y = 672;
	gTileClips[TILE_328].w = TILE_WIDTH;
	gTileClips[TILE_328].h = TILE_HEIGHT;

	gTileClips[TILE_329].x = 448;
	gTileClips[TILE_329].y = 672;
	gTileClips[TILE_329].w = TILE_WIDTH;
	gTileClips[TILE_329].h = TILE_HEIGHT;
	//-----------------------------------------------
	gTileClips[TILE_330].x = 0;
	gTileClips[TILE_330].y = 704;
	gTileClips[TILE_330].w = TILE_WIDTH;
	gTileClips[TILE_330].h = TILE_HEIGHT;

	gTileClips[TILE_331].x = 32;
	gTileClips[TILE_331].y = 704;
	gTileClips[TILE_331].w = TILE_WIDTH;
	gTileClips[TILE_331].h = TILE_HEIGHT;

	gTileClips[TILE_332].x = 64;
	gTileClips[TILE_332].y = 704;
	gTileClips[TILE_332].w = TILE_WIDTH;
	gTileClips[TILE_332].h = TILE_HEIGHT;

	gTileClips[TILE_333].x = 96;
	gTileClips[TILE_333].y = 704;
	gTileClips[TILE_333].w = TILE_WIDTH;
	gTileClips[TILE_333].h = TILE_HEIGHT;

	gTileClips[TILE_334].x = 128;
	gTileClips[TILE_334].y = 704;
	gTileClips[TILE_334].w = TILE_WIDTH;
	gTileClips[TILE_334].h = TILE_HEIGHT;

	gTileClips[TILE_335].x = 160;
	gTileClips[TILE_335].y = 704;
	gTileClips[TILE_335].w = TILE_WIDTH;
	gTileClips[TILE_335].h = TILE_HEIGHT;

	gTileClips[TILE_336].x = 192;
	gTileClips[TILE_336].y = 704;
	gTileClips[TILE_336].w = TILE_WIDTH;
	gTileClips[TILE_336].h = TILE_HEIGHT;

	gTileClips[TILE_337].x = 224;
	gTileClips[TILE_337].y = 704;
	gTileClips[TILE_337].w = TILE_WIDTH;
	gTileClips[TILE_337].h = TILE_HEIGHT;

	gTileClips[TILE_338].x = 256;
	gTileClips[TILE_338].y = 704;
	gTileClips[TILE_338].w = TILE_WIDTH;
	gTileClips[TILE_338].h = TILE_HEIGHT;

	gTileClips[TILE_339].x = 288;
	gTileClips[TILE_339].y = 704;
	gTileClips[TILE_339].w = TILE_WIDTH;
	gTileClips[TILE_339].h = TILE_HEIGHT;

	gTileClips[TILE_340].x = 320;
	gTileClips[TILE_340].y = 704;
	gTileClips[TILE_340].w = TILE_WIDTH;
	gTileClips[TILE_340].h = TILE_HEIGHT;

	gTileClips[TILE_341].x = 352;
	gTileClips[TILE_341].y = 704;
	gTileClips[TILE_341].w = TILE_WIDTH;
	gTileClips[TILE_341].h = TILE_HEIGHT;

	gTileClips[TILE_342].x = 384;
	gTileClips[TILE_342].y = 704;
	gTileClips[TILE_342].w = TILE_WIDTH;
	gTileClips[TILE_342].h = TILE_HEIGHT;

	gTileClips[TILE_343].x = 416;
	gTileClips[TILE_343].y = 704;
	gTileClips[TILE_343].w = TILE_WIDTH;
	gTileClips[TILE_343].h = TILE_HEIGHT;

	gTileClips[TILE_344].x = 448;
	gTileClips[TILE_344].y = 704;
	gTileClips[TILE_344].w = TILE_WIDTH;
	gTileClips[TILE_344].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_345].x = 0;
	gTileClips[TILE_345].y = 736;
	gTileClips[TILE_345].w = TILE_WIDTH;
	gTileClips[TILE_345].h = TILE_HEIGHT;

	gTileClips[TILE_346].x = 32;
	gTileClips[TILE_346].y = 736;
	gTileClips[TILE_346].w = TILE_WIDTH;
	gTileClips[TILE_346].h = TILE_HEIGHT;

	gTileClips[TILE_347].x = 64;
	gTileClips[TILE_347].y = 736;
	gTileClips[TILE_347].w = TILE_WIDTH;
	gTileClips[TILE_347].h = TILE_HEIGHT;

	gTileClips[TILE_348].x = 96;
	gTileClips[TILE_348].y = 736;
	gTileClips[TILE_348].w = TILE_WIDTH;
	gTileClips[TILE_348].h = TILE_HEIGHT;

	gTileClips[TILE_349].x = 128;
	gTileClips[TILE_349].y = 736;
	gTileClips[TILE_349].w = TILE_WIDTH;
	gTileClips[TILE_349].h = TILE_HEIGHT;

	gTileClips[TILE_350].x = 160;
	gTileClips[TILE_350].y = 736;
	gTileClips[TILE_350].w = TILE_WIDTH;
	gTileClips[TILE_350].h = TILE_HEIGHT;

	gTileClips[TILE_351].x = 192;
	gTileClips[TILE_351].y = 736;
	gTileClips[TILE_351].w = TILE_WIDTH;
	gTileClips[TILE_351].h = TILE_HEIGHT;

	gTileClips[TILE_352].x = 224;
	gTileClips[TILE_352].y = 736;
	gTileClips[TILE_352].w = TILE_WIDTH;
	gTileClips[TILE_352].h = TILE_HEIGHT;

	gTileClips[TILE_353].x = 256;
	gTileClips[TILE_353].y = 736;
	gTileClips[TILE_353].w = TILE_WIDTH;
	gTileClips[TILE_353].h = TILE_HEIGHT;

	gTileClips[TILE_354].x = 288;
	gTileClips[TILE_354].y = 736;
	gTileClips[TILE_354].w = TILE_WIDTH;
	gTileClips[TILE_354].h = TILE_HEIGHT;

	gTileClips[TILE_355].x = 320;
	gTileClips[TILE_355].y = 736;
	gTileClips[TILE_355].w = TILE_WIDTH;
	gTileClips[TILE_355].h = TILE_HEIGHT;

	gTileClips[TILE_356].x = 352;
	gTileClips[TILE_356].y = 736;
	gTileClips[TILE_356].w = TILE_WIDTH;
	gTileClips[TILE_356].h = TILE_HEIGHT;

	gTileClips[TILE_357].x = 384;
	gTileClips[TILE_357].y = 736;
	gTileClips[TILE_357].w = TILE_WIDTH;
	gTileClips[TILE_357].h = TILE_HEIGHT;

	gTileClips[TILE_358].x = 416;
	gTileClips[TILE_358].y = 736;
	gTileClips[TILE_358].w = TILE_WIDTH;
	gTileClips[TILE_358].h = TILE_HEIGHT;

	gTileClips[TILE_359].x = 448;
	gTileClips[TILE_359].y = 736;
	gTileClips[TILE_359].w = TILE_WIDTH;
	gTileClips[TILE_359].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_360].x = 0;
	gTileClips[TILE_360].y = 768;
	gTileClips[TILE_360].w = TILE_WIDTH;
	gTileClips[TILE_360].h = TILE_HEIGHT;

	gTileClips[TILE_361].x = 32;
	gTileClips[TILE_361].y = 768;
	gTileClips[TILE_361].w = TILE_WIDTH;
	gTileClips[TILE_361].h = TILE_HEIGHT;

	gTileClips[TILE_362].x = 64;
	gTileClips[TILE_362].y = 768;
	gTileClips[TILE_362].w = TILE_WIDTH;
	gTileClips[TILE_362].h = TILE_HEIGHT;

	gTileClips[TILE_363].x = 96;
	gTileClips[TILE_363].y = 768;
	gTileClips[TILE_363].w = TILE_WIDTH;
	gTileClips[TILE_363].h = TILE_HEIGHT;

	gTileClips[TILE_364].x = 128;
	gTileClips[TILE_364].y = 768;
	gTileClips[TILE_364].w = TILE_WIDTH;
	gTileClips[TILE_364].h = TILE_HEIGHT;

	gTileClips[TILE_365].x = 160;
	gTileClips[TILE_365].y = 768;
	gTileClips[TILE_365].w = TILE_WIDTH;
	gTileClips[TILE_365].h = TILE_HEIGHT;

	gTileClips[TILE_366].x = 192;
	gTileClips[TILE_366].y = 768;
	gTileClips[TILE_366].w = TILE_WIDTH;
	gTileClips[TILE_366].h = TILE_HEIGHT;

	gTileClips[TILE_367].x = 224;
	gTileClips[TILE_367].y = 768;
	gTileClips[TILE_367].w = TILE_WIDTH;
	gTileClips[TILE_367].h = TILE_HEIGHT;

	gTileClips[TILE_368].x = 256;
	gTileClips[TILE_368].y = 768;
	gTileClips[TILE_368].w = TILE_WIDTH;
	gTileClips[TILE_368].h = TILE_HEIGHT;

	gTileClips[TILE_369].x = 288;
	gTileClips[TILE_369].y = 768;
	gTileClips[TILE_369].w = TILE_WIDTH;
	gTileClips[TILE_369].h = TILE_HEIGHT;

	gTileClips[TILE_370].x = 320;
	gTileClips[TILE_370].y = 768;
	gTileClips[TILE_370].w = TILE_WIDTH;
	gTileClips[TILE_370].h = TILE_HEIGHT;

	gTileClips[TILE_371].x = 352;
	gTileClips[TILE_371].y = 768;
	gTileClips[TILE_371].w = TILE_WIDTH;
	gTileClips[TILE_371].h = TILE_HEIGHT;

	gTileClips[TILE_372].x = 384;
	gTileClips[TILE_372].y = 768;
	gTileClips[TILE_372].w = TILE_WIDTH;
	gTileClips[TILE_372].h = TILE_HEIGHT;

	gTileClips[TILE_373].x = 416;
	gTileClips[TILE_373].y = 768;
	gTileClips[TILE_373].w = TILE_WIDTH;
	gTileClips[TILE_373].h = TILE_HEIGHT;

	gTileClips[TILE_374].x = 448;
	gTileClips[TILE_374].y = 768;
	gTileClips[TILE_374].w = TILE_WIDTH;
	gTileClips[TILE_374].h = TILE_HEIGHT;
	//------------------------------------------------
	gTileClips[TILE_375].x = 0;
	gTileClips[TILE_375].y = 800;
	gTileClips[TILE_375].w = TILE_WIDTH;
	gTileClips[TILE_375].h = TILE_HEIGHT;

	gTileClips[TILE_376].x = 32;
	gTileClips[TILE_376].y = 800;
	gTileClips[TILE_376].w = TILE_WIDTH;
	gTileClips[TILE_376].h = TILE_HEIGHT;

	gTileClips[TILE_377].x = 64;
	gTileClips[TILE_377].y = 800;
	gTileClips[TILE_377].w = TILE_WIDTH;
	gTileClips[TILE_377].h = TILE_HEIGHT;

	gTileClips[TILE_378].x = 96;
	gTileClips[TILE_378].y = 800;
	gTileClips[TILE_378].w = TILE_WIDTH;
	gTileClips[TILE_378].h = TILE_HEIGHT;

	gTileClips[TILE_379].x = 128;
	gTileClips[TILE_379].y = 800;
	gTileClips[TILE_379].w = TILE_WIDTH;
	gTileClips[TILE_379].h = TILE_HEIGHT;

	gTileClips[TILE_380].x = 160;
	gTileClips[TILE_380].y = 800;
	gTileClips[TILE_380].w = TILE_WIDTH;
	gTileClips[TILE_380].h = TILE_HEIGHT;

	gTileClips[TILE_381].x = 192;
	gTileClips[TILE_381].y = 800;
	gTileClips[TILE_381].w = TILE_WIDTH;
	gTileClips[TILE_381].h = TILE_HEIGHT;

	gTileClips[TILE_382].x = 224;
	gTileClips[TILE_382].y = 800;
	gTileClips[TILE_382].w = TILE_WIDTH;
	gTileClips[TILE_382].h = TILE_HEIGHT;

	gTileClips[TILE_383].x = 256;
	gTileClips[TILE_383].y = 800;
	gTileClips[TILE_383].w = TILE_WIDTH;
	gTileClips[TILE_383].h = TILE_HEIGHT;

	gTileClips[TILE_384].x = 288;
	gTileClips[TILE_384].y = 800;
	gTileClips[TILE_384].w = TILE_WIDTH;
	gTileClips[TILE_384].h = TILE_HEIGHT;

	gTileClips[TILE_385].x = 320;
	gTileClips[TILE_385].y = 800;
	gTileClips[TILE_385].w = TILE_WIDTH;
	gTileClips[TILE_385].h = TILE_HEIGHT;

	gTileClips[TILE_386].x = 352;
	gTileClips[TILE_386].y = 800;
	gTileClips[TILE_386].w = TILE_WIDTH;
	gTileClips[TILE_386].h = TILE_HEIGHT;

	gTileClips[TILE_387].x = 384;
	gTileClips[TILE_387].y = 800;
	gTileClips[TILE_387].w = TILE_WIDTH;
	gTileClips[TILE_387].h = TILE_HEIGHT;

	gTileClips[TILE_388].x = 416;
	gTileClips[TILE_388].y = 800;
	gTileClips[TILE_388].w = TILE_WIDTH;
	gTileClips[TILE_388].h = TILE_HEIGHT;

	gTileClips[TILE_389].x = 448;
	gTileClips[TILE_389].y = 800;
	gTileClips[TILE_389].w = TILE_WIDTH;
	gTileClips[TILE_389].h = TILE_HEIGHT;
	//------------------------------------------------
	}

#include "Juego.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Error.h"
#include "MenuInicio.h"
#include "GameOver.h"
#include "Pausa.h"
#include "Mundo.h"
#include "MundoVirtual.h"
#include "Combinaciones.h"
#include "PantallaControles.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
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
	winRect = {100, 100, SCREEN_WIDTH, SCREEN_HEIGHT };

	initSDL();//Inicializamos el renderizador

	nombreMapas = { "..\\bmps\\Habitaciones\\mapCompleto.csv" };
	nombreObjetos = { "..\\bmps\\Objetos\\Objetos1.csv" };

	initMedia();

	for (int i = 0; i < TAMAÑO_LLAVES; i++)
		llavesCogidas[i] = false;

	estadoEnum = MInicio;
	vectorEstados.push_back(new MenuInicio(this));//Primer estado de la pila
	
	//vectorEstados.push_back(new Mundo(this));//Primer estado de la pila

	combinaciones.reserve(1);
	combinaciones.emplace_back("3412");
	puertas[0] = false;
	numero = 20;
	
}
void Juego::reset(){
	srand(SDL_GetTicks());//Inicializamos los números aleatorios de manera que cada vez se van modificando
	exit = false;
	colorWin = { 0, 0, 0, 255 };
	borraEstado = false;

	for (int i = 0; i < TAMAÑO_LLAVES; i++)
		llavesCogidas[i] = false;

	combinaciones.reserve(1);
	combinaciones.emplace_back("3412");
	puertas[0] = false;
	numero = 20;
	indiceMapas = 1;
	nivel = 0;
}

bool Juego::getPuerta(int i){
	return puertas[i];
}

int Juego::getNumero()
{
	return numero;
}

//Paso de niveles
string Juego::SelectorDeNiveles() {
	return nombreMapas[0];

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
	bool combs = false;
	bool controles = false;

	switch (estado){
		//Menus
	case MInicio:
		aux = new MenuInicio(this);
		break;

	case MGameOver:
		aux = new GameOver(this);
		break;

	case MControles:
		aux = new PantallaControles(this);
		//controles = true;
		break;
	case MPausa:
		aux = new Pausa(this);
		pausa = true;
		break;

		//Mundos
	case MundoReal:
		aux = new Mundo(this, SelectorDeNiveles());
		break;
	case ECombinaciones:
		aux = new Combinaciones(this, combinaciones[0], 0);
		combs = true;
		break;

	default:
		aux = new MenuInicio(this);
		break;

	}

	/*if (controles)
		goToControles(aux);*/
	if (combs)
		goToCombinaciones(aux);
	else if (!pausa)
		changeState(aux);
	else
		goToPausa(aux);

	pausa = false;
	combs = false;
	borraEstado = false;

}

/*Arranca el bucle principal y controla si acaba la ejecución*/
void Juego::run()
{
	// La necesitaremos con un valor menor 
	Uint32 MSxUpdate = 5;
	Uint32 MSxInput = 5;

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
	// pRenderer = nullptr;

	SDL_DestroyWindow(pWin);
	// pWin = nullptr;

	SDL_Quit();
}

//SE PUEDE METER INIT Y FREE EN EL PADRE
void Juego::initMedia()
{
	//TEXTURAS

	vector <string>nombArchTex = { "..\\bmps\\AL.png","..\\bmps\\blood1.png", "..\\bmps\\hotelterror.png", "..\\bmps\\bala.png", "..\\bmps\\selft-time.png", "..\\bmps\\manticora.png", "..\\bmps\\botonjugar.png",
		"..\\bmps\\botonmenu.png", "..\\bmps\\botonsalir.png", "..\\bmps\\tilesdef.png", "..\\bmps\\llave.png",
		"..\\bmps\\informe1.png", "..\\bmps\\Informe2.png", "..\\bmps\\uno.png", "..\\bmps\\dos.png", "..\\bmps\\tres.png",
		"..\\bmps\\cuatro.png", "..\\bmps\\cinco.png", "..\\bmps\\seis.png", "..\\bmps\\siete.png", "..\\bmps\\ocho.png", "..\\bmps\\nueve.png",
		"..\\bmps\\cero.png", "..\\bmps\\teclado.png", "..\\bmps\\backButton.png", "..\\bmps\\pistola.png","..\\bmps\\Controles.png",  
		"..\\bmps\\Keypad.png" };

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
	string archAudioMp3 = { "..\\sounds\\mInicio.mp3" };
	musica[MusicaInicio] = new Musica();
	musica[MusicaInicio]->load(archAudioMp3);

}

void Juego::freeMedia()
{

	for (auto t : texturas2) {
		delete t;
	}

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

	//SDL_RenderCopy(renderer, textureInterface, NULL, &interface_rect);
	

	topEstado()->draw();

	//Intercambiar buffer y mostrar

	SDL_RenderPresent(pRenderer);
}

void Juego::changeState(EstadoJuego *estado){
	Sleep(1000); // ES IMPOSIBLE QUE DEJE DE ODIAROS
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

void Juego::goToCombinaciones(EstadoJuego* estado)
{
	vectorEstados.push_back(estado);//Añadimos el estado Pausa sin eliminar el estado actual 
}

void Juego::goToControles(EstadoJuego* estado)
{
	vectorEstados.push_back(estado);//Añadimos el estado Pausa sin eliminar el estado actual 
}
// tendrás que añadir atributos para la posición del ratón(que deben actualizarse en onClick)
/*std::pair<int, int> Juego::getMousePos() const {
	return std::make_pair(posMouseX, posMouseY);
}
*/
void Juego::getMousePos(int & mpx, int & mpy) const
{
	mpx = posMouseX;
	mpy = posMouseY;
}

// Comprueba si hay un evento en la cola de eventos y procesa el metodo correspondiente
void Juego::handle_event(){
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
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
	int k = 0;
	for (int i = 0; i <= 800; i += 32)
	{
		for (int j = 0; j <= 448; j += 32)
		{
			gTileClips[k].x = j;
			gTileClips[k].y = i;
			gTileClips[k].w = TILE_WIDTH;
			gTileClips[k].h = TILE_HEIGHT;

			k++;
		}

	}


}

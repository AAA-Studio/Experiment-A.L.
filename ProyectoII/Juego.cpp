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

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 

//Constructora
Juego::Juego() : JuegoSDL(" ", SCREEN_WIDTH, SCREEN_HEIGHT)
{
	exit = false;
	borraEstado = false;


	nombreMapas = { "..\\bmps\\Habitaciones\\MAPACOMPLETO.csv" };
	nombreObjetos = { "..\\bmps\\Objetos\\Objetos1.csv" };

	recortarTiles();


	for (int i = 0; i < TAMAÑO_LLAVES; i++)
		llavesCogidas[i] = false;

	estadoEnum = Estados_t::MInicio;
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

	SDL_ShowWindow(pWindow_);
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
	SDL_HideWindow(pWindow_);
	//GAME OVER

	// La necesitaremos con un valor menor 
	SDL_Delay(1000); //cin.get();
}

void Juego::render()
{
	//Limpiar el buffer
	SDL_RenderClear(pRenderer_);

	//SDL_RenderCopy(renderer, textureInterface, NULL, &interface_rect);
	
	topEstado()->draw();

	//Intercambiar buffer y mostrar

	SDL_RenderPresent(pRenderer_);
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
	for (int i = 0; i <= 1440; i += 32)
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

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
#include "CinematicaInicial.h"


#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 

//Constructora
Juego::Juego() : JuegoSDL(" ", SCREEN_WIDTH, SCREEN_HEIGHT)
{
	exit = false;
	borraEstado = false;


	nombreMapa = { "..\\bmps\\Habitaciones\\MAPACOMPLETO.csv" };
	nombreObjetos = { "..\\bmps\\Objetos\\Objetos1.csv" };

	recortarTiles();


	estadoEnum = Estados_t::MInicio;
	vectorEstados.push_back(new Mundo(this, nombreMapa));//Primer estado de la pila

	combinaciones.reserve(1);
	combinaciones.emplace_back("3412");
	
	puertasAbiertas[0] = false; //Se inicializa la 1a puerta



}

//Destructora
Juego::~Juego()
{
}

void Juego::gestionaEstados(Estados_t estado){
	EstadoJuego *aux; //Estado auxiliar que va a ser el estado a crear

	switch (estado){
		//Menus
	case MInicio:
		aux = new MenuInicio(this);
		changeState(aux);
		break;

	case EGameOver:
		aux = new GameOver(this);
		changeState(aux);
		break;
	case MPausa:
		aux = new Pausa(this);
		goToState(aux);
		break;


		//Mundos
	case MundoReal:
		aux = new Mundo(this, nombreMapa);//ARREGLAR METIENDO COSAS EN MUNDOVIRTUAL
		changeState(aux);
		break;
	case ECombinaciones:
		aux = new Combinaciones(this, combinaciones[0], 0);
		goToState(aux);
		break;
	case CinematicaI:
		aux = new CinematicaInicial(this, nombreMapa);
		changeState(aux);
		break;
	default:
		aux = new MenuInicio(this);
		changeState(aux);
		break;

	}

	borraEstado = false;
}

/*Arranca el bucle principal y controla si acaba la ejecución*/
void Juego::run()
{
	// La necesitaremos con un valor menor 
	Uint32 MSxUpdate = 5;

	SDL_ShowWindow(pWindow_);
	Uint32 lastUpdate = SDL_GetTicks(); //tiempo transcurrido desde el ultimo update()

	render();
	handle_event();
	while (!exit)
	{
		if (borraEstado)
			gestionaEstados(estadoEnum);

		if (SDL_GetTicks() - lastUpdate >= MSxUpdate)//Se pide la hora y se compara con la última 
		{
			topEstado()->update();
			handle_event();
			render();

			lastUpdate = SDL_GetTicks();
		}
	}
	//render();
	SDL_HideWindow(pWindow_);
	//GAME OVER

	// La necesitaremos con un valor menor 
	SDL_Delay(1000); //cin.get();
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
	//Sleep(1000); // ES IMPOSIBLE QUE DEJE DE ODIAROS; HAY QUE HACER UN ESTADO INTERMEDIO
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

//Metodo que se le llama al ir a Pausa, Controles y Combinaciones. No borra el estado anterior
void Juego::goToState(EstadoJuego *estado){
	vectorEstados.push_back(estado);
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

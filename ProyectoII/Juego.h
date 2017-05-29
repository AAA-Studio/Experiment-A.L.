#ifndef Juego_H
#define Juego_H
#include "checkML.h"

#include "JuegoSDL.h"
#include "EstadoJuego.h"
#include <vector>
#include <string>
#include <SDL.h>

// OS ODIARE PARA SIEMPRE
using namespace std;

//-----------------CONSTANTES----------------------

//Screen dimension constants pixels
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

//The dimensions of the level pixels
const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 15360;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 24000;
const int TOTAL_TILE_SPRITES = 1000;

//----------------------------------------------------

const int TAMAÑO_LLAVES = 2;

//------------------ENUMS--------------------------

enum Estados_t{ MInicio, MGameOver, MPausa, MundoReal, MundoOscuro, /*MPasoDeNivel*/ ECombinaciones, CinematicaI };

enum ListaBalas_t{ LBalasEnemigos, LBalasPersonaje };

//----------------------------------------------------


class Juego : public JuegoSDL
{
public:

	//Constructora, en caso de error muestra un mensaje y deja los atributos nulos y hace un thwrow que se captura en main
	Juego();

	//Destructora
	~Juego();
	
	// Arranca el bucle principal y, si se termina el juego. Tambien puede terminar si se cierra la ventana
	void run();

	//----------------ESTADOS---------------------

	//Devuelve el estado actual
	inline EstadoJuego * topEstado(){ return vectorEstados[vectorEstados.size() - 1]; };

	void changeState(EstadoJuego *estado);

	//Elimina el último estado
	void popState();

	void goToState(EstadoJuego * estado);

	//Sale del programa
	void inline setSalir() { exit = true; };

	//SETTER Y GETTER
	inline void setBorraEstado(bool borrar){ borraEstado = borrar; };
	inline bool getBorraEstado()const{ return borraEstado; };

	inline Estados_t getEstadoEnum(){ return estadoEnum; };
	inline void setEstadoEnum(Estados_t est){ estadoEnum = est; };

	void gestionaEstados(Estados_t estado);

	//------------ESTADOS------------------------


	//---------------GETTER Y SETTER----------------------
	//Raton
	//Detecta posición del raton
	void getMousePos(int & mpx, int & mpy) const;

	//Puerta
	void setPuerta(int i, bool estado){ puertasAbiertas[i] = estado; }
	inline bool getPuerta(int i)const{ return puertasAbiertas[i]; };

	//Objetos
	string getNombreObjetos(){ return nombreObjetos; }

	
	//Tile
	//Devuelve la colision del tile pasado como parametro
	inline SDL_Rect getRectTile(int numTile){ return gTileClips[numTile]; };

	//---------------GETTER Y SETTER----------------------

	

private:
	//-----------------------------ATRIBUTOS--------------------------
	//Estados
	bool borraEstado;
	vector <EstadoJuego*> vectorEstados;
	Estados_t estadoEnum;
	
	//Raton
	int posMouseX, posMouseY;

	//Nombre de archivos
	string nombreMapa;
	string nombreObjetos;

	//Combinaciones
	bool puertasAbiertas[1];
	vector <string> combinaciones;//Esto debe estar aquí porque combinaciones es un estado aparte, no pertenece a mundo
	
	//Salir del juego 
	bool exit;
	
	//Tile
	SDL_Rect gTileClips[TOTAL_TILE_SPRITES];



	//---------------------------ATRIBUTOS-----------------------------



	//----------------------------MÉTODOS--------------------------------

	//Interfaz
	void handle_event();	// REVISAR
	void render();

	//Tile
	void recortarTiles();

	//Añade un nuevo estado
	void pushState(EstadoJuego * nuevoEstado);

	//----------------------------MÉTODOS--------------------------------
};

#endif
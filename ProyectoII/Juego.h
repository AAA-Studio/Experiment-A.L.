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

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

//The dimensions of the level
const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 3840;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 6000;
const int TOTAL_TILE_SPRITES = 390;

//----------------------------------------------------

const int TAMAÑO_LLAVES = 2;


//----------------------------------------------------


//------------------ENUMS--------------------------

enum Estados_t{ MInicio, MGameOver, MPausa, MundoReal, MundoOscuro, ECombinaciones };

enum ListaBalas_t{ LBalasEnemigos, LBalasPersonaje };

//----------------------------------------------------


class Juego : public JuegoSDL
{
public:
	//Constructora, en caso de error muestra un mensaje y deja los atributos nulos y hace un thwrow que se captura en main
	Juego();
	void reset();
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

	// en duda
	void goToPausa(EstadoJuego * estado);
	void goToControles(EstadoJuego* estado);
	//crea el estado combinaciones
	void goToCombinaciones(EstadoJuego* estado);

	//Sale del programa
	void inline setSalir() { exit = true; };

	void setNivel(int i){
		nivel = i;
		indiceMapas += nivel;
	};
	//---------------GETTER----------------------
	//Saber el nivel del mapa en el que estamos
	int getNivel() { return nivel; };
	//Detecta posición del raton
	void getMousePos(int & mpx, int & mpy) const;

	//---------------GETTER----------------------

	inline bool getLLavesCogidas(int indice) const{ return llavesCogidas[indice]; };
	inline void setLlaveCogida(int indice){ llavesCogidas[indice] = !llavesCogidas[indice]; };


	//-----------TILE----------------
	// NUCA DEJARE DE ODIAROS
	SDL_Rect gTileClips[TOTAL_TILE_SPRITES]; //Array con los rectángulos de las colisiones

	inline SDL_Rect getRectTile(int numTile){ return gTileClips[numTile]; };//Devuelve la colision del tile pasado como parametro

	void recortarTiles();

	//---------------------------------------

	void escribir(string texto, int x, int y){
		getResources()->getTextura(TFuente)->renderFont(pRenderer_, x, y, texto,*getResources()->getFuente(FNormal));
	}
	// ES PUBLICO PORQUE OS ODIO
	bool borraEstado;
	Estados_t estadoEnum;

	void gestionaEstados(Estados_t estado);

	string SelectorDeNiveles();
	int indiceMapas = 1;
	//geter de los objetos desde fichero
	string dameObjetos(){ return nombreObjetos[0]; }

	//setter para cambiar el estado de una puerta cerrada a abierta
	void setPuerta(int i, bool estado){ puertas[i] = estado; }

	bool getPuerta(int i);

	//setter y getter de numero (EstadoCombinaciones)
	void setNumero(int i){ numero = i; }
	int getNumero();
	bool nuevoJuego = false;

private:



	//Atributos
	
	int nivel;
	bool exit;
	int posMouseX, posMouseY;
	vector <string> nombreMapas;
	vector <string> nombreObjetos;
	int numero; //numero para los teclados del estado combinaciones


	vector <EstadoJuego*> vectorEstados;
	bool llavesCogidas[TAMAÑO_LLAVES];

	void render();

	// REVISAR
	void handle_event();

	//Añade un nuevo estado
	void pushState(EstadoJuego * nuevoEstado);

	vector <string> combinaciones;
	bool puertas[1];
};

#endif
#ifndef Juego_H
#define Juego_H
#include "checkML.h"
#include "EstadoJuego.h"
#include "TexturasSDL.h"
#include "Fuente.h"
#include "Musica.h"
#include <vector>
#include <string>
#include <SDL.h>

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 768;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 960;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_0 = 0;
const int TILE_1 = 1;
const int TILE_2 = 2;
const int TILE_3 = 3;
const int TILE_4 = 4;
const int TILE_5 = 5;
const int TILE_6 = 6;
const int TILE_7 = 7;
const int TILE_8 = 8;
const int TILE_9 = 9;
const int TILE_10 = 10;
const int TILE_11 = 11;



using namespace std;

enum  Texturas_t{ TJugador, TPlay, TMenu, TExit, TLlave, TTilemap,/*TFondoMenu,*/ /*TInforme, TNewspaper,*/ TFuente, Texturas_t_SIZE };
enum  Efectos_t{ ENull, Efectos_t_SIZE };
enum  Musica_t{ Musica_t_SIZE};

//----------------------------------------------------

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

class Juego
{
public:
	//Constructora, en caso de error muestra un mensaje y deja los atributos nulos y hace un thwrow que se captura en main
	Juego();
	//Destructora
	~Juego();

	// Arranca el bucle principal y, si se termina el juego. Tambien puede terminar si se cierra la ventana
	void run();

	// detectara la posicion del jugador
	void getMousePos(int & mpx, int & mpy) const;

	//Devuelve el estado actual
	EstadoJuego * topEstado(){ return vectorEstados[vectorEstados.size() - 1]; };

	void changeState(EstadoJuego *estado);

	//Elimina el último estado
	void popState();

	// en duda
	void goToPausa(EstadoJuego * estado);

	//Sale del programa
	void setSalir(){ exit = true; };

	SDL_Renderer * getRender() const{ return pRenderer; };
	TexturasSDL * getTextura(Texturas_t et) const { return texturas[et]; }

	Efecto * getEfecto(Efectos_t et) const { return efectos[et]; }
	//no hay música todavía
	//Musica * getMusica(Musica_t et) const { return musica[et]; }

	Fuente getFuente() const { return fuente; }

	int getAncho(){ return winRect.w; }
	int getAlto(){ return winRect.h; }


	//-------------------------------------

	SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

	SDL_Rect getRectTile(int numTile){ return gTileClips[numTile]; };

	//Sets tiles from tile map
	void recortarTiles();

	//---------------------------------------



private:

	//Atributos
	bool exit;
	int posMouseX, posMouseY;

	SDL_Window *pWin;//Puntero de la ventana
	SDL_Renderer *pRenderer;//Puntero del renderizador

	SDL_Rect winRect;//Rectángulo de la ventana
	SDL_Color colorWin;//Color de la ventana

	vector <EstadoJuego*> vectorEstados;

	TexturasSDL*  texturas[Texturas_t_SIZE];

	//AMPLIACIONES
	Fuente fuente;
	TexturasSDL * textFuente;

	//No hay música todavía
	//Musica * musica[Musica_t_SIZE];
	Efecto * efectos[Efectos_t_SIZE];

	//Inicializa el renderizador, en caso de error muestra un mensaje y deja los atributos nulos
	void initSDL();
	//Libera los atributos inicados en initSDL
	void closeSDL();

	void initMedia();
	void freeMedia();

	void render();

	// REVISAR
	void handle_event();

	//Añade un nuevo estado
	void pushState(EstadoJuego * nuevoEstado);

	//---------------------


	//---------------------
};

#endif
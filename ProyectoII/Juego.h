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

using namespace std;

//-----------------CONSTANTES----------------------

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

//The dimensions of the level
const int LEVEL_WIDTH = 800;
const int LEVEL_HEIGHT = 640;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 500;
const int TOTAL_TILE_SPRITES = 390;

//----------------------------------------------------

const int TAMAÑO_LLAVES = 1;


//----------------------------------------------------


//------------------ENUMS--------------------------

enum  Texturas_t{ TJugador, TPlay, TMenu, TExit, TTilemap, TLlave, TInforme1, TInforme2,/*TFondoMenu,*/
	TUno, TDos, TTres, TCuatro, TCinco, TSeis, TSiete, TOcho, TNueve, TCero, TTeclado, TFuente, Texturas_t_SIZE };
enum  Efectos_t{ ENull, Efectos_t_SIZE };
enum  Musica_t{ Musica_t_SIZE};
enum Estados_t{MInicio, MGameOver, MPausa, MundoReal, MundoOscuro, ECombinaciones};

//----------------------------------------------------


class Juego
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

	// en duda
	void goToPausa(EstadoJuego * estado);

	//Sale del programa
	void setSalir(){ exit = true; };
	
	void setNivel(int i){ nivel =  i; };
	//---------------GETTER----------------------
	//Saber el nivel del mapa en el que estamos
	int getNivel() { return nivel; };
	//Detecta posición del raton
	void getMousePos(int & mpx, int & mpy) const;

	//---------------GETTER----------------------


	//Dibujado
	inline SDL_Renderer * getRender() const{ return pRenderer; };
	inline TexturasSDL * getTextura(Texturas_t et) const { return texturas[et]; }



	//Musica
	inline Efecto * getEfecto(Efectos_t et) const { return efectos[et]; }
	//Musica * getMusica(Musica_t et) const { return musica[et]; }

	//Fuente
	inline Fuente getFuente() const { return fuente; }

	//Ventana
	inline int getAncho()const{ return winRect.w; }
	inline int getAlto() const{ return winRect.h; }

	inline bool getLLavesCogidas(int indice) const{ return llavesCogidas[indice]; };
	inline void setLlaveCogida(int indice){ llavesCogidas[indice] = !llavesCogidas[indice]; };


	//-----------TILE----------------

	SDL_Rect gTileClips[TOTAL_TILE_SPRITES]; //Array con los rectángulos de las colisiones

	inline SDL_Rect getRectTile(int numTile){ return gTileClips[numTile]; };//Devuelve la colision del tile pasado como parametro

	void recortarTiles();

	//---------------------------------------

	bool borraEstado;
	Estados_t estadoEnum;

	void gestionaEstados(Estados_t estado);

	string SelectorDeNiveles();
	int indiceMapas=1;

	//numero tecleado para las combinaciones
	int numero;
	

private:

	//Atributos
	int nivel;
	bool exit;
	int posMouseX, posMouseY;
	vector <string> nombreMapas;
	

	SDL_Window *pWin;//Puntero de la ventana
	SDL_Renderer *pRenderer;//Puntero del renderizador

	SDL_Rect winRect;//Rectángulo de la ventana
	SDL_Color colorWin;//Color de la ventana

	vector <EstadoJuego*> vectorEstados;
	bool llavesCogidas[TAMAÑO_LLAVES];

	TexturasSDL*  texturas[Texturas_t_SIZE];

	//AMPLIACIONES
	Fuente fuente;
	TexturasSDL * textFuente;

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

};

#endif
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
const int TOTAL_TILE_SPRITES = 108;

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
const int TILE_12 = 12;
const int TILE_13 = 13;
const int TILE_14 = 14;
const int TILE_15 = 15;
const int TILE_16 = 16;
const int TILE_17 = 17;
const int TILE_18 = 18;
const int TILE_19 = 19;
const int TILE_20 = 20;
const int TILE_21 = 21;
const int TILE_22 = 22;
const int TILE_23 = 23;
const int TILE_24 = 24;
const int TILE_25 = 25;
const int TILE_26 = 26;
const int TILE_27 = 27;
const int TILE_28 = 28;
const int TILE_29 = 29;
const int TILE_30 = 30;
const int TILE_31 = 31;
const int TILE_32 = 32;
const int TILE_33 = 33;
const int TILE_34 = 34;
const int TILE_35 = 35;
const int TILE_36 = 36;
const int TILE_37 = 37;
const int TILE_38 = 38;
const int TILE_39 = 39;
const int TILE_40 = 40;
const int TILE_41 = 41;
const int TILE_42 = 42;
const int TILE_43 = 43;
const int TILE_44 = 44;
const int TILE_45 = 45;
const int TILE_46 = 46;
const int TILE_47 = 47;
const int TILE_48 = 48;
const int TILE_49 = 49;
const int TILE_50 = 50;
const int TILE_51 = 51;
const int TILE_52 = 52;
const int TILE_53 = 53;
const int TILE_54 = 54;
const int TILE_55 = 55;
const int TILE_56 = 56;
const int TILE_57 = 57;
const int TILE_58 = 58;
const int TILE_59 = 59;
const int TILE_60 = 60;
const int TILE_61 = 61;
const int TILE_62 = 62;
const int TILE_63 = 63;
const int TILE_64 = 64;
const int TILE_65 = 65;
const int TILE_66 = 66;
const int TILE_67 = 67;
const int TILE_68 = 68;
const int TILE_69 = 69;
const int TILE_70 = 70;
const int TILE_71 = 71;
const int TILE_72 = 72;
const int TILE_73 = 73;
const int TILE_74 = 74;
const int TILE_75 = 75;
const int TILE_76 = 76;
const int TILE_77 = 77;
const int TILE_78 = 78;
const int TILE_79 = 79;
const int TILE_80 = 80;
const int TILE_81 = 81;
const int TILE_82 = 82;
const int TILE_83 = 83;
const int TILE_84 = 84;
const int TILE_85 = 85;
const int TILE_86 = 86;
const int TILE_87 = 87;
const int TILE_88 = 88;
const int TILE_89 = 89;
const int TILE_90 = 90;
const int TILE_91 = 91;
const int TILE_92 = 92;
const int TILE_93 = 93;
const int TILE_94 = 94;
const int TILE_95 = 95;
const int TILE_96 = 96;
const int TILE_97 = 97;
const int TILE_98 = 98;
const int TILE_99 = 99;
const int TILE_100 = 100;
const int TILE_101 = 101;
const int TILE_102 = 102;
const int TILE_103 = 103;
const int TILE_104 = 104;
const int TILE_105 = 105;
const int TILE_106 = 106;
const int TILE_107 = 107;

//----------------------------------------------------


//------------------ENUMS--------------------------

enum  Texturas_t{ TJugador, TPlay, TMenu, TExit, TTilemap,/*TFondoMenu,*/ TFuente, Texturas_t_SIZE };
enum  Efectos_t{ ENull, Efectos_t_SIZE };
enum  Musica_t{ Musica_t_SIZE};
enum Estados_t{MInicio,MGameOver,MPausa,MundoReal,MundoOscuro};

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
	
	void setNivel(int i){ nivel = nivel + i; };
	//---------------GETTER----------------------
	//Saber el nivel del mapa en el que estamos
	int getNivel() { return nivel; };
	//Detecta posición del raton
	void getMousePos(int & mpx, int & mpy) const;

	//Dibujado
	inline SDL_Renderer * getRender() const{ return pRenderer; };
	inline TexturasSDL * getTextura(Texturas_t et) const { return texturas[et]; }

	//Musica
	inline Efecto * getEfecto(Efectos_t et) const { return efectos[et]; }
	//Musica * getMusica(Musica_t et) const { return musica[et]; }

	//Fuente
	inline Fuente getFuente() const { return fuente; }

	//Ventana
	inline int getAncho(){ return winRect.w; }
	inline int getAlto(){ return winRect.h; }

	//-----------TILE----------------

	SDL_Rect gTileClips[TOTAL_TILE_SPRITES]; //Array con los rectángulos de las colisiones

	inline SDL_Rect getRectTile(int numTile){ return gTileClips[numTile]; };//Devuelve la colision del tile pasado como parametro

	void recortarTiles();

	//---------------------------------------

	bool borraEstado;
	Estados_t estadoEnum;

	void gestionaEstados(Estados_t estado);

	string SelectorDeNiveles();
	int indiceMapas;
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
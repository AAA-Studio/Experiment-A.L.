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

enum  Texturas_t{ TJugador, TPlay, TMenu, TExit, /*TFondoMenu,*/ TFuente, Texturas_t_SIZE };
enum  Efectos_t{ ENull, Efectos_t_SIZE };
enum  Musica_t{ Musica_t_SIZE};

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

private:

	//Atributos
	bool exit;
	int posMouseX, posMouseY;

	SDL_Window *pWin;//Puntero de la ventana
	SDL_Renderer *pRenderer;//Puntero del renderizador

	SDL_Rect winRect;//Rectángulo de la ventana
	SDL_Color colorWin;//Color de la ventana

	vector <EstadoJuego*> vectorEstados;

	vector <string> nombArchTex;
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
	//Elimina el último estado
	void popState();

};

#endif
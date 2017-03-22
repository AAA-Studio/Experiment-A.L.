#ifndef Personaje_H
#define Personaje_H
#include "checkML.h"
#include "Entidad.h"
#include "PersonajeVirtual.h"
#include <list>
#include <SDL.h>
#include <iostream>




class Personaje : public PersonajeVirtual
{
public:
	Personaje(Juego*pJ, int x, int y, Texturas_t color, Efectos_t efecto);//Constructora
	~Personaje();//Destructora

	virtual void update();//Actualiza el estado y devuelve false si el globo queda desinflado
	virtual void onInput();
	virtual void draw()const; //Para dibujar las balas

	
	//----------------GETTER-------------------------------------------------------
	int getX(){ return rect.x; };
	int getY(){ return rect.y; };
	SDL_Rect getRectPsj(){ return rect; };
	int getAngulo(){ return angulo; };
	const SDL_Rect getRect(){ return rect; };


	//-------MÉTODOS QUE VIENEN DE LA CLASE INTERFAZ PERSONAJE VIRTUAL-------------
	void setCamera(SDL_Rect& camera);
	void restaVida();
	void destruyeBala(EntidadJuego * bala);
	//-----------------------------------------------------------------------------

	

	

private:
	//Atributos
	list <EntidadJuego*> balas;
	const float tiempoBala = 1000;
	Uint32 ultimaBala;
	int angulo;
	bool balaDestruida;
	int vida;



	Juego * pJuego;//Sustituye al puntero a la textura y al renderizador de la clase globo
	Texturas_t pTextura;
	Efectos_t sonido;

	SDL_Rect rect;//Rectángulo para cada textura

	//Métodos
	void disparo();
	void move(int x, int y);
};
#endif
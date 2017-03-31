#ifndef Personaje_H
#define Personaje_H
#include "checkML.h"
#include "Entidad.h"
#include "PersonajeVirtual.h"
#include <list>
#include <SDL.h>
#include <iostream>
#include "MundoVirtual.h"


enum Direccion{Derecha, Izquierda};//Posible enum para direcciones???

class Personaje : public PersonajeVirtual
{
public:
	Personaje(MundoVirtual * pM, int x, int y, Texturas_t color, Efectos_t efecto);//Constructora
	~Personaje();//Destructora

	virtual void update();//Actualiza el estado y devuelve false si el globo queda desinflado
	virtual void onInput();
	virtual void draw()const; //Para dibujar las balas

	
	//----------------GETTER-------------------------------------------------------
	int getX(){ return rect.x; };
	int getY(){ return rect.y; };
	SDL_Rect getRectPsj(){ return rect; };
	int getAngulo(){ return angulo; };
	inline SDL_Rect getRect()const { return rect; };
	Objetos_t getType() const  { return ONull; };
	inline int getVida()const { return vida; };



	//-------MÉTODOS QUE VIENEN DE LA CLASE INTERFAZ PERSONAJE VIRTUAL-------------
	void setCamera(SDL_Rect& camera);
	void restaVida();
	void destruyeBala(EntidadJuego * bala);
	//-----------------------------------------------------------------------------

	void empujeHaciaAtras();
	

	

private:
	//Atributos
	list <EntidadJuego*> balas;
	const float tiempoBala = 1000;
	Uint32 ultimaBala;
	int angulo;
	bool balaDestruida, llaveCogida, informeCogido;
	int vida;
	Direccion dir;



	Juego * pJuego;//Sustituye al puntero a la textura y al renderizador de la clase globo
	MundoVirtual * pMundo;
	Texturas_t pTextura;
	Texturas_t informe;
	Efectos_t sonido;
	Objetos_t obj;

	SDL_Rect rect;//Rectángulo para cada textura
	SDL_Rect rectInforme;
	SDL_Rect rectLlave;


	//Métodos
	void disparo();
	void coger();
	void soltar(Objetos_t obj);
	void move(int x, int y);
	void soltarInforme();


};
#endif
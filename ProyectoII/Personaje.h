#ifndef Personaje_H
#define Personaje_H
#include "checkML.h"
#include "Entidad.h"
#include "PersonajeVirtual.h"
#include <list>
#include <SDL.h>
#include <iostream>
#include "MundoVirtual.h"
#include "Armas.h"
struct Direccion{
	int x;
	int y;
};


class Personaje : public Entidad, public PersonajeVirtual
{
public:
	Personaje(MundoVirtual * pM, int x, int y, Texturas_t color, Efectos_t efecto);//Constructora
	~Personaje();//Destructora

	virtual void update();//Actualiza el estado y devuelve false si el globo queda desinflado
	virtual void onInput();

	virtual void draw(int x, int y)const; //Para dibujar las balas

	void cogeArma(Armas* arma);

	//----------------GETTER-------------------------------------------------------
	inline int getAngulo(){ return angulo; };
	inline float getVida()const { return vida; };
	inline SDL_Rect getHUD() { return rectHUD; };
	inline Uint8 getAlpha() { return (vida * 255) / maxVida; };
	inline int DamePosAntX(){ return posXAnt; };
	inline int DamePosAntY(){ return posYAnt; };
	inline int getX(){ return rect.x; };
	inline int getY(){ return rect.y; };
	inline Armas* getArma(){ return arma; }
	//-------MÉTODOS QUE VIENEN DE LA CLASE INTERFAZ PERSONAJE VIRTUAL-------------
	void restaVida();
	//-----------------------------------------------------------------------------

	void empujeHaciaAtras();

	//--------------PARA LA INTERFAZ DE CHOQUE CON EL MUNDO-------------------------
	void setPosChocando(int x, int y);
	void setDir(Direccion direc){ dir = direc; };
private:
	//Atributos
	const float tiempoBala = 1000;
	const float tiempoEmpuje = 500;
	Uint32 ultimoEmpuje;
	Uint32 ultimaBala;
	int angulo;
	bool balaDestruida, llaveCogida, informeCogido;
	float vida, maxVida;
	Direccion dir;
	Armas* arma;
	MundoVirtual * pMundo;
	Texturas_t informe;

	SDL_Rect rectInforme;
	SDL_Rect rectLlave;
	SDL_Rect rectHUD;
	int posXAnt, posYAnt;
	bool empuje;
	


	//Métodos
	void disparo();
	void coger();
	void soltar(Objetos_t obj);
	void move(int x, int y);
	void soltarInforme();

	//Animación
	SDL_Rect  rectAn;
	enum animar { derecha, izquierda, arriba, abajo };
	void animacion(animar currentFrame);
	void frames();
	void pasos();
	int cont;
	int retardo;
};
#endif
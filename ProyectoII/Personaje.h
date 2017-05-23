#ifndef Personaje_H
#define Personaje_H
#include "checkML.h"
#include "Entidad.h"
#include <list>
#include <SDL.h>
#include <iostream>
#include "MundoVirtual.h"
#include "Armas.h"

struct Direccion{
	int x;
	int y;
};

static const int MAXVIDA = 3;

class Personaje : public Entidad
{
public:
	Personaje(MundoVirtual * pM, int x, int y, JuegoSDL::Texturas_t color, JuegoSDL::Efectos_t efecto);//Constructora
	~Personaje();//Destructora

	virtual void update();
	virtual void onInput();
	virtual void draw(int x, int y)const; //Para dibujar las balas
	
	void empujeHaciaAtras();
	void cogeArma(Armas* arma);
	inline void empiezaPerderVida(){ pierdesVida = true; }
	void move(int x, int y);

	//----------------GETTER-------------------------------------------------------
	inline int getAngulo(){ return angulo; };
	inline SDL_Rect getHUD() { return rectHUD; };
	inline Uint8 getAlpha() { return (vida * 255) / MAXVIDA; };
	inline int DamePosAntX(){ return posXAnt; };
	inline int DamePosAntY(){ return posYAnt; };
	inline void setRect(SDL_Rect rectPsj){ rect = rectPsj; };
	inline SDL_Rect getRect()const{ return rect; };
	inline Armas* getArma(){ return arma; }
	inline bool getempiezaPerderVida(){ return pierdesVida; }
	inline void SetCinematica(bool c){ cinematica = c; };
	//-----------------------------------------------------------------------------

	//-------MÉTODOS QUE VIENEN DE LA CLASE INTERFAZ PERSONAJE VIRTUAL-------------
	void restaVida();
	inline float getVida()const { return vida; };
	//-----------------------------------------------------------------------------

	
	//--------------PARA LA INTERFAZ DE CHOQUE CON EL MUNDO-------------------------
	void setPosChocando(int x, int y);
	void setDir(Direccion direc){ dir = direc; };
	//------------------------------------------------------------------------------

private:
	//Atributos
	//Variablles de tiempo
	const float tiempoBala = 1000;
	const float tiempoEmpuje = 500;
	Uint32 ultimoEmpuje;
	Uint32 ultimaBala;

	Direccion dir;
	int posXAnt, posYAnt;
	int angulo;
	bool llaveCogida, informeCogido, pierdesVida;//MUUUUUUNDOOOOOO
	bool empuje, balaDestruida;
	float vida;

	Armas* arma;
	MundoVirtual * pMundo;
	JuegoSDL::Texturas_t informe;

	//Rectángulo ESTO DEBERIA ESTAR EN MUNDOOOOO
	SDL_Rect rectInforme;
	SDL_Rect rectLlave;
	SDL_Rect rectHUD;

	//Métodos
	void disparo();
	void coger();
	void soltar(Objetos_t obj);
	void soltarInforme();

	//Animación
	SDL_Rect  rectAn;
	enum animar { derecha, izquierda, arriba, abajo };
	void animacion(animar currentFrame);
	void frames();
	void pasos();
	int cont;
	int retardo;
	bool cinematica;

};
#endif
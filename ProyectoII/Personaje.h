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
	Personaje(MundoVirtual * pM, int x, int y, JuegoSDL::Texturas_t color, JuegoSDL::Efectos_t efecto);//Constructora
	~Personaje();//Destructora

	virtual void update();//Actualiza el estado y devuelve false si el globo queda desinflado
	virtual void onInput();

	virtual void draw(int x, int y)const; //Para dibujar las balas

	void cogeArma(Armas* arma);

	virtual void mover(int x, int y);

	inline void SetCinematica(bool c){ cinematica = c; };
	inline void empiezaPerderVida(){ pierdesVida = true; }
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
	inline bool getempiezaPerderVida(){ return pierdesVida; }
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
	JuegoSDL::Texturas_t informe;

	SDL_Rect rectInforme;
	SDL_Rect rectLlave;
	SDL_Rect rectHUD;
	int posXAnt, posYAnt;
	bool empuje;
	bool pierdesVida = false;


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
	bool cinematica;

};
#endif
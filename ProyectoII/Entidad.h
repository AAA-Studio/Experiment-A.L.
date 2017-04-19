#ifndef Entidad_H
#define Entidad_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"
#include "Mundo.h"
#include "MathCore.h"

//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Entidad : public EntidadJuego
{
protected:

	virtual void draw() const;
	virtual void onInput(const Controles_t & c) {};

	//El update no se modifica

	Juego * pJuego;//Sustituye al puntero a la textura y al renderizador de la clase globo
	Texturas_t pTextura;
	Efectos_t sonido;

	double posX, posY;
	int  ancho, alto;
	SDL_Rect rect;//Rectángulo para cada textura
	float m_maxVelocity;
	Vector2 m_velocity;

public:
	const SDL_Rect getRect(){ return rect; }
	Entidad * getEntity() { return this; }
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	void SetVelocity(float velocityX, float velocityY) { m_velocity.m_x = velocityX; m_velocity.m_y = velocityY; }
	Vector2 getPosition() const 
	{ 
		return Vector2(posX, posY); 
	}

	Entidad(Juego*pJ, double x, double y, Texturas_t textura, Efectos_t efecto);
	// Mal menor para terminar Enemigo
	Entidad();
	
	virtual ~Entidad();

};

#endif

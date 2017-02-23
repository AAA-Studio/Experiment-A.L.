#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"
#include <stack>
enum Controles_t { SuperNULL, JArriba, JAbajo, JIzquierda, JDerecha,JPIUM};



class EntidadJuego
{
	//Métodos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw() const = 0;

	virtual void update() = 0;

	virtual void onInput(const Controles_t &c) = 0;

};

#endif
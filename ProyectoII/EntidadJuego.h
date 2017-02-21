#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"

class EntidadJuego
{
	//Métodos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw() const = 0;

	virtual void update() = 0;

	virtual bool onClick() = 0;

};

#endif
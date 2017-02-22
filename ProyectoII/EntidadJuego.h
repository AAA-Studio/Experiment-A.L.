#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"

class EntidadJuego
{
	//M�todos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw() const = 0;

	virtual void update() = 0;

	virtual void onInput(const char& c) = 0;

};

#endif
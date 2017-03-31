#ifndef Pausa_H
#define Pausa_H
#include "Menu.h"
#include "Juego.h"

class Pausa : public Menu
{
public:
	Pausa(Juego * pJ);
	~Pausa();

	virtual void draw() const;

private:
	void initObjetos();

};

#endif

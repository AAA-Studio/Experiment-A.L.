
#ifndef MenuInicio_H
#define MenuInicio_H
#include "checkML.h"
#include "Estado.h"


class MenuInicio : public Estado
{
public:
	MenuInicio(Juego * pJ);
	~MenuInicio(){};
	virtual void draw()const;
	virtual void onInput(SDL_Event &e);

private:
	void initObjetos();

};

#endif

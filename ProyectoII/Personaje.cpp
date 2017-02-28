#include "Personaje.h"
#include <iostream>
//Constructora
Personaje::Personaje(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto)
{
	ultimaBala = SDL_GetTicks();
}

//Destructora
Personaje::~Personaje()
{
}


//Actualiza el estado y devuelve false si el globo queda desinflado
void Personaje::update()  
{	
	list<Bala*>::iterator it = balas.begin();


	while (!balas.empty() && it != balas.end())
	{
		(*it)->update();
		if (!balas.empty())
			it++;
	}
	
}

void Personaje::draw()const
{
	Entidad::draw();

	list<Bala*>::const_iterator it = balas.cbegin();
	while (!balas.empty() && it != balas.cend())
	{
		(*it)->draw();
		it++;
	}

}

void Personaje::onInput()
{
	double x = 0, y = 0;

	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);

	if (keyStatesActuales[SDL_SCANCODE_W] && keyStatesActuales[SDL_SCANCODE_A])
	{
		y += -0.1;
		x += -0.1;
		angulo = 135;
	}
	else if (keyStatesActuales[SDL_SCANCODE_W] && keyStatesActuales[SDL_SCANCODE_D])
	{
		y += -0.1;
		x += 0.1;
		angulo = 45;

	}
	else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_A])
	{
		y += 0.1;
		x += -0.1;
		angulo = 225;
	}
	else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_D])
	{
		y += 0.1;
		x += 0.1;
		angulo = 315;
	}
	else if (keyStatesActuales[SDL_SCANCODE_W])
	{
		y += -0.1;
		angulo = 90;
	}
	else if (keyStatesActuales[SDL_SCANCODE_A])
	{
		x += -0.1;
		angulo = 180;
	}
	else if (keyStatesActuales[SDL_SCANCODE_S])
	{
		y += 0.1;
		angulo = 270;
	}
	else if (keyStatesActuales[SDL_SCANCODE_D])
	{
		x += 0.1;
		angulo = 0;
	}

	if (keyStatesActuales[SDL_SCANCODE_E])
	{
		disparo();
	}
		
	move(x, y);
}

void Personaje::move(double x, double y)
{
	posX += x;
	posY += y;

	rect = { posX, posY, ancho, alto };

}

void Personaje::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)//Se pide la hora y se compara con la última 
	{
		balas.push_back(new Bala(pJuego, posX, posY, TPlay, ENull,angulo,this));

		ultimaBala = SDL_GetTicks();
	}
}

void Personaje::destruyeBala(Bala * bala)
{
	list<Bala*>::iterator it = balas.begin();
	while (it != balas.end() &&(*it) != bala)
	{
		it++;
	}

	balas.erase(it);
	delete (bala);
	bala = nullptr;

}







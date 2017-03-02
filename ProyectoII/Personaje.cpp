#include "Personaje.h"
#include <iostream>
//Constructora
Personaje::Personaje(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto)
{
	ultimaBala = SDL_GetTicks();
	balaDestruida = false;
}

//Destructora
Personaje::~Personaje()
{
}


//Actualiza el estado y devuelve false si el globo queda desinflado
void Personaje::update()  
{	
	list<Bala*>::iterator it = balas.begin();
	balaDestruida = false;

	while (!balaDestruida && !balas.empty() && it != balas.end())
	{
		(*it)->update();
		if (!balaDestruida)
		{
			it++;

		}

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
		y += -1;
		x += -1;
		angulo = 135;
	}
	else if (keyStatesActuales[SDL_SCANCODE_W] && keyStatesActuales[SDL_SCANCODE_D])
	{
		y += -1;
		x += 1;
		angulo = 45;

	}
	else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_A])
	{
		y += 1;
		x += -1;
		angulo = 225;
	}
	else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_D])
	{
		y += 1;
		x += 1;
		angulo = 315;
	}
	else if (keyStatesActuales[SDL_SCANCODE_W])
	{
		y += -1;
		angulo = 90;
	}
	else if (keyStatesActuales[SDL_SCANCODE_A])
	{
		x += -1;
		angulo = 180;
	}
	else if (keyStatesActuales[SDL_SCANCODE_S])
	{
		y += 1;
		angulo = 270;
	}
	else if (keyStatesActuales[SDL_SCANCODE_D])
	{
		x += 1;
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

	rect.x += x;

	//Si no colisiona con los tiles, me muevo
	if (static_cast<Mundo*> (pJuego->topEstado())->touchesWall(rect))
	{
		rect.x -= x;
	}

	rect.y += y;
	if (static_cast<Mundo*> (pJuego->topEstado())->touchesWall(rect))
	{
		rect.y -= y;
	}
}

void Personaje::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)//Se pide la hora y se compara con la última 
	{
		balas.push_back(new Bala(pJuego, rect.x, rect.y, TPlay, ENull,angulo,this));

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
	balaDestruida = true;
	balas.erase(it);
	delete (bala);
	bala = nullptr;

}

void Personaje::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (rect.x + rect.w / 2) - SCREEN_WIDTH / 2;
	camera.y = (rect.y + rect.h / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}







#include "Enemigo.h"
#include "Bala.h"


Enemigo::Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto, ONull)
{
	vida = 3;
	angulo = 180;
}


Enemigo::~Enemigo()
{
}

void Enemigo::update(){
	list<EntidadJuego*>::iterator it = balas.begin();
	balaDestruida = false;
	disparo();
	//Actualizo las balas
	while (!balaDestruida && !balas.empty() && it != balas.end())
	{
		(*it)->update();
		if (!balaDestruida)
			it++;	

	}

}

void Enemigo::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)//Se pide la hora y se compara con la última 
	{
		balas.push_back(new Bala(pJuego, rect.x, rect.y, TPlay, ENull, angulo, this));

		ultimaBala = SDL_GetTicks();
	}
}

void Enemigo::destruyeBala(EntidadJuego * bala)
{
	list<EntidadJuego*>::iterator it = balas.begin();
	while (it != balas.end() && (*it) != bala)
	{
		it++;
	}
	balaDestruida = true;
	balas.erase(it);
	delete (bala);
	bala = nullptr;

}


void Enemigo::draw()const
{

	Entidad::draw();

	list<EntidadJuego*>::const_iterator it = balas.cbegin();
	while (!balas.empty() && it != balas.cend())
	{
		(*it)->draw();
		it++;
	}


}



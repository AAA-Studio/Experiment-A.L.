#include "Enemigo4.h"
#include "Personaje.h"

Enemigo4::Enemigo4(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) : Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{
	pMundo = pM;
	posXAnt = x;
	posYAnt = y;
	chocando = false;
	xCol = yCol = 'n';
}

void Enemigo4::update(){

	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje
	posXAnt = rect.x;
	posYAnt = rect.y;
	ataque();

}

void Enemigo4::setPosChocando(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Enemigo4::ataque(){
	if (!chocando) //si no colisiona con nada persigue al jugador
		perseguir();
	else
	{
		if (xCol == 'x')
		{
		
		}
		else if (yCol == 'y')
		{

		}
	}

	if (pMundo->checkCollision(rectPJ, rect))
	{
		pMundo->getPersonaje()->restaVida(0);
	}
}

void Enemigo4::rodear()
{

}

void Enemigo4::perseguir(){
	

	if (rect.y > rectPJ.y) //movimiento en el eje y
		rect.y -= 1;
	else if (rect.y < rectPJ.y)
		rect.y += 1;

	if (rect.x > rectPJ.x) //movimiento en el eje x
		rect.x -= 1;
	else if (rect.x < rectPJ.x)
		rect.x += 1;
}


Enemigo4::~Enemigo4()
{
}

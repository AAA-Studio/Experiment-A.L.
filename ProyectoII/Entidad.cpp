#include "Entidad.h"


Entidad::Entidad(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto)
{
	ancho = alto = 100;
	posX = x;
	posY = y;
	pJuego = pJ;
	pTextura = textura;
	sonido = efecto;
}

Entidad::~Entidad()
{
}

void Entidad::draw()const
{
	pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect);//Dibujamos la textura
}

bool Entidad::onClick()
{
	int posMouseX, posMouseY;
	pJuego->getMousePos(posMouseX, posMouseY);

	//Comprobamos si la pos del ratón coincide con la pos de la textura del globo

	return dentro(posMouseX, posMouseY);
}

bool Entidad::dentro(int x, int y)const
{
	return (x >= posX && x <= (posX + ancho) && y >= posY && y <= (posY + alto));
}
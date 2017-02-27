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

SDL_Rect Entidad::dameRect(){
	SDL_Rect rectangulo;
	rectangulo.x = posX;
	rectangulo.y = posY;
	rectangulo.w = rect.w;
	rectangulo.h = rect.h;
	return rectangulo;
}

bool Entidad::onClick()
{
	int posMouseX, posMouseY;
	pJuego->getMousePos(posMouseX, posMouseY);

	//Comprobamos si la pos del rat�n coincide con la pos de la textura del globo

	return dentro(posMouseX, posMouseY);
}

bool Entidad::dentro(int x, int y)const
{
	return (x >= posX && x <= (posX + ancho) && y >= posY && y <= (posY + alto));
}
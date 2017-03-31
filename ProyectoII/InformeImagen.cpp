#include "InformeImagen.h"


InformeImagen::InformeImagen(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto)
{
	rect.w = rect.w * 5;
	rect.h = rect.h * 8;
}


InformeImagen::~InformeImagen()
{
}


#ifndef InformeImagen_H_
#define InformeImagen_H_

#include "checkML.h"
#include "Entidad.h"
class InformeImagen : public Entidad
{
public:
	InformeImagen(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	~InformeImagen();
	
};

#endif
#include "Informe.h"
#include "Personaje.h"
#include "Leer.h"

Informe::Informe(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto, Texturas_t textura2) : Entidad(pJ, x, y, textura, efecto)
{
	visible = true;
	text = textura2;
	
}

void Informe::coger(){
	pJuego->pushState(new Leer(pJuego, text));

}



Informe::~Informe()
{
}

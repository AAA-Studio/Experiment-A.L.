#include "Tecla.h"
#include "Combinaciones.h"

Tecla::Tecla(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb) : Boton(pJ, x, y, textura, efecto, cb)

{
	//cboton = cb;
	this->numero = numero;
	
}

void Tecla::onInput(){
	//Combinaciones* comb = new Combinaciones(pJuego); 

	int posMouseX, posMouseY;
	pJuego->getMousePos(posMouseX, posMouseY);

	//Comprobamos si la pos del ratón coincide con la pos de la textura del globo
	if (dentro(posMouseX, posMouseY)){
		cboton(pJuego);
	}
	
}



Tecla::~Tecla()
{
}

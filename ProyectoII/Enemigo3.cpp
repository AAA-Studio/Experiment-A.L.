#include "Enemigo3.h"
#include "Personaje.h"


Enemigo3::Enemigo3(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
: Enemigo(pM, x, y, w, h, textura, efecto)
{
	vida = 3;
	velocidad = 1;
	passedTime = 0;
	timeA = 60;
	embistiendo = false;

	enemigoDcha = 197;
	enemigoArr = 298;
	enemigoIzq = 94;
	sumaAnimX = 114;
	limiteX = 227;
}


Enemigo3::~Enemigo3()
{
}

void Enemigo3::update() {

	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje
	posXAnt = rect.x;
	posYAnt = rect.y;
	pegar(0.008);
	passedTime++;
	timeC = 20;
	if (embistiendo)
		embestir();
	else
		perseguir();

}

void Enemigo3::perseguir(){

	if (passedTime >= timeA)
	{
		passedTime = 0;
		velocidad = 5;
		embistiendo = true;
	}
	else
		Enemigo::perseguir();

}

void Enemigo3::embestir(){
	if (embistiendo)
	{
		if (passedTime < timeC)
		{
			//cout << "persigo";
			cargarContraPJ(); //le persigo de forma que cargo contra el 
		}
		else
		{
			passedTime = 0;
			velocidad = 1;
			embistiendo = false;
		}
	}

}

void Enemigo3::cargarContraPJ(){

	moveX = moveY = 0;

	if (rect.y > yPJ) //movimiento en el eje y
	{
		moveY -= velocidad;
	}
	else if (rect.y < yPJ)
		moveY += velocidad;

	if (rect.x > xPJ) //movimiento en el eje x
		moveX -= velocidad;
	else if (rect.x < xPJ)
		moveX += velocidad;

	mover(moveX, moveY);
}
#include "BossFinal.h"
#include "Personaje.h"

BossFinal::BossFinal(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) 
: Enemigo(pM, x, y, w, h, textura, efecto)
{
	vida = 10;
	velocidad = 1;
	timeR = 5000;
	passedTime = 0;
	comportamiento = EPersigue;
	estoyCerca = false;
	dist = rect;
	rangoDist = 30;
	embistiendo;

	rect = { x, y, 85, 76 };
	rectAn = { 0, 0, 85, 76 };	//medidas del rect de la animacion

	enemigoDcha = 193;
	enemigoArr = 288;
	enemigoIzq = 98;
	sumaAnimX = 105;
	limiteX = 183;
}
BossFinal::~BossFinal(){}


void BossFinal::update()
{
	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje
	posXAnt = rect.x;
	posYAnt = rect.y;

	switch (comportamiento)
	{
	case ERecarga:
		passedTime++;
		recargando();
		break;
	case EPersigue:
		perseguir();
		break;
	case EEmbiste:
		passedTime++;
		//cout << "tengo que embestir";
		embestir();
		break;
	case EDispara1:
		break;
	default:
		break;
	}
}

void BossFinal::recargando(){
	if (passedTime >= timeR)
	{
		comportamiento = EPersigue;
		passedTime = 0;
	}
}

void BossFinal::perseguir(){

	moveX = moveY = 0;
	dist = rect;

	if (rect.y > rectPJ.y) //movimiento en el eje y
	{
		moveY -= velocidad;
	}
	else if (rect.y < rectPJ.y)
	{
		moveY += velocidad;
		
	}

	if (rect.x > rectPJ.x) //movimiento en el eje x
		moveX -= velocidad;
	else if (rect.x < rectPJ.x)
		moveX += velocidad;

	mover(moveX, moveY);

	/*dist.x += rangoDist * moveX;
	dist.y += rangoDist * moveY;

	if (!pMundo->checkCollision(dist, rectPJ))
	{
		mover(moveX, moveY);
		cout << "me muevo como una princesa ";
	}
	else
	{
		cout << "vamos a joderte un rato ";
		xPJ = rectPJ.x;
		yPJ = rectPJ.y;
		velocidad = 3;
		embistiendo = true;
		comportamiento = EEmbiste;
	}*/
}

void BossFinal::embestir(){
	if (embistiendo)
	{
		cout << "hola guapa que llevas puesto";
		if (rect.x != xPJ && rect.y != yPJ) //si no he llegado a la ultima posicion registrada del jugador por enemigo
		{
			perseguir(); //le persigo de forma que cargo contra el 
		}
		else
		{
			velocidad = 1; //si he llegado a la posicion, cambio la velocidad y dejo de embestir
			embistiendo = false;
		}
	}
	else
		comportamiento = ERecarga; //cuando acabo de embestir me paro y recargo

}



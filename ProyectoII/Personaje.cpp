#include "Personaje.h"
#include <iostream>
#include "Mundo.h"
#include "Bala.h"

//Constructora
Personaje::Personaje(MundoVirtual * pM, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pM->getPJ(), x, y, 30,40, textura, efecto, ONull)
{
	pMundo = pM;
	rect = { x, y, 30, 40 };
	rectInforme = { pJuego->getAncho() / 4, pJuego->getAlto() / 20, 300, 600 };
	rectLlave = { 50, pJuego->getAlto() - 100, 100, 100 };
	rectHUD = { 0, 0, 800, 640 };
	ultimaBala = SDL_GetTicks();
	balaDestruida = false;
	llaveCogida = false;
	informeCogido = false;
	vida = maxVida = 3;
	angulo = 90;
	empuje = false;
	posXAnt = x;
	posYAnt = y;
}

//Destructora
Personaje::~Personaje()
{
}

void Personaje::update()
{
	if (!informeCogido){
		vida -= 0.001;
	}

}

void Personaje::draw()const
{
	Entidad::draw();

	if (informeCogido)
		pJuego->getTextura(informe)->draw(pJuego->getRender(), rectInforme);

	if (pJuego->getLLavesCogidas(0))
		pJuego->getTextura(TLlave)->draw(pJuego->getRender(), rectLlave);

}

void Personaje::onInput()
{
	int x = 0, y = 0;
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);

	if (!informeCogido && !empuje)
	{
		int x = 0, y = 0;

		if (keyStatesActuales[SDL_SCANCODE_W] && keyStatesActuales[SDL_SCANCODE_A])
		{
			y += -1;
			x += -1;
			angulo = 135;
		}
		else if (keyStatesActuales[SDL_SCANCODE_W] && keyStatesActuales[SDL_SCANCODE_D])
		{
			y += -1;
			x += 1;
			angulo = 45;

		}
		else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_A])
		{
			y += 1;
			x += -1;
			angulo = 225;
		}
		else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_D])
		{
			y += 1;
			x += 1;
			angulo = 315;
		}
		else if (keyStatesActuales[SDL_SCANCODE_W])
		{
			y += -1;
			angulo = 90;
		}
		else if (keyStatesActuales[SDL_SCANCODE_A])
		{
			x += -1;
			angulo = 180;
		}
		else if (keyStatesActuales[SDL_SCANCODE_S])
		{
			y += 1;
			angulo = 270;
		}
		else if (keyStatesActuales[SDL_SCANCODE_D])
		{
			x += 1;
			angulo = 0;
		}
		//Disparo
		if (keyStatesActuales[SDL_SCANCODE_E])
		{
			disparo();
		}
		//Caso en el que se coge un objeto
		if (keyStatesActuales[SDL_SCANCODE_C]){
			coger();
		}


		move(x, y);
	}

	else if (informeCogido)
	{
		if (keyStatesActuales[SDL_SCANCODE_Q])
			soltarInforme();

	}

	else if (empuje)
	{
		move(-dir.x, -dir.y);

		if (SDL_GetTicks() - ultimoEmpuje >= tiempoEmpuje)//Se pide la hora y se compara con la última 
			empuje = false;

	}
}
void Personaje::setPosChocando(int x, int y){
	rect.x = x;
	rect.y = y;
}
void Personaje::move(int x, int y)
{

	posXAnt = rect.x;
	posYAnt = rect.y;

	rect.x += x;
	rect.y += y;
}

void Personaje::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)//Se pide la hora y se compara con la última 
	{
		pMundo->insertaBala(LBalasPersonaje, new Bala(pMundo, rect.x, rect.y, TBala, ENull, angulo, LBalasPersonaje, rect.w / 15, rect.h / 15));

		ultimaBala = SDL_GetTicks();
	}
}



/*
void Personaje::setCamera(SDL_Rect& camera)
{
//Center the camera over the dot
camera.x = (rect.x + rect.w / 2) - SCREEN_WIDTH / 2;
camera.y = (rect.y + rect.h / 2) - SCREEN_HEIGHT / 2;

//Keep the camera in bounds
if (camera.x < 0)
{
camera.x = 0;
}
if (camera.y < 0)
{
camera.y = 0;
}
if (camera.x > LEVEL_WIDTH - camera.w)
{
camera.x = LEVEL_WIDTH - camera.w;
}
if (camera.y > LEVEL_HEIGHT - camera.h)
{
camera.y = LEVEL_HEIGHT - camera.h;
}
}
*/

//Necesito la dirección del personaje para poder empujarle hacia atrás
void Personaje::empujeHaciaAtras(){
	empuje = true;
	ultimoEmpuje = SDL_GetTicks();
}

void Personaje::restaVida(){
	vida -= 1;
}

void Personaje::coger(){
	EntidadJuego * objeto;
	objeto = pMundo->compruebaColisionObjetos();//Compruebo si estoy colisionando con el obj para poder cogerlo

	if (objeto != nullptr){
		switch (objeto->getType())
		{
		case OInforme1:
			informe = TInforme1;
			informeCogido = true;
			break;
		case OInforme2:
			informe = TInforme2;
			informeCogido = true;
			break;

		case OLlave:
			pMundo->destruyeLlave(objeto);
			break;
		case OTeclado:
			pJuego->borraEstado = true;
			pJuego->estadoEnum = ECombinaciones;
		}
	}




}

void Personaje::soltarInforme(){
	informeCogido = false;
	informe = Texturas_t_SIZE;




}






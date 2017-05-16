#include "Personaje.h"
#include <iostream>
#include "Mundo.h"
#include "Bala.h"

//Constructora
Personaje::Personaje(MundoVirtual * pM, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pM->getPJ(), x, y, 30,40, textura, efecto, ONull)
{
	pMundo = pM;
	rect = { x, y, 31, 50 };
	rectAn = { 0, 0, 31, 50 };
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
	retardo = 0;
	arma = nullptr;
	cinematica = true;
}

//Destructora
Personaje::~Personaje()
{
}

void Personaje::update()
{

	//Center the camera over the dot
	//pMundo->setCamera(rect.x - SCREEN_WIDTH / 2, rect.y - SCREEN_HEIGHT / 2); 
	if (pJuego->indiceMapas<6 && !informeCogido && !cinematica)
	vida -= 0.001;


}

void Personaje::mover(int x, int y){
	rect.x += x;
	rect.y += y;
}

void Personaje::draw(int x, int y)const
{

	//Entidad::draw(x,y);

	
	pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect,x,y, &rectAn);//Dibujamos la textura


	if (informeCogido)
		pJuego->getTextura(informe)->draw(pJuego->getRender(), rectInforme, rectInforme.x, rectInforme.y,nullptr);

	if (pJuego->getLLavesCogidas(0))
		pJuego->getTextura(TLlave)->draw(pJuego->getRender(), rectLlave, 50 , SCREEN_HEIGHT - 100,nullptr);

}

void Personaje::animacion(animar currentFrame){
	retardo++;
	if (retardo == 5){
		switch (currentFrame){
		case Personaje::derecha:
			rectAn.y = 192;
			retardo = 0;
			break;
		case Personaje::izquierda:
			rectAn.y = 64;
			retardo = 0;
			break;
		case Personaje::arriba:
			rectAn.y = 0;
			retardo = 0;
			break;
		case Personaje::abajo:
			rectAn.y = 128;
			retardo = 0;
			break;
		default:
			break;
		}
		frames();
		
	}
	
}

void Personaje::frames(){
	if (rectAn.x >= 240){
		rectAn.x = 0;
	}
	else{
		rectAn.x += 30;
	}
}
void Personaje::onInput()
{
	int x = 0, y = 0;
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);

	if (!informeCogido && !empuje)
	{
		int x = 0, y = 0;

		if (keyStatesActuales[SDL_SCANCODE_UP] && keyStatesActuales[SDL_SCANCODE_LEFT])
		{
			y += -1;
			x += -1;
			animacion(izquierda);
			angulo = 135;
		}
		else if (keyStatesActuales[SDL_SCANCODE_UP] && keyStatesActuales[SDL_SCANCODE_RIGHT])
		{
			y += -1;
			x += 1;
			animacion(derecha);
			angulo = 45;

		}
		else if (keyStatesActuales[SDL_SCANCODE_DOWN] && keyStatesActuales[SDL_SCANCODE_LEFT])
		{
			y += 1;
			x += -1;
			animacion(izquierda);
			angulo = 225;
		}
		else if (keyStatesActuales[SDL_SCANCODE_DOWN] && keyStatesActuales[SDL_SCANCODE_RIGHT])
		{
			y += 1;
			x += 1;
			animacion(derecha);
			angulo = 315;
		}
		else if (keyStatesActuales[SDL_SCANCODE_UP])
		{
			y += -1;
			animacion(arriba);
			angulo = 90;
		}
		else if (keyStatesActuales[SDL_SCANCODE_LEFT])
		{
			x += -1;
			animacion(izquierda);
			angulo = 180;
		}
		else if (keyStatesActuales[SDL_SCANCODE_DOWN])
		{
			y += 1;
			animacion(abajo);
			angulo = 270;
		}
		else if (keyStatesActuales[SDL_SCANCODE_RIGHT])
		{
			x += 1;
			animacion(derecha);
			angulo = 0;
		}
		//Disparo
		if (keyStatesActuales[SDL_SCANCODE_SPACE])
		{
			disparo();
		}
		//Caso en el que se coge un objeto
		if (keyStatesActuales[SDL_SCANCODE_E]){
			coger();
		}


		move(x, y);
	}

	else if (informeCogido)
	{
		if (keyStatesActuales[SDL_SCANCODE_E])
			soltarInforme();

	}

	else if (empuje)
	{
		move(-dir.x, -dir.y);

		if (SDL_GetTicks() - ultimoEmpuje >= tiempoEmpuje)//Se pide la hora y se compara con la �ltima 
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

	rect.x += 3*x;
	rect.y += 3*y;
}

void Personaje::disparo(){
if (arma != nullptr && arma->getBalas() > 0){
		if (SDL_GetTicks() - ultimaBala >= arma->getCadencia() )//Se pide la hora y se compara con la �ltima 
		{
			pMundo->insertaBala(LBalasPersonaje, new Bala(pMundo, rect.x, rect.y, TBala, ENull, angulo, LBalasPersonaje, rect.w / 15, rect.h / 15));
			arma->restaBalas();
			ultimaBala = SDL_GetTicks();
		}
	}
}







//Necesito la direcci�n del personaje para poder empujarle hacia atr�s
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
		if (objeto->getType() == OAk47)
			pMundo->ponmeArma();
		else{
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
				break;
			}
		}
	}
}
void Personaje::cogeArma(Armas* arma){
	delete this->arma;
	this->arma = nullptr;
	this->arma = arma;
}
void Personaje::soltarInforme(){
	informeCogido = false;
	informe = Texturas_t_SIZE;




}






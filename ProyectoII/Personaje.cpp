#include "Personaje.h"
#include <iostream>
#include "Mundo.h"
#include "Bala.h"


//Constructora
Personaje::Personaje(MundoVirtual * pM, int x, int y, Texturas_t textura, Efectos_t efecto)
{
	pMundo = pM;
	pJuego = pM->getPJ();
	pTextura = textura;
	sonido = efecto;
	rect = { x, y, 20, 20 };
	rectInforme = { pJuego->getAncho() / 2, pJuego->getAlto() / 2, 300, 600 };
	rectLlave = { 50, pJuego->getAlto() - 100, 100,100 };
	ultimaBala = SDL_GetTicks();
	balaDestruida = false;
	llaveCogida = false;
	informeCogido = false;
	vida = 3;
}

//Destructora
Personaje::~Personaje()
{
}


//Actualiza el estado y devuelve false si el globo queda desinflado
void Personaje::update()  
{	
	if (!informeCogido){
		list<EntidadJuego*>::iterator it = balas.begin();
		balaDestruida = false;

		while (!balaDestruida && !balas.empty() && it != balas.end())
		{
			(*it)->update();
			if (!balaDestruida)
			{
				it++;

			}

		}
	}
	
}

void Personaje::draw()const
{

	pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect);//Dibujamos la textura

	list<EntidadJuego*>::const_iterator it = balas.cbegin();
	while (!balas.empty() && it != balas.cend())
	{
		(*it)->draw();
		it++;
	}

	if (informeCogido)
		pJuego->getTextura(informe)->draw(pJuego->getRender(), rectInforme);

	if (pJuego->getLLavesCogidas(0))
		pJuego->getTextura(TLlave)->draw(pJuego->getRender(), rectLlave);


}

void Personaje::onInput()
{

	int x = 0, y = 0;
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);

	if (!informeCogido)
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

	else
	{
		if (keyStatesActuales[SDL_SCANCODE_Q]){
			soltarInforme();

		}



	}
}

void Personaje::move(int x, int y)
{

	rect.x += x;

	//--------------------------------
	if (x < 0) dir = Direccion::Derecha;
	else if (x > 0) dir = Direccion::Izquierda;
	//--------------------------------

	//Si no colisiona con los tiles, me muevo
	if (static_cast<Mundo*> (pJuego->topEstado())->getMapa()->touchesWall(rect))
	{
		rect.x -= x;
	}

	rect.y += y;
	if (static_cast<Mundo*> (pJuego->topEstado())->getMapa()->touchesWall(rect))
	{
		rect.y -= y;
	}
}

void Personaje::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)//Se pide la hora y se compara con la última 
	{
		balas.push_back(new Bala(pJuego, rect.x, rect.y, TPlay, ENull,angulo,this));

		ultimaBala = SDL_GetTicks();
	}
}

void Personaje::destruyeBala(EntidadJuego * bala)
{
	list<EntidadJuego*>::iterator it = balas.begin();
	while (it != balas.end() &&(*it) != bala)
	{
		it++;
	}
	balaDestruida = true;
	balas.erase(it);
	delete (bala);
	bala = nullptr;

}




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

//Necesito la dirección del personaje para poder empujarle hacia atrás
void Personaje::empujeHaciaAtras(){
	//Si la dirección es der, empujo hacia la izq


	//Si la dirección es izq, empujo hacia la der
	
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
		}
	}
	



}

void Personaje::soltarInforme(){
	informeCogido = false;
	informe = Texturas_t_SIZE;




}





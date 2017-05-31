#include "Enemigo4.h"
#include "Personaje.h"

Enemigo4::Enemigo4(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) : Enemigo(pM, x, y, w, h, textura, efecto)
{
	velocidad = 1;
	vida = 3;

	rect = { x, y, 87, 70 };
	rectAn = { 0, 0, 87, 70 };	//medidas del rect de la animacion

	enemigoDcha = 194;
	enemigoArr = 292;
	enemigoIzq = 94;
	sumaAnimX = 101;
	limiteX = 187;
}

void Enemigo4::update(){

	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje
	posXAnt = rect.x;
	posYAnt = rect.y;
	ataque();

}



void Enemigo4::ataque(){
	if (!chocando)//si no colisiona con nada persigue al jugador
	{
		atascadoX = atascadoY = false;
		perseguir();
	}
	else
	{
		rodear();
	}

	pegar(0.005);
}




Enemigo4::~Enemigo4()
{
}

//intento de algoritmo de la izquierda
/*int x = 0;
int y = 0;

if (izquierda)
{
rect.x -= 1;
izquierda = false;
}
else if (deFrente)
{
rect.y -= 1;
deFrente = false;
}
else if (derecha)
{
rect.x += 1;
}
else
{
rect.y += 1;
izquierda = deFrente = derecha = true;
}*/


/*void Enemigo4::rodear()
{
if (rect.y == rectPJ.y)
deFrente = true;
//else deFrente = false; //movimiento en el eje y

if (deFrente)
{
//cout << "here";
if (izquierda)
rect.y += 1;
else
rect.y -= 1;

if (pMundo->checkColMapa(rect))
izquierda = false;
}
else if (rect.y > rectPJ.y)
{
rect.y -= 1;
}
else if (rect.y < rectPJ.y)
{
rect.y += 1;
}

if (rect.x == rectPJ.x)
atascadoX = true;

if (atascadoX)
{
if (derecha)
rect.x += 1;
else
rect.x -= 1;

if (pMundo->checkColMapa(rect))
derecha = false;
}
if (rect.x > rectPJ.x) //movimiento en el eje x
rect.x -= 1;
else if (rect.x < rectPJ.x)
rect.x += 1;

/*SDL_Rect rectAr = { rect.x, rect.y + 1, rect.w, rect.h };
SDL_Rect rectAb = { rect.x, rect.y - 1, rect.w, rect.h };
SDL_Rect rectI = { rect.x, rect.y, rect.w, rect.h };
SDL_Rect rectD = { rect.x, rect.y, rect.w, rect.h };
if (pMundo->checkColMapa(rectAr))
if (pMundo->checkColMapa(rect))
chocando = false;
}*/
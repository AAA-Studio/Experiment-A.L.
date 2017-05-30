#include "Enemigo5.h"
#include "Personaje.h"


Enemigo5::Enemigo5(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
: Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull), pMundo(pM)
{
	chocando = false;
	estaEnEmbestida = estabaEmbistiendo = false;
	m_dirY = no;
	m_dirX = none;

	rectAntesEmbestida = { x, y, w, h };
}


Enemigo5::~Enemigo5()
{
}

void Enemigo5::update() {
	
	rectPJ = pMundo->getPersonaje()->getRect();
	
	if (EstaEnArea(200.0f)) {
		if (EstaEnArea(100.0f)) {
			if (estaEnEmbestida) {
				movimiento(rectPJ);
				if (EstaEnArea(5.0f)) {

					if (m_dirX == izq) rectPJ.x -= 5;
					else if (m_dirX == drcha)rectPJ.x += 5;
					if (m_dirY == up) rectPJ.y -= 5;
					else if (m_dirY == down) rectPJ.y += 5;
					estabaEmbistiendo != estaEnEmbestida;
				}
			}

			else {
				movimiento(rectAntesEmbestida);
			}
		}

		else {
			if (estabaEmbistiendo) {
				movimiento(rectPJ);
				estaEnEmbestida = true;
			}
		}
	}

	else {
		rectAntesEmbestida.x = rect.x; rectAntesEmbestida.y = rect.y;
	}

}

void Enemigo5::movimiento(SDL_Rect target) {
	if (rect.y > target.y) { //movimiento en el eje y
		m_dirY = up;
		rect.y--;
	}
	else if (rect.y < target.y) {
		m_dirY = down;
		rect.y++;
	}

	if (rect.x > target.x) { //movimiento en el eje x
		m_dirX = izq;
		rect.x--;
	}
	else if (rect.x < target.x) {
		m_dirX = drcha;
		rect.x++;
	}
}

bool Enemigo5::EstaEnArea(float minDistancia) {

	
	//Vectores auxiliares
	pair<float, float> targetPosition = make_pair(rectPJ.x, rectPJ.y);
	pair <float, float> position = make_pair(rect.x, rect.y);

	pair <float, float> toTarget = make_pair(targetPosition.first - position.first, targetPosition.second - position.second);

	float distance = sqrt((toTarget.first*toTarget.first) + (toTarget.second*toTarget.second));

	return (distance <= minDistancia);
}

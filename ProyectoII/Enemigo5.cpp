#include "Enemigo5.h"
#include "Personaje.h"


Enemigo5::Enemigo5(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
: Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull), pMundo(pM)
{
	chocando = false;
	estaEnEmbestida = estabaEmbistiendo = false;
	m_dirY = no;
	m_dirX = none;
}


Enemigo5::~Enemigo5()
{
}

void Enemigo5::update() {
	
	rectPJ = pMundo->getPersonaje()->getRect();

	if (EstaEnArea(200.0f)) {
		estaEnEmbestida != estabaEmbistiendo;
		if (EstaEnArea(100.0f)) {
			if (estaEnEmbestida) {
				embiste();
				if (EstaEnArea(5.0f)) {

					if (m_dirX == izq) rectPJ.x -= 5;
					else if (m_dirX == drcha)rectPJ.x += 5;
					if (m_dirY == up) rectPJ.y -= 5;
					else if (m_dirY == down) rectPJ.y += 5;
					estabaEmbistiendo != estaEnEmbestida;
				}
			}

			else {
				recargaEmbestida();
			}
		}

		else {
			if (estabaEmbistiendo) {
				embiste();
				estaEnEmbestida = true;
			}
		}
	}

}

void Enemigo5::embiste() {
	if (rect.y > rectPJ.y) { //movimiento en el eje y
		m_dirY = up;
		rect.y--;
	}
	else if (rect.y < rectPJ.y) {
		m_dirY = down;
		rect.y++;
	}

	if (rect.x > rectPJ.x) { //movimiento en el eje x
		m_dirX = izq;
		rect.x--;
	}
	else if (rect.x < rectPJ.x) {
		m_dirX = drcha;
		rect.x++;
	}
}

void Enemigo5::recargaEmbestida() {
	// O deshace el camino recorrido
	// o sigue hacia adelante hasta salir del area
}

bool Enemigo5::EstaEnArea(float minDistancia) {

	
	//Vectores auxiliares
	pair<float, float> targetPosition = make_pair(rectPJ.x, rectPJ.y);
	pair <float, float> position = make_pair(rect.x, rect.y);

	pair <float, float> toTarget = make_pair(targetPosition.first - position.first, targetPosition.second - position.second);

	float distance = sqrt((toTarget.first*toTarget.first) + (toTarget.second*toTarget.second));

	return (distance <= minDistancia);
}

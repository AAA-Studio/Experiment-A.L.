#include "Enemigo3.h"
#include "Personaje.h"


Enemigo3::Enemigo3(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
: Enemigo(pM, x, y, w, h, textura, efecto)
{
	estaEnEmbestida = estabaEmbistiendo = false;
	m_dirY = no;
	m_dirX = none;

	rectAntesEmbestida = { x, y, w, h };
	vida = 3;
	velocidad = 3;

}


Enemigo3::~Enemigo3()
{
}

void Enemigo3::update() {

	rectPJ = pMundo->getPersonaje()->getRect();
	estabaEmbistiendo = estaEnEmbestida = EstaEnArea(200.0f);
	if (estaEnEmbestida) velocidad = 3;
	else velocidad = 1;
	if (EstaEnArea(100.0f)) {
		if (EstaEnArea(50.0f)) {
			if (estaEnEmbestida) {
				movimiento(rectPJ);
				if (EstaEnArea(20.0f)) {

					if (m_dirX == izq) rectPJ.x -= 5;
					else if (m_dirX == drcha)rectPJ.x += 5;
					if (m_dirY == up) rectPJ.y -= 5;
					else if (m_dirY == down) rectPJ.y += 5;
					estabaEmbistiendo != estaEnEmbestida;
					velocidad = 1;
				}
			}

			else {
				velocidad = 2;
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

void Enemigo3::movimiento(SDL_Rect target) {
	if (rect.y > target.y) { //movimiento en el eje y
		m_dirY = up;
		rect.y -= velocidad;
	}
	else if (rect.y < target.y) {
		m_dirY = down;
		rect.y+= velocidad;
	}

	if (rect.x > target.x) { //movimiento en el eje x
		m_dirX = izq;
		rect.x -= velocidad;
	}
	else if (rect.x < target.x) {
		m_dirX = drcha;
		rect.x += velocidad;
	}
}

bool Enemigo3::EstaEnArea(float minDistancia) {

	//Vectores auxiliares
	pair<float, float> targetPosition = make_pair(rectPJ.x, rectPJ.y);
	pair <float, float> position = make_pair(rect.x, rect.y);

	pair <float, float> toTarget = make_pair(targetPosition.first - position.first, targetPosition.second - position.second);

	float distance = sqrt((toTarget.first*toTarget.first) + (toTarget.second*toTarget.second));

	return (distance <= minDistancia);
}
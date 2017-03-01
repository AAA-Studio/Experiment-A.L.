#include "Enemigo.h"


Enemigo::Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto)
{
}

void Enemigo::RandomizeGoal()
{
	int random_integerX = (int)(rand() % WORLD_SIZE*CELL_SIZE);
	int random_integerZ = (int)(rand() % WORLD_SIZE*CELL_SIZE);
	targetPos = Vector3((float)random_integerX, 0, (float)random_integerZ);
}

void Enemigo::Draw() {
	
	m_pathfinding->DrawDebug();

}

void Enemigo::Update(float deltaTime) {
	
	if (hasBeenHit) {
		regainControllerTimer += deltaTime / 10;
		// minuto 3:23 del video y tengo que crear la clase rectangulo
	}

}

Enemigo::~Enemigo()
{
}

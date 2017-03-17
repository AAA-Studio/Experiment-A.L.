#include "Enemigo.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <gl/GL.h> // Core Opengl functions


Enemigo::Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, vector <Vector2> waypoints) : Entidad(pJ, x, y, textura, efecto)
{
	m_currentState = IDLE;
	m_currentIndex = 0;
	m_idleTime = 3.0f;
	m_waypoints = waypoints;
}

void Enemigo::Initialize() {
	m_maxVelocity = 50.0f;
}

void Enemigo::Update() {
	switch (m_currentState) {
	case IDLE:
		{
			m_idleTime -= (float)SDL_GetTicks();
			if (m_idleTime <= 0.0f) {

				m_currentState = PATROL;
				m_idleTime = 3.0f;
				m_currentWayPoint = findNextWayPoints();
			}
		}
		break;

	case PATROL: {

			// Transform& transform = m_entidad->GetTransform();
			
			// Posicion del enemigo
			Vector2 position = m_entidad->getPosition();
			// Distancia enemigo - personaje
			Vector2 toTarget = m_currentWayPoint - Vector2 (position.GetX(), position.GetY());
			float distance = toTarget.Length;
			if (distance != 0.0f) {
				// Se acerca el enemigo al personaje
				toTarget.SetX(toTarget.GetX() / distance);
				toTarget.SetY(toTarget.GetY() / distance);
			}

			if (distance >= 4.0f) {
				m_currentState = IDLE;
				return;
			}

			Vector2 velocity = toTarget * 50.0f;
			// setVelocity(velocity.GetX(), velocity.GetY()):
			
		}
		break;
	}
}

Vector2 Enemigo::findNextWayPoints(){

	Vector2 waypoint = m_waypoints[m_currentIndex];
	m_currentIndex++;
	if (m_currentIndex >= (int)m_waypoints.size()) {
		m_currentIndex = 0;
	}

	return waypoint;
}



/*void Enemigo::RandomizeGoal()
{
	int random_integerX = (int)(rand() % WORLD_SIZE*CELL_SIZE);
	int random_integerZ = (int)(rand() % WORLD_SIZE*CELL_SIZE);
	targetPos = Vector2((float)random_integerX, 0, (float)random_integerZ);
}*/

/*void Enemigo::Draw() {

	//Hay que dibujar el enemigo
	
	m_pathfinding->DrawDebug();

}*/

/*void Enemigo::Update(float deltaTime) {

	if (hasBeenHit) {
		regainControllerTimer += deltaTime / 10;

		if (regainControllerTimer > 0.5f) {
			hasBeenHit = false;
			m_pathfinding->m_initializedStartGoal = false;
			m_pathfinding->m_foundGoal = false;
			m_pathfinding->ClearPathToGoal();
			isAtGoal = false;
			lockedGuard = false;
			Stop();
			m_pathState = RANDOMIZE;
			regainControllerTimer = 0;

		}
	}
	else {
		if (!lockedGuard)
			SetTargetTurretAngle(GetTTargetTurretAngle() + 7.0f);

		switch (m_pathState)
		{
			case RANDOMIZE: // Si no hay objetivo se mueve a una posicion aleatoria
			{
				isAtGoal = false;
				RandomizeGoal();
				m_pathState = SEARCHING;
				break;
			}
			case SEARCHING: // busca el mejor camino
			{
				// Si en el camino al objetivo hay una pared o se sale de los limites
				if (GetGameWorld()->GetCellState(GetGameWorld()->GetCellX(targetPos.m_x), GetGameWorld()->GetCellZ(targetPos.m_z)) ||
					targetPos.m_x < 0 || targetPos.m_x > WORLD_SIZE * CELL_SIZE || targetPos.m_z < 0 || targetPos.m_z > WORLD_SIZE * CELL_SIZE) {

					m_pathfinding->m_initializedStartGoal = false;
					m_pathfinding->m_foundGoal = false;
					m_pathfinding->ClearOpenList();
					m_pathfinding->ClearVisitedList();
					Stop();
					m_pathState = RANDOMIZE;
				}
				Vector2 newTargetPos;
				
				if (GetEnemyView(&newTargetPos, TYPE_PICKUP)) {
					targetPos = newTargetPos;
					m_pathfinding->ClearPathToGoal();
					Stop();
					m_pathfinding->m_initializedStartGoal = false;
					m_pathfinding->m_foundGoal = false;
					m_pathfinding->FindPath(pos, targetPos);
					isAtGoal = false;
					if (m_pathfinding->m_foundGoal) {
						m_pathState = FOUND_GOAL;
					}
					else {
						m_pathfinding->FindPath(pos, targetPos);
						isAtGoal = false;
						if (m_pathfinding->m_foundGoal) {
							m_pathState = FOUND_GOAL;
						}
					}
				}
			}
			break;

			case FOUND_GOAL: // una vez haya encontrado el camino a seguir, lo sigue
				Vector2 distanceToTarget = targetPos - pos;

				if (!isAtGoal) {
					Vector2 dist2Target = m_pathfinding->NextPathPos(this) - pos;
					float angle = rad2deg(atan2(dist2Target.m_x, dist2Target.m_z));
					SetDesiredRot(Vector2(0, angle, 0)); // Rota en la Y
					Accelerate(2.0f);
					Vector2 newTargetPos;

					if (GetEnemyView(&newTargetPos)) {
						targetPos = newTargetPos;
						m_pathfinding->ClearPathToGoal();
						Stop();
						m_pathfinding->m_initializedStartGoal = false;
						m_pathfinding->m_foundGoal = false;
						m_pathState = SEARCHING;
					}

					if (distanceToTarget.Length < radius *2.0f) {
						// llega
						m_pathfinding->ClearPathToGoal();
						isAtGoal = true;
						Stop();
						m_pathfinding->m_foundGoal = false;
						m_pathfinding->m_initializedStartGoal = false;
						lockedGuard = false;
						m_pathState = RANDOMIZE;
					}

				}

			break;

		}


	}
}*/

Enemigo::~Enemigo()
{


}

#include "PatrolState.h"
#include "EnemigoIA.h"
#include "IdleState.h"
#include "ChaseState.h"

PatrolState::PatrolState(vector<Vector2> waypoints)
{
	m_waypoints = waypoints;
}

PatrolState::~PatrolState()
{
	m_waypoints.clear();
}

void PatrolState::Enter(EnemigoIA * character) {

	character->SetMaxVelocity(75.0f);
}

void PatrolState::Execute(EnemigoIA * character) {

	Vector2 waypoint = m_waypoints[m_waypoints.size() - 1];

	// Posicion del enemigo     /*no hace falta?*/
	Vector2 position = character->getEntity()->getPosition();
	// Distancia enemigo - waypoint
	Vector2 toTarget = Vector2(waypoint.GetX(), waypoint.GetY())
		- Vector2(position.GetX(), position.GetY());
	float distance = toTarget.Length;

	// distancia con el jugador
	if (character->IsWithinRangeOfTarget(100.0f)) {
		character->GetStateMachine()->ChangeState(new ChaseState());
		return;
	}

	if (distance != 0) {
		// Se acerca el enemigo al waypoint
		toTarget.SetX(toTarget.GetX() / distance);
		toTarget.SetY(toTarget.GetY() / distance);
	}

	if (distance  <= 20.0f)) {
		// Voy borrando el ultimo hasta que el vector este vacio.
		m_waypoints.erase(m_waypoints.begin() + (m_waypoints.size() - 1));

		if (m_waypoints.empty()) {
			character->GetStateMachine()->ChangeState(new IdleState());
			return;
		}
	}

	Vector2 velocity = toTarget * 50.0f;

	position.SetX(position.GetX() + velocity.GetX() * (float)SDL_GetTicks());
	position.SetY(position.GetY() + velocity.GetY() * (float)SDL_GetTicks());

	/*Vector2 velocity = toTarget * 20.0f
	character->addVelocity(velocity.GetX(), velocity.GetY());
	*/
}

void PatrolState::Exit(EnemigoIA * character) { }
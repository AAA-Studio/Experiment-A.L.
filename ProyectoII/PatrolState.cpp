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

void PatrolState::Enter(EnemigoIA * character) {}

void PatrolState::Execute(EnemigoIA * character) {

	Vector2 waypoint = m_waypoints[m_waypoints.size() - 1];

	// Posicion del enemigo
	Vector2 position = character->getEntity()->getPosition();
	// Distancia enemigo - personaje
	Vector2 toTarget = Vector2(waypoint.GetX(), waypoint.GetY())
		- Vector2(position.GetX(), position.GetY());
	float distance = toTarget.Length;
	if (distance != 0.0f) {
		// Se acerca el enemigo al personaje
		toTarget.SetX(toTarget.GetX() / distance);
		toTarget.SetY(toTarget.GetY() / distance);
	}

	if (distance <= 2.0f) {

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

	if (character->IsWithinRangeOfTarget(100.0f)) {
		position.SetX(position.GetX());
		position.SetY(position.GetY());
		character->GetStateMachine()->ChangeState(new ChaseState());
	}
}

void PatrolState::Exit(EnemigoIA * character) { }
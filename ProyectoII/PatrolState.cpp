#include "PatrolState.h"
#include "EnemigoIA.h"
#include "IdleState.h"
#include "ChaseState.h"
#include "Mundo.h"

#include <iostream>

PatrolState::PatrolState(std::vector<pair <float, float>> waypoints) : State<EnemigoIA>()
{
	m_stateName = "PatrolState";
	m_waypoints = waypoints;
}

PatrolState::~PatrolState()
{
	m_waypoints.clear();
}

void PatrolState::Enter(EnemigoIA * character) {

	character->SetMaxVelocity(0.5f);
}

void PatrolState::Execute(EnemigoIA * character) {

	pair <float, float> waypoint = m_waypoints[m_waypoints.size() - 1];
	

	// Posicion del enemigo
	pair <float, float> position(character->getRect().x, character->getRect().y);
	// Distancia enemigo - waypoint
	pair <float, float> toTarget = make_pair(waypoint.first - position.first, waypoint.second - position.second);
	float distance = sqrt((toTarget.first*toTarget.first) + (toTarget.second*toTarget.second));

	if (distance != 0) {
		// Se acerca el enemigo al waypoint
		toTarget.first = toTarget.first / distance;
		toTarget.second = toTarget.second / distance;
	}

	if (distance <= 20.0f) {
		// Voy borrando el ultimo hasta que el vector este vacio.
		m_waypoints.erase(m_waypoints.begin() + (m_waypoints.size() - 1));

		if (m_waypoints.empty()) {
			character->GetStateMachine()->ChangeState(new IdleState());
		}
	}

	if (position.first < 10.0f || position.second < 10.0f)
		std::cout << "Se va a (0,0)" << endl;

	pair <float, float> velocity = make_pair(toTarget.first * 1.5f, toTarget.second * 1.5f);

	position.first = position.first + velocity.first;
	position.second = position.second + velocity.second;

	SDL_Rect posRect = { position.first, position.second, character->getRect().w, character->getRect().h };
	character->setRect(posRect);
}

void PatrolState::Exit(EnemigoIA * character) { }
#include "EnemigoIA.h"
#include "IdleState.h"
#include "SearchCell.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <gl/GL.h> // Core Opengl functions

EnemigoIA::EnemigoIA(/*Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto,*/Entidad * pEntidad)
{
	// pEntidad se inicializa antes de entrar en la constructora
	pEntidad = NULL;
	m_stateMachine = NULL;
}


EnemigoIA::~EnemigoIA()
{
	if (m_stateMachine) {
	
		delete m_stateMachine;
		m_stateMachine = NULL;
	}
}

void EnemigoIA::Initialize() {
	
	m_maxVelocity = 50.0f;
	m_stateMachine = new StateMachine<EnemigoIA>(this);
	m_stateMachine->ChangeState(new IdleState());
}

void EnemigoIA::Update() {

	Enemigo::Update();
	m_stateMachine->Update();
}

void EnemigoIA::ChaseTarget() {
	m_maxVelocity = 150.0f;
	SDL_Rect targetTransform = m_target->getRect();

	Vector2 targetPosition;
	targetPosition.m_x = targetTransform.x;
	targetPosition.m_y = targetTransform.y;

	Vector2 position;
	position.m_x = m_transform->x;
	position.m_y = m_transform->y;

	Vector2 toTarget = targetPosition - position;
	float distance = toTarget.Length;
	if (!character->IsWithinRangeOfTarget(0)) {
		// toTarget.SetX(toTarget.GetX() / distance);
		// toTarget.SetY(toTarget.GetY() / distance);
		toTarget /= distance;
	}

	Vector2 velocity = toTarget * 35.0f;

	position.SetX(position.GetX() + velocity.GetX() * (float)SDL_GetTicks());
	position.SetY(position.GetY() + velocity.GetY() * (float)SDL_GetTicks());
}

StateMachine<EnemigoIA>*EnemigoIA::GetStateMachine() {
	return m_stateMachine;
}

Vector2 EnemigoIA::findNextWayPoints(){

	Vector2 waypoint = m_waypoints[m_currentIndex];
	m_currentIndex = (int)(rand() % m_waypoints.size() - 1);

	/*m_currentIndex++;
	if (m_currentIndex >= (int)m_waypoints.size()) {
	m_currentIndex = 0;
	}*/

	return waypoint;
}

bool EnemigoIA::IsWithinRangeOfTarget(float minDistance) {

	SDL_Rect targetTransform = m_target->getRect();
	Vector2 targetPosition;
	targetPosition.m_x = targetTransform.x;
	targetPosition.m_y = targetTransform.y;

	Vector2 position;
	position.m_x = m_transform->x;
	position.m_y = m_transform->y;

	Vector2 toTarget = targetPosition - position;
	float distance = toTarget.Length;

	return (distance <= minDistance);
}
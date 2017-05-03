#include "EnemigoIA.h"
#include "IdleState.h"
#include "SearchCell.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <gl/GL.h> // Core Opengl functions

EnemigoIA::EnemigoIA(MundoVirtual*pM, int x, int y, int w, int h, Texturas_t textura, Efectos_t efecto) : Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{
	vida = 3;
	pMundo = pM;
	m_currentIndex = 0;
	Initialize();
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

void EnemigoIA::update() {

	Entidad::update();
	m_stateMachine->Update();
}

void EnemigoIA::ChaseTarget() {
	m_maxVelocity = 150.0f;
	SDL_Rect targetTransform = m_target->getRect();

	//Vectores auxiliares
	Vector2 targetPosition;
	targetPosition.SetX(targetTransform.x);
	targetPosition.SetY(targetTransform.y);

	Vector2 position;
	position.SetX(rect.x);
	position.SetY(rect.y);

	Vector2 toTarget = targetPosition - position;
	float distance = toTarget.GetLength();

	if (!IsWithinRangeOfTarget(0)) 
		toTarget /= distance;

	Vector2 velocity = toTarget * 35.0f;

	position.SetX(position.GetX() + velocity.GetX() * (float)SDL_GetTicks());
	position.SetY(position.GetY() + velocity.GetY() * (float)SDL_GetTicks());
}

StateMachine<EnemigoIA>*EnemigoIA::GetStateMachine() {
	return m_stateMachine;
}

Vector2 EnemigoIA::findNextWayPoints(){

	if (m_waypoints.size() != 0)
	{
		Vector2 waypoint = m_waypoints[m_currentIndex];
		m_currentIndex = (int)(rand() % m_waypoints.size() - 1);

		return waypoint;
	}
	else
		return;
}

bool EnemigoIA::IsWithinRangeOfTarget(float minDistance) {

	SDL_Rect targetTransform = m_target->getRect();

	//Vectores auxiliares
	Vector2 targetPosition;
	targetPosition.SetX(targetTransform.x);
	targetPosition.SetY(targetTransform.y);

	Vector2 position;
	position.SetX(rect.x);
	position.SetY(rect.y);

	Vector2 toTarget = targetPosition - position;
	float distance = toTarget.GetLength();

	return (distance <= minDistance);
}
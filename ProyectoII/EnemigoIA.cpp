#include "EnemigoIA.h"
#include "SearchCell.h"
#include "IdleState.h"
#include "EnemigoIAGlobalState.h"

#include <math.h>
#include <windows.h>
#include <utility>

EnemigoIA::EnemigoIA(MundoVirtual*pM, Entidad* target, int x, int y, int w, int h, Texturas_t textura, Efectos_t efecto/*, vector < pair<float, float>> waypoints*/)
: Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{
	vida = 3;
	pMundo = pM;
	m_target = target;
	m_currentIndex = 0;
	Initialize();
	initWaypoints();
}


EnemigoIA::~EnemigoIA()
{
	if (m_stateMachine) {
	
		delete m_stateMachine;
		m_stateMachine = NULL;
	}
}

void EnemigoIA::Initialize() {
	
	//m_target será el personaje
	m_maxVelocity = 0.0f;
	m_stateMachine = new StateMachine<EnemigoIA>(this);
	m_stateMachine->ChangeState(new IdleState());
	m_stateMachine->SetGlobalState(new EnemigoIAGlobalState());
}

void EnemigoIA::initWaypoints(){

	// Para comprobar que funciona el codigo
	
	m_waypoints.push_back(make_pair(rand() % LEVEL_WIDTH, rand() % LEVEL_HEIGHT));
	m_waypoints.push_back(make_pair(rand() % LEVEL_WIDTH, rand() % LEVEL_HEIGHT));
	m_waypoints.push_back(make_pair(rand() % LEVEL_WIDTH, rand() % LEVEL_HEIGHT));
	
}

void EnemigoIA::update() {

	Entidad::update();
	m_stateMachine->Update();
}

void EnemigoIA::ChaseTarget() {
	m_maxVelocity = 0.0001f;
	SDL_Rect targetTransform = m_target->getRect();

	//Vectores auxiliares
	pair<float, float> targetPosition = make_pair(targetTransform.x, targetTransform.y);
	pair <float,float> position = make_pair(rect.x, rect.y);

	pair <float, float> toTarget = make_pair(targetPosition.first - position.first, targetPosition.second - position.second);
	float distance = sqrt((toTarget.first*toTarget.first) + (toTarget.second*toTarget.second));

	if (!IsWithinRangeOfTarget(0)) {
		
		toTarget.first /= distance;
		toTarget.second /= distance;
	}

	pair <float, float> velocity = make_pair(toTarget.first * m_maxVelocity, toTarget.second * m_maxVelocity);

	position.first = position.first + velocity.first * (float)SDL_GetTicks();
	position.second = position.second + velocity.second * (float)SDL_GetTicks();

	SDL_Rect posRect = { position.first, position.second, rect.w, rect.h };
	setRect(posRect);

}

StateMachine<EnemigoIA>*EnemigoIA::GetStateMachine() {
	return m_stateMachine;
}

const pair <float, float> &EnemigoIA::findNextWayPoints(){

	if (m_waypoints.size() != 0)
	{
		const pair <float, float>& waypoint = m_waypoints[m_currentIndex];
		m_currentIndex = (int)(rand() % m_waypoints.size() - 1);

		return waypoint;
	}
	// Para debug
	else{

		initWaypoints();
		const pair <float, float>& waypoint = m_waypoints[m_currentIndex];
		m_currentIndex = (int)(rand() % m_waypoints.size());

		return waypoint;
	}
}

bool EnemigoIA::IsWithinRangeOfTarget(float minDistance) {

	SDL_Rect targetTransform = m_target->getRect();

	//Vectores auxiliares
	pair<float, float> targetPosition = make_pair(targetTransform.x, targetTransform.y);
	pair <float, float> position = make_pair(rect.x, rect.y);

	pair <float, float> toTarget = make_pair(targetPosition.first - position.first, targetPosition.second - position.second);

	float distance = sqrt((toTarget.first*toTarget.first) + (toTarget.second*toTarget.second));

	return (distance <= minDistance);
}
#include "EnemigoIA.h"
#include "IdleState.h"

EnemigoIA::EnemigoIA(Entidad * pEntidad, vector<Vector2> waypoints) : Enemigo(pEntidad, waypoints)
{
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
	
	Enemigo::Initialize();
	m_stateMachine = new StateMachine<EnemigoIA>(this);
	m_stateMachine->ChangeState(new IdleState());
}

void EnemigoIA::Update() {

	Enemigo::Update();
	m_stateMachine->Update();
}

StateMachine<EnemigoIA>*EnemigoIA::GetStateMachine() {
	return m_stateMachine;
}
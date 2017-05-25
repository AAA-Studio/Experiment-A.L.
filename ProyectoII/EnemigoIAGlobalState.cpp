#include "EnemigoIAGlobalState.h"
#include "EnemigoIA.h"
#include "ChaseState.h"


EnemigoIAGlobalState::EnemigoIAGlobalState() : State<EnemigoIA>()
{
	m_stateName = "EnemigoIAGlobalState";
}


EnemigoIAGlobalState::~EnemigoIAGlobalState()
{
}

void EnemigoIAGlobalState::Enter(EnemigoIA * character){

}

void EnemigoIAGlobalState::Execute(EnemigoIA * character){

	string currentStateName = character->GetStateMachine()->GetCurrentState()->getStateName();

	// distancia con el jugador
	if (currentStateName != "ChaseState")
	if (character->IsWithinRangeOfTarget(50.0f)) {
		character->SetVelocity(0, 0);
		character->GetStateMachine()->ChangeState(new ChaseState());
	}
}

void EnemigoIAGlobalState::Exit(EnemigoIA * character){

}

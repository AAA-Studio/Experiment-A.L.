#include "ChaseState.h"
#include "EnemigoIA.h"
#include "IdleState.h"

ChaseState::ChaseState() : State<EnemigoIA>()
{
	m_stateName = "ChaseState";
}

ChaseState::~ChaseState()
{
}

void ChaseState::Enter(EnemigoIA * character) {
	character->SetMaxVelocity(0.2f);
}

void ChaseState::Execute(EnemigoIA * character) {
	
	character->ChaseTarget();
	
	if (!character->IsWithinRangeOfTarget(50.0f)) {
		character->SetVelocity(0, 0);
		character->GetStateMachine()->ChangeState(new IdleState());
	} 	
}

void ChaseState::Exit(EnemigoIA * character) {
	character->SetVelocity(0, 0);
}
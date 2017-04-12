#include "StateMachine.h"

template<class character_type>
StateMachine<character_type>::StateMachine()
{
	m_globalState = 0;
	m_currentState = 0;
	m_previousState = 0;

}
						
template<class character_type>
StateMachine<character_type>::~StateMachine()
{

	if (m_globalState) {
		
		delete m_globalState;
		m_globalState = 0;

	}

	if (m_currentState) {
	
		delete m_currentState;
		m_currentState = 0;
	
	}

	
}

template<class character_type>
void StateMachine<character_type>::Update() {

	if (m_globalState) {
	
		m_globalState->Execute(m_owner);
	}

	if (m_currentState) {

		m_currentState->Execute(m_owner);
	}

	if (m_previousState) {

		m_previousState->Execute(m_owner);
	}
}

template<class character_type>
void StateMachine<character_type>::ChangeState(State<character_type>* state) {

	m_previousState = m_currentState;


	if (m_currentState) {

		m_currentState->Exit(m_owner);
		delete m_currentState;
		m_currentState = 0;
	}

	m_currentState = state;
	m_currentState->Enter(m_owner);

	if (m_currentState) {
	
		m_currentState->Enter(m_owner);
	}


}

template<class character_type>
void StateMachine<character_type>::RevertToPreviousState() {}


template<class character_type>
void StateMachine<character_type>::SetCurrentState(State <character_type>* state) {}

template<class character_type>
void StateMachine<character_type>::SetGlobalState(State <character_type>* state) {}

template<class character_type>
void StateMachine<character_type>::SetPreviousState(State <character_type>* state) {}

#ifndef _H_StateMachine_H_
#define _H_StateMachine_H_

#include "State.h" 

template<class character_type>

class StateMachine
{
public:
	StateMachine(character_type* pOwner) {
		m_globalState = 0;
		m_currentState = 0;
		m_previousState = 0;

		m_owner = pOwner;
	}

	~StateMachine() {
		if (m_globalState) {

			delete m_globalState;
			m_globalState = 0;

		}

		if (m_currentState) {

			delete m_currentState;
			m_currentState = 0;

		}
	}

	void Update() {
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

	void ChangeState(State<character_type>* state) {
		m_previousState = m_currentState;


		if (m_currentState) {

			m_currentState->Exit(m_owner);
			delete m_currentState;
			m_currentState = 0;
		}

		m_currentState = state;

		// Caso en el que puede que el estado al que vayamos este NULL
		if (m_currentState) m_currentState->Enter(m_owner);
		
		else {
			m_currentState = m_previousState;
			m_currentState->Enter(m_owner);
		}
	}

	void RevertToPreviousState() {
		ChangeState(m_previousState);
	}

	void SetGlobalState(State <character_type>* state) {
		if (m_globalState) {
			delete m_globalState;
			m_globalState = 0;
		}

		m_globalState = state;

		if (m_globalState) {

			m_globalState->Enter(m_owner);
		}
	}
	void SetPreviousState(State <character_type>* state) {
		if (m_previousState) {
			delete m_previousState;
			m_previousState = 0;
		}

		m_previousState = state;

		if (m_previousState) {

			m_previousState->Enter(m_owner);
		}
	}


private:
	State<character_type>* m_globalState;
	State<character_type>* m_currentState;
	State<character_type>* m_previousState;

	character_type* m_owner = nullptr;

};
#endif


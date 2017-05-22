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
	}

	void ChangeState(State<character_type>* state) {

		m_previousState = m_currentState;

		// Sale del estado y lo borra de la memoria
		if (m_currentState)  {
			m_currentState->Exit(m_owner);
			delete m_currentState;
			m_currentState = 0;
		}

		m_currentState = state;

		// Nos aseguramos de que el estado no esta a NULL y lo cambiamos
		if (m_currentState) { 
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
	State<character_type>* m_globalState = NULL;
	State<character_type>* m_currentState = NULL;
	State<character_type>* m_previousState = NULL;

	character_type* m_owner = nullptr;

};
#endif


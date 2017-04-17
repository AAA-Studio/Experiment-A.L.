#ifndef _H_StateMachine_H_
#define _H_StateMachine_H_

#include "State.h" 

template<class character_type>

class StateMachine
{
public:
	StateMachine(character_type* pOwner);
	~StateMachine();

	void Update(); 

	void ChangeState(State<character_type>* state);
	void RevertToPreviousState();

	// void SetCurrentState(State <character_type>* state);
	void SetGlobalState(State <character_type>* state);
	void SetPreviousState(State <character_type>* state);


private:
	State<character_type>* m_globalState;
	State<character_type>* m_currentState;
	State<character_type>* m_previousState;

	character_type* m_owner;

};
#endif


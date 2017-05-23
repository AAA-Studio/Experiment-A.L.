#ifndef _H_State_H
#define _H_State_H

#include <string>

template<class character_type>

//Virtual pura
class State
{
public:
	State() { m_stateName = ""; }
	virtual ~State() {}

	virtual void Enter(character_type * character) = 0;
	virtual void Execute(character_type * character) = 0;
	virtual void Exit (character_type * character) = 0;

	std::string getStateName() { return m_stateName; }

protected:

	std::string m_stateName;

};
#endif


#ifndef _H_State_H
#define _H_State_H

template<class character_type>

//Virtual pura
class State
{
public:
	State() {}
	virtual ~State() {}

	virtual void Enter(character_type * character) = 0;
	virtual void Execute(character_type * character) = 0;
	virtual void Exit (character_type * character) = 0;
};
#endif


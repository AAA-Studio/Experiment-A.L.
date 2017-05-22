#ifndef _H_EnemigoIAGlobalState_H_
#define _H_EnemigoIAGlobalState_H_
#include "State.h"
class EnemigoIA;

class EnemigoIAGlobalState : public State<EnemigoIA>
{
public:
	EnemigoIAGlobalState();
	~EnemigoIAGlobalState();

	void Enter(EnemigoIA * character);
	void Execute(EnemigoIA * character);
	void Exit(EnemigoIA * character);
};
#endif


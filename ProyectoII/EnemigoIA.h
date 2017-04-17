#ifndef _H_EnemigoIA_H_
#define _H_EnemigoIA_H_

#include "Enemigo.h"
#include "StateMachine.h"

class EnemigoIA: public Enemigo
{
public:
	EnemigoIA(Entidad * pEntidad, vector<Vector2> waypoints);
	~EnemigoIA();

	virtual void Initialize();
	virtual void Update();

private: 
	StateMachine<EnemigoIA*> m_stateMachine;
};
#endif

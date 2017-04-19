#ifndef _H_EnemigoIA_H_
#define _H_EnemigoIA_H_

#include "Enemigo.h"
#include "StateMachine.h"

class EnemigoIA: public Enemigo
{
public:

	EnemigoIA();
	EnemigoIA(Entidad * pEntidad, vector<Vector2> waypoints);
	~EnemigoIA();

	void Initialize();
	void Update();
	void ChaseTarget();
	bool IsWithinRangeOfTarget(float minDistance);
	StateMachine<EnemigoIA>* GetStateMachine();
	Vector2 findNextWayPoints();
private: 
	StateMachine<EnemigoIA>* m_stateMachine;
};
#endif

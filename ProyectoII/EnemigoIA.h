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

	StateMachine<EnemigoIA>* GetStateMachine();
protected:
	Vector2 findNextWayPoints();
	bool IsWithinRangeOfTarget(float minDistance);
private: 
	StateMachine<EnemigoIA>* m_stateMachine;
};
#endif

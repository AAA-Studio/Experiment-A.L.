#ifndef _H_Enemigo_H_
#define _H_Enemigo_H_

#include "checkML.h"
#include "Entidad.h"
#include "MathCore.h"
#include "Pathfinding.h"

class Enemigo: public Entidad
{
	enum PathState
	{
		CHECK_AROUND,
		RANDOMIZE,
		SEARCHING,
		FOUND_GOAL,
	};
	PathState m_pathState;
	PathFinding * m_pathfinding;
public:
	Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	~Enemigo();

	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual bool HandleKeydown(int key);
	virtual bool HandleKeyUp(int key);
	virtual void HandleMouseDown(bool isLeft, Vector3 mouseWorldPos);

	double radius;
	Vector3 pos;

private: 
	bool hasBeenHit;
	bool isAtGoal;
	bool lockedGuard;
	float regainControllerTimer;
	const float LASER_SIGTH_DIST = 500.0f;
	void RandomizeGoal();

	Vector3 targetPos;
};
#endif

#ifndef Enemigo_H
#define Enemigo_H

#include "checkML.h"
#include "Entidad.h"
#include "MathCore.h"
#include <vector>

#define M_PI 3.1416

class Enemigo: public Entidad
{
public:

	enum State {
		IDLE, 
		PATROL,
		CHASE,
	};

	// Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, vector <Vector2> waypoints);
	Enemigo();
	Enemigo(Entidad* pEntidad, vector <Vector2> waypoints);
	~Enemigo();

	//virtual void Draw();
	void Initialize();
	void Update();
	void SetTarget(Entidad*  target) { m_target = target; }	
	Vector2 pos;
	double radius;

protected: 

	Entidad * m_entidad;
	State m_currentState;
	vector <Vector2> m_waypoints; // Celdas por donde pasa el enmeigo
	Vector2 * m_currentWayPoint;
	Entidad* m_target;
	int m_currentIndex;
	float m_idleTime;
	float m_maxVelocity;
	Vector2 m_velocity;
	SDL_Rect* m_transform;
	// virtual bool HandleKeydown(int key);
	// virtual bool HandleKeyUp(int key);
	// virtual void HandleMouseDown(bool isLeft, Vector2 mouseWorldPos);

private: 
	bool hasBeenHit;
	bool isAtGoal;
	bool lockedGuard;
	float regainControllerTimer;
	int angle;
	const float LASER_SIGTH_DIST = 500.0f;

	void RandomizeGoal();
	bool GetEnemyView(const Vector2 &targetPos);
	void SetTargetTurretAngle(float angulos) { angle = angulos; }
	inline float GetTargetTurretAngle() const { return angle; }
	float rad2deg(double rad) { // de radianes a grados
		double deg = 0;
		deg = rad * (180/M_PI);
		return deg;
	}

	Vector2 targetPos;
};
#endif

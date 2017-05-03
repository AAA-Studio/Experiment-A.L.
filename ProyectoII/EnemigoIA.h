#ifndef _H_EnemigoIA_H_
#define _H_EnemigoIA_H_

#include "Enemigo.h"
#include "StateMachine.h"
#include "MathCore.h"
#include <vector>
#include "MundoVirtual.h"

#define M_PI 3.1416

class EnemigoIA : public Entidad, PersonajeVirtual
{
public:

	EnemigoIA(MundoVirtual*pM, int x, int y, int w, int h, Texturas_t textura, Efectos_t efecto);
	~EnemigoIA();

	void Initialize();
	virtual void update();

	void ChaseTarget();//Persigue al personaje
	bool IsWithinRangeOfTarget(float minDistance);//Devuelve true si esta en el rango con el personaje
	Vector2 findNextWayPoints();

	//GETTER
	StateMachine<EnemigoIA>* GetStateMachine();
	inline float getVida()const { return vida; };
	inline MapaVirtual* getMapa() const { return pMundo->getMapa(); };

	//SETTER
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	void SetVelocity(float velocityX, float velocityY) { m_velocity.SetX(velocityX); m_velocity.SetY(velocityY); }
	inline void restaVida() { vida--; };


protected: 
	StateMachine<EnemigoIA>* m_stateMachine;

	vector <Vector2> m_waypoints; // Celdas por donde pasa el enemigo
	Vector2 * m_currentWayPoint;

	float m_maxVelocity;
	Vector2 m_velocity;

	// Sobran algunas, comprobar cuales
	Entidad* m_target;//Puntero al personaje

	int m_currentIndex;

private:
	MundoVirtual* pMundo;
	int vida;

	/*
	int angle;
	const float LASER_SIGTH_DIST = 500.0f;

	
	bool GetEnemyView(const Vector2 &targetPos);
	void SetTargetTurretAngle(float angulos) { angle = angulos; }
	inline float GetTargetTurretAngle() const { return angle; }
	float rad2deg(double rad) { // de radianes a grados
		double deg = 0;
		deg = rad * (180 / M_PI);
		return deg;
	}
	*/
};
#endif

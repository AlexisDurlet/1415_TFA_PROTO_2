#ifndef	 ENEMY_H_INCLUDED
#define  ENEMY_H_INCLUDED

#include "collider_circle.h"

class TTime;
class TPlayer;
enum ETrajectories : int;

class TEnemy : private TColliderCircle
{
	private : 

		ETrajectories m_eTrajectory;
		float m_fRadialCoordinate;
		float m_fAngularCoordinate;
		float m_fAngularSpeed;

		int m_iLife;
		bool m_bAlive;
		TCircle m_tLifeCircle;

	public :

		int m_iLeftOrRight;
		int m_iPosY;
		int m_iUpOrDown;
		int m_iPosX;

		void Initialize(const ETrajectories &eTrajectory, const float fAngularSpeedDeg);
		void Update(const TTime &tTime, TPlayer &tPlayer);

		inline bool GetLifeState()
		{
			return m_bAlive;
		}

};

#endif

#ifndef	CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include "collider_circle.h"

enum ECellState : int;
class TTime;
class TPlayerModule;

class TCell : public TColliderCircle
{
	friend class TEnemy;
	friend class TPlayer;

	private:

		ECellState m_eState;
		int m_iInfectionSpeed;
		float m_iRed;
		float m_iGreen;
		int m_iTimeInfected;
		int m_iDeltaTimeInfected;

		int m_iLife;
		bool m_bAlive;
		TCircle m_tLifeCircle;

	public:

		inline void SetCenter(TGfxVec2 tCenter)
		{
			m_tCenter = tCenter;
		}

		void Initialize();
		void Update(const TTime & tTime, TPlayerModule * tPlayerModule);
};



#endif


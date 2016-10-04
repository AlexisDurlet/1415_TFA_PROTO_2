#ifndef	 PROJECTILE_H_INCLUDED
#define  PROJECTILE_H_INCLUDED

#include "movable _circle.h"

class TTime;

class TProjectile : private TMovableCircle
{
	friend class TEnemy;
	friend class TCell;

	protected:

		float m_fSpeed;
		TGfxVec2 m_tTarget;
		bool m_bActive;

	public:
	
		TProjectile();


		inline bool GetActive()
		{
			return m_bActive;
		}

		inline void SetCenter(TGfxVec2 tCenter)
		{
			m_tCenter = tCenter;
		}

		inline void SetRadius(float fRadius)
		{
			m_fRadius = fRadius;
		}

		inline void SetTarget(TGfxVec2 tTarget)
		{
			m_tTarget = tTarget;
		}
		

		void Initialize();
		void Update(const TTime &tTime);
		void Render();
};


#endif

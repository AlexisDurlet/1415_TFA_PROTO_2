#ifndef  PLAYER_MODULE_H_INCLUDED
#define  PLAYER_MODULE_H_INCLUDED

#include "circle.h"
#include "shooting_entity.h"

class TPlayerTarget;
class TTime;

class TPlayerModule : public TCircle, private TShootingEntity
{
	friend class TEnemy;
	friend class TCell;

	public:

		TPlayerModule();

		inline void SetCenter(TGfxVec2 tCenter)
		{
			m_tCenter = tCenter;
		}

		inline float GetRadius()
		{
			return m_fRadius;
		}

		void Initialize(const TPlayerTarget &tPlayerTarget, const float fFireRate, const float fProjectileRadius);
		void Update(const TTime &tTime, const TPlayerTarget &tPlayerTarget); 
		void Render();
};



#endif

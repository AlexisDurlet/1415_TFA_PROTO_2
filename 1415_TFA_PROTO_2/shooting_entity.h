#ifndef  SHOOTING_ENTITY_H_INCLUDED
#define	 SHOOTING_ENTITY_H_INCLUDED

#include "flib_vec2.h"
#include "projectile.h"
#include "constants.h"

class TTime;

class TShootingEntity
{
	friend class TEnemy;
	friend class TCell;

	private:

		TGfxVec2 m_tShootingEntityCenter;
		TGfxVec2 m_tTarget;

		float m_fProjectilePerSecond;
		float m_fProjectileRadius;
		TProjectile m_pProjectiles[MAX_PROJECTILES];
		int m_iProjectilesFired;
		int m_iProjectileIndex;
		int m_iProjectileToRender;
		int m_iLastTimeFired;


	public:

		TShootingEntity();

		inline void SetCenter(TGfxVec2 tCenter)
		{
			m_tShootingEntityCenter = tCenter;
		}

		inline void SetTarget(TGfxVec2 tTarget)
		{
			m_tTarget = tTarget;
		}

		
		void SetFire(float fFireRate, float fProjectileRadius);
		void Initialize();
		void Update(const TTime &tTime);
		void Render();
		
};


#endif

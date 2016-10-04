#include "shooting_entity.h"
#include "time.h"

TShootingEntity::TShootingEntity()
{
	m_fProjectilePerSecond = 0;
}

void TShootingEntity::SetFire(float fFireRate, float fProjectileRadius)
{
	m_fProjectilePerSecond = fFireRate;
	m_fProjectileRadius = fProjectileRadius;
	
}

void TShootingEntity::Initialize()
{
	m_iProjectilesFired = 0;
	m_iProjectileIndex = 0;
	m_iProjectileToRender = 0;
	m_iLastTimeFired = 0;
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		m_pProjectiles[i].SetCenter(m_tShootingEntityCenter);
		m_pProjectiles[i].SetRadius(m_fProjectileRadius);
		m_pProjectiles[i].SetTarget(m_tTarget);
	}
}

void TShootingEntity::Update(const TTime &tTime)
{
	int iTimeNow = tTime.GetTimeNow();
	int iLastShotTimeDelta = iTimeNow - m_iLastTimeFired;
	

	if (iLastShotTimeDelta > 1000 / m_fProjectilePerSecond)
	{
		m_iLastTimeFired = iTimeNow;
		m_iProjectilesFired++;
		if (m_iProjectileToRender < MAX_PROJECTILES)
		{
			m_iProjectileToRender++;
		}

		m_iProjectileIndex = (m_iProjectilesFired - 1) % (MAX_PROJECTILES);
		m_pProjectiles[m_iProjectileIndex].SetCenter(m_tShootingEntityCenter);
		m_pProjectiles[m_iProjectileIndex].SetTarget(m_tTarget);
		m_pProjectiles[m_iProjectileIndex].Initialize();
	}

	for (int i = 0; i < m_iProjectileToRender; i++)
	{
		if (m_pProjectiles[i].GetActive())
		{
			m_pProjectiles[i].Update(tTime);
		}
	}
}

void TShootingEntity::Render()
{
	for (int i = 0; i < m_iProjectileToRender; i++)
	{
		m_pProjectiles[i].Render();
	}
}
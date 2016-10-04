#include "projectile.h"
#include "time.h"
#include "constants.h"
#include "flib.h"

TProjectile::TProjectile()
{
	m_fRadius = 5;
	m_tTarget = TGfxVec2(0, 0);
	m_fSpeed = float(DEFAULT_PROJECTILE_SPEED);
}

void TProjectile::Initialize()
{
	m_bActive = true;

	if (m_tTarget - m_tCenter != TGfxVec2(0, 0))
	{
		m_tSpeed = (m_tTarget - m_tCenter).Normalize() * m_fSpeed;
	}
	else
	{
		m_tSpeed = TGfxVec2(0, 0);
	}


		TCircle::Initialize();
	
}

void TProjectile::Update(const TTime &tTime)
{
	TMovableCircle::MoveUpdate(tTime);
	TCircle::Update();
}

void TProjectile::Render()
{
	TCircle::Render();
}

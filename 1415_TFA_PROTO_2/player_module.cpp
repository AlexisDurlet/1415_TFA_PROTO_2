#include "player_module.h"
#include"player_target.h"
#include "constants.h"

TPlayerModule::TPlayerModule()
{
	m_fRadius = PLAYER_MODULE_RADIUS;
}

void TPlayerModule::Initialize(const TPlayerTarget &tPlayerTarget, const float fFireRate, const float fProjectileRadius)
{
	TShootingEntity::SetTarget(tPlayerTarget.GetCenter());
	TShootingEntity::SetCenter(m_tCenter);
	TShootingEntity::SetFire(fFireRate, fProjectileRadius);
	TShootingEntity::Initialize();

	TCircle::Initialize();
}

void TPlayerModule::Update(const TTime &tTime, const TPlayerTarget &tPlayerTarget)
{
	TShootingEntity::SetTarget(tPlayerTarget.GetCenter());
	TShootingEntity::Update(tTime);
	TCircle::Update();
}

void TPlayerModule::Render()
{
	TShootingEntity::Render();
	TCircle::Render();
}

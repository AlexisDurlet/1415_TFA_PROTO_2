#include "collider_circle.h"

bool TColliderCircle::Collision(TCircle tCollidedCircle)
{
	TGfxVec2 tCenterToCollidedCenter = tCollidedCircle.GetCenter() - m_tCenter;
	float fDistance = tCenterToCollidedCenter.Length();
	float fCollisionDistance = m_fRadius + tCollidedCircle.GetRadius();

	if (fDistance < fCollisionDistance)
	{
		return true;
	}
	
	return false;
}
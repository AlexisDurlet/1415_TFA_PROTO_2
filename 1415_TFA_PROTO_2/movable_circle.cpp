#include "movable _circle.h"
#include "time.h"

TMovableCircle::TMovableCircle()
{
	TCircle::TCircle();

	m_tSpeed = TGfxVec2(0, 0);
	m_tAcceleration = TGfxVec2(0, 0);
}

void TMovableCircle::MoveUpdate(const TTime &tTime)
{
	const float iTimeDelta = tTime.GetTimeDelta() / 1000.0f;

	m_tCenter = m_tCenter + iTimeDelta * m_tSpeed + (m_tAcceleration / 2) * iTimeDelta * iTimeDelta;
	m_tSpeed = m_tSpeed + m_tAcceleration * iTimeDelta;

}


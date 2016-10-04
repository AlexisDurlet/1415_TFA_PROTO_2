#include "time.h"
#include "flib.h"

void TTime::InitializeTime()
{
	m_iTimeNow = GfxTimeGetMilliseconds();
	m_iTimeBegin = m_iTimeNow;
	m_iTimePrevious = m_iTimeNow;
	m_iTimeFromBegin = m_iTimeNow;
}
void TTime::UpdateTime()
{
	m_iTimeNow = GfxTimeGetMilliseconds();
	m_iTimeFromBegin = m_iTimeNow - m_iTimeBegin;
	m_iTimeDelta = m_iTimeNow - m_iTimePrevious;
	m_iTimePrevious = m_iTimeNow;
}
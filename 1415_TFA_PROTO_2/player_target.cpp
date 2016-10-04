#include "player_target.h"
#include"constants.h"
#include "flib.h"
#include "math.h"
#include "float.h"

TPlayerTarget::TPlayerTarget()
:TCircle(TGfxVec2(0,0), PLAYER_TARGET_RADIUS)
{
}

void TPlayerTarget::Initialize()
{
	m_bGrabbed = false;
	TCircle::Initialize();
}

void TPlayerTarget::Update(const TGfxVec2 &tMousePos, TPlayerTarget * tOtherTargets, const int iOtherTargetsnumber, int iTargetIndex)
{
	TGfxVec2 tTargetToMouse = tMousePos - m_tCenter;

	const int iToleranceZone = 10;

	bool bInputIsJustPressed = GfxInputIsJustPressed(EGfxInputID_MouseLeft);

	if (bInputIsJustPressed)
	{
		if (tTargetToMouse.Length() < m_fRadius + iToleranceZone)
		{
			m_bGrabbed = true;
		}
		else
		{
			m_bGrabbed = false;
		}
	}

	if (m_bGrabbed)
	{
		if (tMousePos != TGfxVec2(FLT_MAX, FLT_MAX))
		{
			m_tCenter = tMousePos;
		}
	}

	for (int i = 0; i < iOtherTargetsnumber; i++)
	{
		if (i != iTargetIndex)
		{
			const TGfxVec2 tCurrentToCollided = tOtherTargets[i].GetCenter() - m_tCenter;
			const float fMaxDist = 2 * PLAYER_TARGET_RADIUS + 2 * iToleranceZone;

			if (tCurrentToCollided.Length() < fMaxDist && tCurrentToCollided != TGfxVec2(0, 0))
			{
				TGfxVec2 tCorrectedCenter = m_tCenter  + tCurrentToCollided.Normalize() * fMaxDist;
				tOtherTargets[i].SetCenter(tCorrectedCenter);
			}
			else if (tCurrentToCollided == TGfxVec2(0, 0))
			{
				TGfxVec2 tCorrectedCenter = m_tCenter + TGfxVec2(0, 1) * fMaxDist;
				tOtherTargets[i].SetCenter(tCorrectedCenter);
			}

			TGfxVec2 tWindow(GfxGetDisplaySizeX() / 2.0f, GfxGetDisplaySizeY() / 2.0f);

			if (fabsf(tOtherTargets[i].GetCenter().x) > tWindow.x)
			{
				TGfxVec2 tCorrectedCenter = tOtherTargets[i].GetCenter() + TGfxVec2(-copysignf(1.0, tOtherTargets[i].GetCenter().x) * PLAYER_TARGET_RADIUS * 2, 0);
				tOtherTargets[i].SetCenter(tCorrectedCenter);
			}

			if (fabsf(tOtherTargets[i].GetCenter().y) > tWindow.y)
			{
				TGfxVec2 tCorrectedCenter = tOtherTargets[i].GetCenter() + TGfxVec2(0, -copysignf(1.0, tOtherTargets[i].GetCenter().y) * PLAYER_TARGET_RADIUS * 2);
				tOtherTargets[i].SetCenter(tCorrectedCenter);
			}
		}
	}



	TCircle::Update();
}

void TPlayerTarget::Render()
{
	TCircle::Render();
}
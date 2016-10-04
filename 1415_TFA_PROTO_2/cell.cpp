#include "cell.h"
#include "constants.h"
#include "e_cell_state.h"
#include "time.h"
#include "flib.h"
#include "player.h"
#include "projectile.h"
#include "float.h"

void TCell::Initialize()
{
	m_fRadius = PLAYER_ALLIES_CELLS_RADIUS;
	m_eState = ECellState_Healthy;
	m_iRed = 0;
	m_iGreen = 255;
	m_iInfectionSpeed = 0;
	SetColor(GfxColor(m_iRed, m_iGreen, 0, 255));

	m_iLife = PLAYER_ALLIES_CELLS_LIFE;
	m_bAlive = true;
}

void TCell::Update(const TTime & tTime, TPlayerModule * tPlayerModule)
{
	if (m_bAlive)
	{
		const float fDeltaTime = tTime.GetTimeDelta() / 1000.0f;

		switch (m_eState)
		{
		case ECellState_Healthy:

			SetColor(GfxColor(m_iRed, m_iGreen, 0, 255));

			break;

		case ECellState_BeingInfected:

			m_iRed += m_iInfectionSpeed * (fDeltaTime);
			m_iGreen -= m_iInfectionSpeed * (fDeltaTime);

			if (m_iRed > 255 || m_iGreen < 0)
			{
				m_iRed = 255;
				m_iGreen = 0;
				SetColor(EGfxColor_Red);
				m_eState = ECellState_Infected;
			}

			SetColor(GfxColor(m_iRed, m_iGreen, 0, 255));

			for (int p = 0; p < MAX_PROJECTILES; p++)
			{
				for (int m = 0; m < PLAYER_MODULES_NUMBER; m++)
				{
					if (tPlayerModule[m].m_pProjectiles[p].GetActive())
					{
						if (Collision(tPlayerModule[m].m_pProjectiles[p]))
						{
							tPlayerModule[m].m_pProjectiles[p].m_bActive = false;
							tPlayerModule[m].m_pProjectiles[p].SetCenter(TGfxVec2(FLT_MAX, FLT_MAX));

							m_iLife--;
							if (m_iLife == 0)
							{
								m_bAlive = false;
								return;
							}
						}
					}
				}
			}

			break;

		case ECellState_Infected:

			for (int p = 0; p < MAX_PROJECTILES; p++)
			{
				for (int m = 0; m < PLAYER_MODULES_NUMBER; m++)
				{
					if (tPlayerModule[m].m_pProjectiles[p].GetActive())
					{
						if (Collision(tPlayerModule[m].m_pProjectiles[p]))
						{
							tPlayerModule[m].m_pProjectiles[p].m_bActive = false;
							tPlayerModule[m].m_pProjectiles[p].SetCenter(TGfxVec2(FLT_MAX, FLT_MAX));

							m_iLife--;
							if (m_iLife == 0)
							{
								m_bAlive = false;
								return;
							}
						}
					}
				}
			}

			break;
		}

		m_tCenter = m_tCenter.Rotate(GfxMathDegToRad(PLAYER_ALLIES_CELLS_ANGULAR_SPEED * fDeltaTime));

		TCircle::Update();
		m_fRadius = PLAYER_ALLIES_CELLS_RADIUS - ((PLAYER_ALLIES_CELLS_LIFE - m_iLife) * (PLAYER_ALLIES_CELLS_RADIUS / PLAYER_ALLIES_CELLS_LIFE));
		TCircle::Update();
		m_fRadius = PLAYER_ALLIES_CELLS_RADIUS;

	}
}
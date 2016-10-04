#include "player.h"
#include "flib.h"
#include "float.h"
#include "e_cell_state.h"
#include "time.h"
#include "enemy_wave.h"

void TPlayer::Initialize()
{
	m_bPlayerDead = false;

	float fCircleAngle = 360;
	float fRepartitionAngle = fCircleAngle / PLAYER_MODULES_NUMBER;
	TGfxVec2 tRepartitionDirection = TGfxVec2(0, 1);

	for (int i = 0; i < PLAYER_MODULES_NUMBER; i++)
	{
		TGfxVec2 tRotatedRepartitionDirection = tRepartitionDirection.Rotate(GfxMathDegToRad( i * fRepartitionAngle));
		TGfxVec2 tModuleCenter = m_tCenter + tRotatedRepartitionDirection * m_pModules[i].GetRadius();
		m_pModules[i].SetCenter(tModuleCenter);
		m_pTargets[i].SetCenter(tModuleCenter + 75 * tRotatedRepartitionDirection);

		m_pTargets[i].Initialize();
		m_pModules[i].Initialize(m_pTargets[i], PLAYER_FIRE_RATE, PLAYER_PROJECTILES_RADIUS);
		m_pTargets[i].SetColor(EGfxColor_Blue);
		m_pModules[i].SetColor(EGfxColor_Blue);
	}

	fRepartitionAngle = fCircleAngle / PLAYER_ALLIES_CELLS_NUMBER;
	for (int r = 0; r < PLAYER_ALLIES_CELLS_RANK; r++)
	{
		for (int i = 0; i < PLAYER_ALLIES_CELLS_NUMBER; i++)
		{
			float fAngle = i * fRepartitionAngle + r * 15;
			TGfxVec2 tRotatedRepartitionDirection = tRepartitionDirection.Rotate(GfxMathDegToRad(fAngle));
			TGfxVec2 tCellCenter = m_tCenter + tRotatedRepartitionDirection * (((PLAYER_MODULE_RADIUS * 2) + PLAYER_ALLIES_CELLS_RADIUS) + r * 2 * PLAYER_ALLIES_CELLS_RADIUS);

			m_pCells[r * PLAYER_ALLIES_CELLS_NUMBER + i].SetCenter(tCellCenter);
			m_pCells[r * PLAYER_ALLIES_CELLS_NUMBER + i].Initialize();
		}
	}
	m_tCenter = TGfxVec2(0, 0);
	m_fRadius = PLAYER_MODULE_RADIUS * 2;

	TCircle::Initialize();
	TCircle::SetColor(EGfxColor_Blue);
	
}


void TPlayer::Update(const TTime &tTime, const int &iMouseNumber, const TGfxVec2 * tMousePos)
{
	if (!m_bPlayerDead)
	{
		for (int i = 0; i < PLAYER_MODULES_NUMBER; i++)
		{
			for (int j = 0; j < iMouseNumber; j++)
			{
				m_pTargets[i].Update(tMousePos[j], m_pTargets, PLAYER_MODULES_NUMBER, i);
			}
			if (iMouseNumber == 0)
			{
				m_pTargets[i].Update(TGfxVec2(FLT_MAX, FLT_MAX), m_pTargets, PLAYER_MODULES_NUMBER, i);
			}


			m_pModules[i].Update(tTime, m_pTargets[i]);

		}

		for (int r = 0; r < PLAYER_ALLIES_CELLS_RANK; r++)
		{
			for (int i = 0; i < PLAYER_ALLIES_CELLS_NUMBER; i++)
			{
				const int iIndex = r * PLAYER_ALLIES_CELLS_NUMBER + i;
				const int iNextRankIndex = (r + 1) * PLAYER_ALLIES_CELLS_NUMBER + i;
				const int iPreviousRankIndex = (r - 1) * PLAYER_ALLIES_CELLS_NUMBER + i;

				if (iNextRankIndex < PLAYER_ALLIES_CELLS_NUMBER * PLAYER_ALLIES_CELLS_RANK)
				{
					if (m_pCells[iNextRankIndex].m_eState == ECellState_Infected)
					{
						switch (m_pCells[iIndex].m_eState)
						{
						case ECellState_Healthy:

							m_pCells[iIndex].m_eState = ECellState_BeingInfected;
							m_pCells[iIndex].m_iInfectionSpeed += ENEMY_INFECTION_SPEED;

							break;

						default:

							break;
						}
					}
				}

				if (iPreviousRankIndex >= 0)
				{
					if (m_pCells[iPreviousRankIndex].m_eState == ECellState_Infected)
					{
						switch (m_pCells[iIndex].m_eState)
						{
						case ECellState_Healthy:

							m_pCells[iIndex].m_eState = ECellState_BeingInfected;
							m_pCells[iIndex].m_iInfectionSpeed += ENEMY_INFECTION_SPEED;

							break;

						default:

							break;
						}
					}
				}


				m_pCells[iIndex].Update(tTime, m_pModules);
			}
		}


		bool bAllCellsDeadOrInfected = true;
		for (int i = 0; i < PLAYER_ALLIES_CELLS_NUMBER * PLAYER_ALLIES_CELLS_RANK; i++)
		{
			if (m_pCells[i].m_eState == ECellState_Healthy)
			{
				bAllCellsDeadOrInfected = false;
			}
		}

		if (bAllCellsDeadOrInfected)
		{
			m_bPlayerDead = true;
			m_iTimeOfDeath = tTime.GetTimeNow();
		}


		TCircle::Update();
	}
}


void TPlayer::Render()
{
	for (int i = 0; i < PLAYER_MODULES_NUMBER; i++)
	{
		m_pTargets[i].Render();
		m_pModules[i].Render();
	}
	TCircle::Render();
}

void TPlayer::RenderDeath(TTime &tTime, TEnemyWave * tEnemyWaves, int iWavesNumber)
{
	if (m_bPlayerDead)
	{
		m_iDeltaTimeOfDeath = tTime.GetTimeNow() - m_iTimeOfDeath;

		if (m_iDeltaTimeOfDeath < 500)
		{
			GfxClear(EGfxColor_Red);
		}
		else if ((m_iDeltaTimeOfDeath > 500))
		{
			TPlayer::Initialize();
			tTime.InitializeTime();

			for (int i = 0; i < iWavesNumber; i++)
			{
				tEnemyWaves[i].m_bActive = false;
				tEnemyWaves[i].Finalize();
			}

			m_bPlayerDead = false;
		}
	}

}

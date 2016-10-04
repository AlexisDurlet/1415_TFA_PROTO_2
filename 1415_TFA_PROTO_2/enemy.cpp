#include"enemy.h"
#include "flib.h"
#include "constants.h"
#include"time.h"
#include "e_trajectories.h"
#include "player.h"
#include "float.h"
#include "e_cell_state.h"

void TEnemy::Initialize(const ETrajectories &eTrajectory, const float fAngularSpeedDeg)
{
	m_eTrajectory = eTrajectory;

	switch (m_eTrajectory)
	{
		case ETrajectories_SpiralFromUp:

			m_fAngularSpeed = -(GfxMathDegToRad(fAngularSpeedDeg) / 1000.0f);

			m_fAngularCoordinate = GfxMathDegToRad(ARCHIMEDES_SPIRAL_BEGIN_ANGLE);

			break;

		case ETrajectories_SpiralFromDown:

			m_fAngularSpeed = -(GfxMathDegToRad(fAngularSpeedDeg) / 1000.0f);

			m_fAngularCoordinate = GfxMathDegToRad(ARCHIMEDES_SPIRAL_BEGIN_ANGLE);

			break;

		case ETrajectories_RandomStraightLineX:

			m_fAngularSpeed = fAngularSpeedDeg;

			m_iLeftOrRight = GfxMathGetRandomInteger(1, 2);
			if (m_iLeftOrRight == 2) m_iLeftOrRight = -1;

			m_iPosY = GfxMathGetRandomInteger(-GfxGetDisplaySizeY() / 2 , GfxGetDisplaySizeY() / 2);

			m_tCenter = TGfxVec2(m_iLeftOrRight * (GfxGetDisplaySizeX() / 2.0f), m_iPosY/1.0f);

			m_tSpeed = - m_tCenter.Normalize() * m_fAngularSpeed;

			break;

		case ETrajectories_RandomStraightLineY:

			m_fAngularSpeed = fAngularSpeedDeg;

			m_iUpOrDown = GfxMathGetRandomInteger(1, 2);
			if (m_iUpOrDown == 2) m_iUpOrDown = -1;

			m_iPosX = GfxMathGetRandomInteger(-GfxGetDisplaySizeX() / 2, GfxGetDisplaySizeX() / 2 );

			m_tCenter = TGfxVec2(m_iPosX / 1.0f , m_iUpOrDown * (GfxGetDisplaySizeY() / 2.0f));

			m_tSpeed = - m_tCenter.Normalize() * m_fAngularSpeed;

			break;

		case ETrajectories_RandomConstantStraightLineX:

			m_fAngularSpeed = fAngularSpeedDeg;

			m_tCenter = TGfxVec2(m_iLeftOrRight * (GfxGetDisplaySizeX() / 2.0f), m_iPosY / 1.0f);

			m_tSpeed = -m_tCenter.Normalize() * m_fAngularSpeed;

			break;

		case ETrajectories_RandomConstantStraightLineY:

			m_fAngularSpeed = fAngularSpeedDeg;

			m_tCenter = TGfxVec2(m_iPosX / 1.0f, m_iUpOrDown * (GfxGetDisplaySizeY() / 2.0f));

			m_tSpeed = -m_tCenter.Normalize() * m_fAngularSpeed;

			break;


	}
	
	m_fRadius = ENEMY_RADIUS;
	TCircle::SetColor(EGfxColor_Red);

	m_iLife = ENEMY_LIFE;
	m_bAlive = true;
}

void TEnemy::Update(const TTime &tTime, TPlayer &tPlayer)
{
	if (m_bAlive)
	{
		const int iTimeDeta = tTime.GetTimeDelta();
		const TGfxVec2 tTrigonoVec = TGfxVec2(1, 0);

		m_fAngularCoordinate = m_fAngularCoordinate + m_fAngularSpeed * iTimeDeta;

		switch (m_eTrajectory)
		{
		case ETrajectories_SpiralFromUp:

			m_fRadialCoordinate = - ARCHIMEDES_SPIRAL_A_ARBITRARY_CONSTANT - ARCHIMEDES_SPIRAL_B_ARBITRARY_CONSTANT * m_fAngularCoordinate;

			m_tCenter = tTrigonoVec.Rotate(m_fAngularCoordinate) * m_fRadialCoordinate;

			break;

		case ETrajectories_SpiralFromDown:

			m_fRadialCoordinate = ARCHIMEDES_SPIRAL_A_ARBITRARY_CONSTANT + ARCHIMEDES_SPIRAL_B_ARBITRARY_CONSTANT * m_fAngularCoordinate;

			m_tCenter = tTrigonoVec.Rotate(m_fAngularCoordinate) * m_fRadialCoordinate;

			break;

		default:

			MoveUpdate(tTime);

			break;

		}



		if (Collision(tPlayer))
		{
			m_iLife = 0;
			m_bAlive = false;
			return;
		}

		for (int p = 0; p < MAX_PROJECTILES; p++)
		{
			for (int m = 0; m < PLAYER_MODULES_NUMBER; m++)
			{
				if (tPlayer.m_pModules[m].m_pProjectiles[p].GetActive())
				{
					if (Collision(tPlayer.m_pModules[m].m_pProjectiles[p]))
					{
						tPlayer.m_pModules[m].m_pProjectiles[p].m_bActive = false;
						tPlayer.m_pModules[m].m_pProjectiles[p].SetCenter(TGfxVec2(FLT_MAX, FLT_MAX));

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

		for (int i = 0; i < PLAYER_ALLIES_CELLS_NUMBER * PLAYER_ALLIES_CELLS_RANK; i++)
		{
			if (tPlayer.m_pCells[i].m_eState != ECellState_Infected)
			{
				if (Collision(tPlayer.m_pCells[i]))
				{

					tPlayer.m_pCells[i].m_eState = ECellState_BeingInfected;
					tPlayer.m_pCells[i].m_iInfectionSpeed += ENEMY_INFECTION_SPEED;

					m_iLife = 0;
					m_bAlive = false;
					return;
				}
			}
		}

		TCircle::Update();
		m_fRadius = ENEMY_RADIUS - ((ENEMY_LIFE - m_iLife) * (ENEMY_RADIUS / ENEMY_LIFE));
		TCircle::Update();
		m_fRadius = ENEMY_RADIUS;
	}
}
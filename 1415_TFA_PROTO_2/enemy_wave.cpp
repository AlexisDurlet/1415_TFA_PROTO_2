#include "enemy_wave.h"
#include "time.h"
#include "enemy.h"
#include "player.h"
#include "e_trajectories.h"
#include "flib.h"

TEnemyWave::TEnemyWave()
{
	m_bActive = false;
	m_bInitialized = false;
	m_bFinalized = false;
	m_pEnemy = nullptr;
}

TEnemyWave::~TEnemyWave()
{
	delete[] m_pEnemy;
}


void TEnemyWave::Initialize(const TTime &tTime, const ETrajectories eTrajectory, const int iDuration, const int iMaxEnemiesNumber, const float fEnnemiesSpeed)
{
	const int iTimeNow = tTime.GetTimeNow();

	m_eTrajectory = eTrajectory;
	m_iDuration = iDuration;
	m_iMaxEnemiesNumber = iMaxEnemiesNumber;
	m_iTimeLauch = iTimeNow;
	m_iTimeDeltaLauch = iTimeNow;
	m_bActive = true;
	m_bInitialized = true;

	if (!m_bFinalized)
	{
		m_pEnemy = new TEnemy[m_iMaxEnemiesNumber];
	}
	m_fEnnemiesSpeed = fEnnemiesSpeed;
	m_iEnemiesSpawned = 0;
	m_fEnnemiesTimeInterval = m_iDuration / (m_iMaxEnemiesNumber * 1.0f);

	switch (m_eTrajectory)
	{
		case ETrajectories_RandomConstantStraightLineX:

			m_iLeftOrRight = GfxMathGetRandomInteger(1, 2);
			if (m_iLeftOrRight == 2) m_iLeftOrRight = -1;

			m_iPosY = GfxMathGetRandomInteger(-GfxGetDisplaySizeY() / 2, GfxGetDisplaySizeY() / 2);

			break;

		case ETrajectories_RandomConstantStraightLineY:

			m_iUpOrDown = GfxMathGetRandomInteger(1, 2);
			if (m_iUpOrDown == 2) m_iUpOrDown = -1;

			m_iPosX = GfxMathGetRandomInteger(-GfxGetDisplaySizeX() / 2, GfxGetDisplaySizeX() / 2);

			break;

		default:


			break;

	}

	TCircle::Initialize();

}

void TEnemyWave::Update(const TTime &tTime, TPlayer &tPlayer)
{
	const int iTimeNow = tTime.GetTimeNow();
	m_iTimeDeltaLauch = iTimeNow - m_iTimeLauch;

	if (m_fEnnemiesTimeInterval * m_iEnemiesSpawned < m_iTimeDeltaLauch && m_iEnemiesSpawned < m_iMaxEnemiesNumber)
	{
		m_iEnemiesSpawned++;

		switch (m_eTrajectory)
		{
		case ETrajectories_RandomConstantStraightLineX:

			m_pEnemy[m_iEnemiesSpawned - 1].m_iLeftOrRight = m_iLeftOrRight;
			m_pEnemy[m_iEnemiesSpawned - 1].m_iPosY = m_iPosY;

			break;

		case ETrajectories_RandomConstantStraightLineY:

			m_pEnemy[m_iEnemiesSpawned - 1].m_iUpOrDown = m_iUpOrDown;
			m_pEnemy[m_iEnemiesSpawned - 1].m_iPosX = m_iPosX;

			break;

		default:


			break;
		}

		m_pEnemy[m_iEnemiesSpawned - 1].Initialize(m_eTrajectory, m_fEnnemiesSpeed);
	}


	bool bAllEnemiesDead = false;

	if (m_iEnemiesSpawned == m_iMaxEnemiesNumber)
	{
		bAllEnemiesDead = true;
		for (int i = 0; i < m_iEnemiesSpawned; i++)
		{
			if (m_pEnemy[i].GetLifeState())
			{
				bAllEnemiesDead = false;
			}
		}
	}

	m_bActive = !bAllEnemiesDead;

	if (m_bActive)
	{
		for (int i = 0; i < m_iEnemiesSpawned; i++)
		{
			m_pEnemy[i].Update(tTime, tPlayer);
			if (!m_pEnemy[i].GetLifeState())
			{
				m_pEnemy[i].~TEnemy();
			}
		}
	}
}

void TEnemyWave::Finalize()
{
	m_bInitialized = false;

	m_bFinalized = true;
}

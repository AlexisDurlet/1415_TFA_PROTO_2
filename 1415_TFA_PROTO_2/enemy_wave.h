#ifndef	ENNEMY_WAVE_INCLUDED
#define ENNEMY_WAVE_INCLUDED

#include "circle.h"

class TTime;
class TEnemy;
class TPlayer;
enum ETrajectories : int;

class TEnemyWave : private TCircle
{

	friend class TPlayer;

	private :

		int m_iTimeLauch;
		int m_iTimeDeltaLauch;
		int m_iDuration;
		bool m_bInitialized;
		bool m_bFinalized;
		bool m_bActive;

		TEnemy * m_pEnemy;
		float m_fEnnemiesSpeed;
		int m_iEnemiesSpawned;
		int m_iMaxEnemiesNumber;
		float m_fEnnemiesTimeInterval;

		ETrajectories m_eTrajectory;
		int m_iLeftOrRight;
		int m_iPosY;
		int m_iUpOrDown;
		int m_iPosX;

	public :

		TEnemyWave();

		bool GetInitialization()
		{
			return m_bInitialized;
		}

		bool GetActive()
		{
			return m_bActive;
		}

		void Initialize(const TTime &tTime, const ETrajectories eTrajectory, const int iDuration, const int iMaxEnemiesNumber, const float fEnnemiesSpeed);
		void Update(const TTime &tTime, TPlayer &tPlayer);
		void Finalize();

		~TEnemyWave();
};


#endif

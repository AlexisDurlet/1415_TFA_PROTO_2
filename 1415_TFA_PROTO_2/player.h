#ifndef	PLAYER_INCLUDED_H
#define PLAYER_INCLUDED_H

#include "constants.h"
#include "circle.h"
#include "player_module.h"
#include "player_target.h"
#include "cell.h"

class TTime;
class TEnemyWave;

class TPlayer : private TCircle
{
	friend class TEnemy;
	friend class TCell;

	private:

		TPlayerModule m_pModules[PLAYER_MODULES_NUMBER];
		TPlayerTarget m_pTargets[PLAYER_MODULES_NUMBER];
		TCell m_pCells[PLAYER_ALLIES_CELLS_NUMBER * PLAYER_ALLIES_CELLS_NUMBER];

		bool m_bPlayerDead;
		int m_iTimeOfDeath;
		int m_iDeltaTimeOfDeath;

	public:

		void Initialize();
		void Update(const TTime &tTime, const int &iMouseNumber, const TGfxVec2 * tMousePos);
		void Render();
		void RenderDeath(TTime &tTime, TEnemyWave * tEnemyWaves, int iWavesNumber);

};



#endif

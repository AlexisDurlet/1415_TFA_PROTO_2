#include "flib.h"
#include "time.h"
#include "constants.h"
#include "player.h"
#include "enemy_wave.h"
#include "e_trajectories.h"

TTime g_tTime;
TCircle g_tCircles;

TPlayer g_tPlayer;
const int ENNEMY_WAVES = 10;
TEnemyWave g_tEnemyWave[ENNEMY_WAVES];
bool g_bWaveToUpdate[ENNEMY_WAVES];


TGfxSprite * g_pFPS;

void Initialize()
{
	g_tTime.InitializeTime();
	g_tCircles.Initialize();

	for (int i = 0; i < ENNEMY_WAVES; i++)
	{
		g_bWaveToUpdate[i] = false;
	}

	g_tPlayer.Initialize();

	g_pFPS = GfxTextSpriteCreate();
	GfxSpriteSetPosition(g_pFPS, 10, 10);
}

void Update()
{
	g_tTime.UpdateTime();

	g_tCircles.Reset();

	if (g_tTime.GetTimeFromBegin() > 0 && !g_tEnemyWave[0].GetInitialization())
	{
		g_tEnemyWave[0].Initialize(g_tTime, ETrajectories_SpiralFromDown, 60 * 1000, 60, 60);
		g_bWaveToUpdate[0] = true;
	}
	if (g_tTime.GetTimeFromBegin() > 0 && !g_tEnemyWave[1].GetInitialization())
	{
		g_tEnemyWave[1].Initialize(g_tTime, ETrajectories_SpiralFromUp, 60 * 1000, 60, 60);
		g_bWaveToUpdate[1] = true;
	}
	if (g_tTime.GetTimeFromBegin() > 0 && !g_tEnemyWave[2].GetInitialization())
	{
		g_tEnemyWave[2].Initialize(g_tTime, ETrajectories_RandomStraightLineX, 60 * 1000, 10, 25);
		g_bWaveToUpdate[2] = true;
	}
	if (g_tTime.GetTimeFromBegin() > 0 && !g_tEnemyWave[3].GetInitialization())
	{
		g_tEnemyWave[3].Initialize(g_tTime, ETrajectories_RandomStraightLineY, 60 * 1000, 10, 25);
		g_bWaveToUpdate[3] = true;
	}

	if (g_tTime.GetTimeFromBegin() > 0 * 1000 && !g_tEnemyWave[4].GetInitialization())
	{
		g_tEnemyWave[4].Initialize(g_tTime, ETrajectories_RandomConstantStraightLineX, 10 * 1000, 10, 20);
		g_bWaveToUpdate[4] = true;
	}

	if (g_tTime.GetTimeFromBegin() > 20 * 1000 && !g_tEnemyWave[5].GetInitialization())
	{
		g_tEnemyWave[5].Initialize(g_tTime, ETrajectories_RandomConstantStraightLineX, 10 * 1000, 10, 20);
		g_bWaveToUpdate[5] = true;
	}

	if (g_tTime.GetTimeFromBegin() > 40 * 1000 && !g_tEnemyWave[6].GetInitialization())
	{
		g_tEnemyWave[6].Initialize(g_tTime, ETrajectories_RandomConstantStraightLineX, 10 * 1000, 10, 20);
		g_bWaveToUpdate[6] = true;
	}

	if (g_tTime.GetTimeFromBegin() > 10 * 1000 && !g_tEnemyWave[7].GetInitialization())
	{
		g_tEnemyWave[7].Initialize(g_tTime, ETrajectories_RandomConstantStraightLineY, 10 * 1000, 10, 20);
		g_bWaveToUpdate[7] = true;
	}

	if (g_tTime.GetTimeFromBegin() > 30 * 1000 && !g_tEnemyWave[8].GetInitialization())
	{
		g_tEnemyWave[8].Initialize(g_tTime, ETrajectories_RandomConstantStraightLineY, 10 * 1000, 10, 20);
		g_bWaveToUpdate[8] = true;
	}

	if (g_tTime.GetTimeFromBegin() > 50 * 1000 && !g_tEnemyWave[9].GetInitialization())
	{
		g_tEnemyWave[9].Initialize(g_tTime, ETrajectories_RandomConstantStraightLineY, 10 * 1000, 10, 20);
		g_bWaveToUpdate[9] = true;
	}


	const int iMouseNumber = GfxInputGetMouseCount();
	TGfxVec2 tMousePos[2];
	for (int i = 0; i < iMouseNumber; i++)
	{
		tMousePos[i] = TGfxVec2(GfxInputGetMousePositionX(i) - GfxGetDisplaySizeX() / 2.0f, -GfxInputGetMousePositionY(i) + GfxGetDisplaySizeY() / 2.0f);
	}

	g_tPlayer.Update(g_tTime, iMouseNumber, tMousePos);

	for (int i = 0; i < ENNEMY_WAVES; i++)
	{
		if (!g_tEnemyWave[i].GetActive())
		{
			g_bWaveToUpdate[i] = false;
		}
	}

	for (int i = 0; i < ENNEMY_WAVES; i++)
	{
		if (g_bWaveToUpdate[i])
		{
			g_tEnemyWave[i].Update(g_tTime, g_tPlayer);
		}
	}

	GfxTextSpritePrintf(g_pFPS, "%f", GfxTimeFrameGetAverageFPS());

	bool bAllEnemyWavesDefeated = true;
	for (int i = 0; i < ENNEMY_WAVES; i++)
	{
		if (g_tEnemyWave[i].GetActive())
		{
			bAllEnemyWavesDefeated = false;
		}
	}
	if (bAllEnemyWavesDefeated)
	{
		g_tTime.InitializeTime();

		for (int i = 0; i < ENNEMY_WAVES; i++)
		{
			g_tEnemyWave[i].Finalize();
		}
	}

}

void Render()
{
	GfxClear(EGfxColor_Black);

	g_tCircles.Render();

	g_tPlayer.RenderDeath(g_tTime, g_tEnemyWave, ENNEMY_WAVES);

	GfxSpriteRender(g_pFPS);

}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}



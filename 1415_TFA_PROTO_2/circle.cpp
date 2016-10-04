#include "circle.h"
#include "flib.h"
#include "math.h"

static TGfxSprite *  m_pSprite;
static bool m_bInitialized;

TCircle::TCircle()
{
	m_bInitialized = false;
	m_tCenter = TGfxVec2(0, 0);
	m_fRadius = 0;
	m_pSprite = nullptr;
	m_iColor = EGfxColor_White;
}

TCircle::TCircle(TGfxVec2 tCenter, float fRadius)
{
	m_bInitialized = false;
	m_tCenter = tCenter;
	m_fRadius = fRadius;
	m_pSprite = nullptr;
	m_iColor = EGfxColor_White;
}

void TCircle::InitializeSprite()
{
	m_pSprite = GfxLineSpriteCreate();
	GfxSpriteSetScale(m_pSprite, 1, -1);
	GfxSpriteSetPosition(m_pSprite, GfxGetDisplaySizeX() / 2.0f, GfxGetDisplaySizeY() / 2.0f);
}

void TCircle::Draw()
{
	GfxLineSpriteSetDrawingColor(m_pSprite, m_iColor);

	GfxLineSpriteJumpTo(m_pSprite, m_tCenter.x + m_fRadius, m_tCenter.y);

	int iCircleIterations = 36;

	for (int i = 0; i < iCircleIterations; i++)
	{
		float fAngle = GfxMathDegToRad((360.0f / iCircleIterations) * (i + 1));
		GfxLineSpriteLineTo(m_pSprite, m_tCenter.x + (cos(fAngle) * m_fRadius), m_tCenter.y + (sin(fAngle) * m_fRadius));
	}

}

void TCircle::Initialize()
{
	if (!m_bInitialized)
	{
		InitializeSprite();
		m_bInitialized = true;
	}
}

void TCircle::Update()
{
	Draw();
}

void TCircle::Render()
{
	GfxSpriteRender(m_pSprite);
}

void TCircle::Reset()
{
	GfxLineSpriteReset(m_pSprite);
}

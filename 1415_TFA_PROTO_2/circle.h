#ifndef	 CIRCLE_H_INCLUDED
#define  CIRCLE_H_INCLUDED


#include"flib_vec2.h"

struct TGfxSprite;

class TCircle 
{
	private : 

		unsigned int m_iColor;
		
		void InitializeSprite();
		void Draw();

	protected:

		TGfxVec2 m_tCenter;
		float m_fRadius;

	public:

		TCircle();
		TCircle(TGfxVec2 tCenter, float fRadius);

		inline TGfxVec2 GetCenter()
		{
			return m_tCenter;
		}

		inline float GetRadius()
		{
			return m_fRadius;
		}

		inline void SetColor(unsigned int iColor)
		{
			m_iColor = iColor;
		}

		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		void Reset();
		
};


#endif

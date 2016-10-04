#ifndef PLAYER_TARGET_H_INCLUDED
#define PLAYER_TARGET_H_INCLUDED

#include "circle.h"

class TPlayerTarget : public TCircle
{
	private:

		bool m_bGrabbed;

	public:

		TPlayerTarget();

		inline TGfxVec2 GetCenter() const 
		{
			return m_tCenter;
		}
		inline void SetCenter(TGfxVec2 tCenter)
		{
			m_tCenter = tCenter;
		}

		void Initialize();
		void Update(const TGfxVec2 &tMousePos, TPlayerTarget * tOtherTargets, const int iOtherTargetsnumber, int iTargetIndex);
		void Render();
};



#endif

#ifndef	MOVABLE_CIRCLE_H_INCLUDED
#define MOVABLE_CIRCLE_H_INCLUDED

#include "circle.h"

class TTime;

class TMovableCircle : public TCircle
{
	protected:

		TGfxVec2 m_tSpeed;
		TGfxVec2 m_tAcceleration;

	public:

		TMovableCircle();

		void MoveUpdate(const TTime &tTime);

};


#endif

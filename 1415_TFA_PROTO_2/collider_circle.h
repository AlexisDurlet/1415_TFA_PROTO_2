#ifndef COLLIDER_CIRCLE_H_INCLUDED
#define	COLLIDER_CIRCLE_H_INCLUDED

#include"movable _circle.h"

class TColliderCircle : public TMovableCircle
{
	public : 

		bool Collision(TCircle tCollidedCircle);
};


#endif

#ifndef INCLUDED_BE_TANK_BULLET_H_
#define INCLUDED_BE_TANK_BULLET_H_

#include "BERigidBlock.h"

class GeoSize;

class BETankBullet : public BERigidBlock
{
public:
	BETankBullet(const GeoSize &size) : BERigidBlock(size) {}
	virtual ~BETankBullet();

	virtual float getDamage() const = 0;
	virtual float getSpeed() const = 0;

	virtual void setDamage(float damage) = 0;
	virtual void setSpeed(float speed) = 0;
};

#endif
#ifndef INCLUDED_BE_TANK_H_
#define INCLUDED_BE_TANK_H_

#include "BERigidBlock.h"
#include <vector>
#include "BEToward.h"

class GeoSize;
class BEITankView;
class BEBlockBehavior;

class BETank : public BERigidBlock
{
public:
	BETank(const GeoSize &rect) : BERigidBlock(rect), m_movingSpeed(1.8f), m_toward(kBETowardRight) {}
	virtual ~BETank();

private:
	BETank(const BETank &tank);
	BETank &operator = (const BETank &tank);

public:
	float getMovingSpeed() const { return m_movingSpeed; }
	int getToward() const { return m_toward; }

	void addView(BEITankView *view) { m_views.push_back(view); }
	void removeBehavior();
	void removeView(BEITankView *view);
	void addBehavior(BEBlockBehavior *behavior);
	void setMovingSpeed(float movingSpeed) { m_movingSpeed = movingSpeed; }
	void setPosition(const GeoPoint &position);	
	void setToward(int toward);

private:
	float m_movingSpeed;
	int m_toward;
	std::vector<BEITankView *> m_views;	
};

#endif
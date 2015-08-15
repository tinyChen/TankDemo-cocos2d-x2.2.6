#ifndef INCLUDED_BE_TANK_STRAIGHT_BULLET_H_
#define INCLUDED_BE_TANK_STRAIGHT_BULLET_H_

#include "BETankBullet.h"
#include <vector>

class BEBlockMover;
class GeoSize;
class BEMapSceneGrid;
class BEIBulletView;
class BETank;

class BETankStraightBullet : public BETankBullet
{
public:
	BETankStraightBullet(const GeoSize &size, BETank *tank, float damage = 1, float speed = 3.0f);
	virtual ~BETankStraightBullet();

private:
	BETankStraightBullet(const BETankStraightBullet &bullet);
	BETankStraightBullet &operator = (const BETankStraightBullet &bullet);

public:
	void addView(BEIBulletView *view) { m_views.push_back(view); }
	float getDamage() const { return m_damage; }
	float getSpeed() const { return m_speed; }
	int getToward() const { return m_toward; }

	void removeView(BEIBulletView *view);
	void setDamage(float damage) { m_damage = damage; }
	void setPosition(const GeoPoint &position);

	void setSpeed(float speed) { m_speed = speed; }
	void setToward(int toward) { m_toward = toward; }

private:
	float m_damage;
	float m_speed;
	BETank *m_tank;
	int m_toward;
	std::vector<BEIBulletView *> m_views;
};

#endif
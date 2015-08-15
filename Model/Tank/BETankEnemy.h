#ifndef INCLUDED_BE_TANK_ENEMY_H_
#define INCLUDED_BE_TANK_ENEMY_H_

#include "BETank.h"

class BETankEnemy : public BETank
{
public:
	BETankEnemy(const GeoSize &size) : BETank(size) {}
	~BETankEnemy() {}

private:
	BETankEnemy(const BETankEnemy &tank);
	BETankEnemy &operator = (const BETankEnemy &tank);

public:
	int getHp() const { return m_hp; }

	int setHp(int hp) { m_hp = hp; }

private:
	int m_hp;
};

#endif
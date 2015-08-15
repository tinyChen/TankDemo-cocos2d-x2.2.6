#ifndef INCLUDED_BE_TANK_PLAYER_H_
#define INCLUDED_BE_TANK_PLAYER_H_

#include "BETank.h"

class BETankPlayer : public BETank
{
public:
	BETankPlayer(const GeoSize &size);
	~BETankPlayer() {}

private:
	BETankPlayer(const BETankPlayer &tank);
	BETankPlayer &operator = (const BETankPlayer &tank);

};

#endif
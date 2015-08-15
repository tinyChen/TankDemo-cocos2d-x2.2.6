#ifndef INCLUDED_BE_ITANK_VIEW_H_
#define INCLUDED_BE_ITANK_VIEW_H_

class GeoPoint;

class BEITankView
{
public:
	virtual ~BEITankView();

	virtual void onTankTowardChanged(int toward) {}
	virtual void onTankPositionChanged(const GeoPoint &pos) {}
};

#endif
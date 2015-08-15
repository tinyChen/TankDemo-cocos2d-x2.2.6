#ifndef INCLUDED_BE_BLOCK_H_
#define INCLUDED_BE_BLOCK_H_

class GeoPoint;
class GeoSize;
class GeoRect;

class BEBlock
{
public:	
	virtual ~BEBlock();

	//ACCESSORS
	virtual int getGridId() const = 0;
	virtual const GeoPoint &getPosition() const = 0;
	virtual const GeoSize &getSize() const = 0;
	virtual GeoRect getBoundingBox() const = 0;
	
	//MANIPULATORS
	virtual void setGridId(int gridId) = 0;
	virtual void setPosition(const GeoPoint &positioin) = 0;
	virtual void setSize(const GeoSize &rect) = 0;
	
};

#endif
#ifndef INCLUDED_BE_OBSTRUCTED_BLOCK_H_
#define INCLUDED_BE_OBSTRUCTED_BLOCK_H_

#include "BEBlock.h"
#include "GeoPoint.h"
#include "GeoSize.h" 

class BEObstructedBlock : public BEBlock
{
public:
	BEObstructedBlock(const GeoSize &rect) : m_size(rect), m_gridId(-1) {}
	BEObstructedBlock(const GeoPoint &position, const GeoSize &rect) : m_position(position), m_size(rect), m_gridId(-1) {}
	virtual ~BEObstructedBlock();

private:
	BEObstructedBlock(const BEObstructedBlock &block);
	BEObstructedBlock &operator = (const BEObstructedBlock &block);	

public:
	//ACCESSORS
	int getGridId() const { return m_gridId; }
	const GeoPoint &getPosition() const { return m_position; }
	const GeoSize &getSize() const { return m_size; }
	GeoRect getBoundingBox () const;

	//MANIPULATORS
	void setGridId(int gridId) { m_gridId = gridId; }
	virtual void setPosition(const GeoPoint &position) { m_position = position; }
	virtual void setSize(const GeoSize &rect) { m_size = rect; }

private:
	GeoPoint m_position;
	GeoSize m_size;
	int m_gridId;
};

#endif
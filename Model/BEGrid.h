#ifndef INCLUDED_BE_GRID_H_
#define INCLUDED_BE_GRID_H_

#include "GeoPoint.h"
#include "GeoSize.h"

class BEGrid
{
public:
	BEGrid(const GeoSize &rect) : m_rect(rect), m_data(nullptr) {}
	BEGrid(const GeoPoint &position, const GeoSize &rect) : m_position(position), m_rect(rect), m_data(nullptr) {}
	~BEGrid() {}

private:
	BEGrid(const BEGrid &block);
	BEGrid &operator = (const BEGrid &block);	

public:
	//ACCESSORS
	void *getData() const { return m_data; }
	const GeoPoint &getPosition() const { return m_position; }
	const GeoSize &getRect() const { return m_rect; }

	//MANIPULATORS
	void setData(void *object);
	void setPosition(const GeoPoint &position) { m_position = position; }
	void setRect(const GeoSize &rect) { m_rect = rect; }

private:
	void *m_data;
	GeoPoint m_position;
	GeoSize m_rect;	
};

#endif
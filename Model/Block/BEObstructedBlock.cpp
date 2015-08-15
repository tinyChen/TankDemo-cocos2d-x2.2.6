#include "BEObstructedBlock.h"
#include "GeoPoint.h"
#include "GeoRect.h"

BEObstructedBlock::~BEObstructedBlock()
{}

GeoRect BEObstructedBlock::getBoundingBox() const
{
	GeoRect rect;
	rect.setLeftTop(GeoPoint(m_position.x() - m_size.width() * 0.5f, m_position.y() + m_size.height() * 0.5f));
	rect.setRightBottom(GeoPoint(m_position.x() + m_size.width() * 0.5f, m_position.y() - m_size.height() * 0.5f));
	return rect;	
}
#include "BEMapSceneGrid.h"
#include <algorithm>
#include "BEGrid.h"
#include "GeoSize.h"
#include <assert.h>

static void initGrids(const GeoSize &rect, int row, int column, std::vector<BEGrid *> *grids)
{
	GeoSize gridRect(rect.width() / column, rect.height() / row);
	float width = 0;
	float height = 0;
	for (int i = 0; i < row; ++i)
	{
		width = gridRect.width() * 0.5f;
		height = rect.height() - i * gridRect.height() - gridRect.height() * 0.5f;
		for (int j = 0; j < column; ++j)
		{
			grids->push_back(new BEGrid(GeoPoint(width, height), gridRect));
			width += gridRect.width();
		}
	}
}

BEMapSceneGrid::BEMapSceneGrid(const GeoSize &rect, int row, int column) : m_rect(rect), m_row(row), m_column(column)
{
	initGrids(rect, row, column, &m_grids);
}

const BEGrid *BEMapSceneGrid::getGrid(int gridId) const
{
	if (isGridIdInRange(gridId))
	{
		return m_grids[gridId];
	}else
	{
		assert(false && "illegal grid id");
		return nullptr;
	}
}

const GeoPoint &BEMapSceneGrid::getGridPosition(int gridId) const
{
	return getGrid(gridId)->getPosition();
}

void *BEMapSceneGrid::getGridData(int gridId) const
{
	if (isGridIdInRange(gridId))
	{
		return m_grids[gridId]->getData();
	}else
	{
		assert(false && "illegal grid id");
		return nullptr;
	}
}

const GeoSize &BEMapSceneGrid::getGridSize() const
{
	static GeoSize size;
	size.setWidth(m_rect.width() / m_column);
	size.setHeight(m_rect.height()/ m_row);

	return size;
}

void BEMapSceneGrid::removeData(int gridId)
{
	if (isGridIdInRange(gridId))
	{
		m_grids[gridId]->setData(nullptr);
	}else
	{
		assert(false && "illegal gridId");
	}
}

void BEMapSceneGrid::setData(int gridId, void *object)
{
	if (isGridIdInRange(gridId))
	{
		m_grids[gridId]->setData(object);
	}else
	{
		assert(false && "illegal gridId");
	}
}

void BEMapSceneGrid::visitEveryGrid(std::function<void (int gridId)> ftn)
{
	for (size_t i = 0; i < m_grids.size(); ++i)
	{
		ftn(i);
	}
}
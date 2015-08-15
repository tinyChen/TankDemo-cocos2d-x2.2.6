#include "BEGridUtil.h"
#include "BEMapSceneGrid.h"
#include "GeoPoint.h"
#include "GeoSize.h"
#include "BEToward.h"
#include "BEBlock.h"
#include <cassert>
#include <algorithm>

int BEGridUtil::getGridIdByPosition(const BEMapSceneGrid *sceneGrid, const GeoPoint &position)
{
	//此函数要求BESceneGrid和position在同一个坐标系
	const GeoSize &size = sceneGrid->getRect();
	if (position.x() > size.width() || position.y() > size.height())
	{
		return -1;
	}

	const GeoSize &gridSize = sceneGrid->getGridSize();
	int row = (size.height() - position.y()) / gridSize.height();
	int column = position.x() / gridSize.width();
	
	return row * sceneGrid->getColumn() + column;
}

int BEGridUtil::getGridIdByBlock(const BEMapSceneGrid *sceneGrid, BEBlock *block, int toward)
{
	GeoSize size = block->getSize();
	GeoPoint glPosition = block->getPosition();
	float validArea = size.width() * 0;
	switch (toward)
	{
	case kBETowardLeft:
		glPosition.setX(glPosition.x() - validArea);
		break;
	case kBETowardUp:
		glPosition.setY(glPosition.y() + validArea);
		break;
	case kBETowardRight:
		glPosition.setX(glPosition.x() + validArea);
		break;
	case kBETowardDown:
		glPosition.setY(glPosition.y() - validArea);
		break;
	default:
		assert(false && "illegal toward");
	}
	return getGridIdByPosition(sceneGrid, glPosition);
}

const GeoSize &BEGridUtil::convertGridIdToRowColumn(int gridId, int column)
{
	static GeoSize rc;
	rc.setHeight(gridId / column);
	rc.setWidth(gridId % column);
	return rc;
}

const std::vector<int> &BEGridUtil::getGridScopeByStep(const BEMapSceneGrid *sceneGrid, int curGridId, int toward, int step)
{
	static std::vector<int> s_gridScope;
	s_gridScope.clear();

	int minGridId = -1;
	int maxGridId = -1;
	int interval = 1;
	int maxColumn = sceneGrid->getColumn();
	int maxRow = sceneGrid->getRow();
	int rowScope = curGridId / maxColumn;
	int columnScope = curGridId % maxColumn;
	
	switch (toward)
	{
	case kBETowardLeft:
		if (step > columnScope) step = columnScope;		
		minGridId = curGridId - step;
		maxGridId = curGridId - 1;
		break;
	case kBETowardUp:
		if (step > rowScope) step = rowScope;
		minGridId = curGridId - step * maxColumn;
		maxGridId = curGridId - maxColumn;
		interval = maxColumn;
		break;
	case kBETowardRight:
		{
			int c = maxColumn - columnScope - 1;
			if (step > c) step = c;		
			minGridId = curGridId + 1;
			maxGridId = curGridId + step;
			break;
		}
	case kBETowardDown:
		{
			int r = maxRow - rowScope - 1;
			if (step > r) step = r;
			minGridId = curGridId + maxColumn;
			maxGridId = curGridId + step * maxColumn;
			interval = maxColumn;
			break;
		}
	default:
		assert(false && "illegal toward");
	}

	for (int i = minGridId; i <= maxGridId; i += interval)
	{
		s_gridScope.push_back(i);
	}
	return s_gridScope;
}

const std::vector<int> &BEGridUtil::getFrontGridIds(const BEMapSceneGrid *sceneGrid, int curGridId, int curToward, int scope)
{
	static std::vector<int> s_gridIds;
	s_gridIds.clear();

	int left = curToward - 1;
	if (left < 0) left = kBETowardCount - 1;
	int right = curToward + 1;
	if (right >= kBETowardCount) right = kBETowardLeft;
	int towardArray[] = { left, curToward, right};
	int nextGridIds[3] = {-1, -1, -1};
	nextGridIds[0] = getNextGridIdByToward(sceneGrid, curGridId, left);
	nextGridIds[1] = getNextGridIdByToward(sceneGrid, curGridId, right);
	nextGridIds[2] = curGridId;
	for (int i = 0; i < 3; ++i)
	{
		if (sceneGrid->isGridIdInRange(nextGridIds[i]))
		{
			std::vector<int> scopeGridIds = getGridScopeByStep(sceneGrid, nextGridIds[i], curToward, scope);
			s_gridIds.insert(s_gridIds.end(), scopeGridIds.begin(), scopeGridIds.end());
		}
	}

	return s_gridIds;
}

int BEGridUtil::getNextGridIdByToward(const BEMapSceneGrid *sceneGrid, int curGridId, int toward)
{
	int column = sceneGrid->getColumn();
	const GeoSize &rc = BEGridUtil::convertGridIdToRowColumn(curGridId, column);

	switch (toward)
	{
	case kBETowardLeft:
		curGridId = rc.width() <= 0 ? -1 : curGridId - 1;
		break;
	case kBETowardUp:
		curGridId -= column;
		break;
	case kBETowardRight:
		curGridId = rc.width() >= column - 1 ? -1 : curGridId + 1;			
		break;
	case kBETowardDown:
		curGridId += column;
		break;
	default:
		assert(false);
	}
	return curGridId;
}
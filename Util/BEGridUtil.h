#ifndef INCLUDED_BE_GRID_UTIL_H_
#define INCLUDED_BE_GRID_UTIL_H_

#include <vector>

class BEMapSceneGrid;
class GeoPoint;
class GeoSize;
class BEBlock;

struct BEGridUtil
{
	static int getGridIdByPosition(const BEMapSceneGrid *sceneGrid, const GeoPoint &position);
	static int getGridIdByBlock(const BEMapSceneGrid *sceneGrid, BEBlock *block, int toward);
	static const GeoSize &convertGridIdToRowColumn(int gridId, int column);
	static const std::vector<int> &getGridScopeByStep(const BEMapSceneGrid *sceneGrid, int curGridId, int toward, int hatredScope);
	static const std::vector<int> &getFrontGridIds(const BEMapSceneGrid *sceneGrid, int curGridId, int curToward, int scope);
	static int getNextGridIdByToward(const BEMapSceneGrid *sceneGrid, int curGridId, int toward);
};

#endif
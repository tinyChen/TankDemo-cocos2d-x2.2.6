#ifndef INCLUDED_BE_MAP_SCENE_GRID_H_
#define INCLUDED_BE_MAP_SCENE_GRID_H_

#include "GeoSize.h"
#include "GeoPoint.h"
#include <vector>
#include <functional>

class BEGrid;

class BEMapSceneGrid
{
public:
	BEMapSceneGrid(const GeoSize &rect, int row, int column);
	~BEMapSceneGrid() {}

private:
	BEMapSceneGrid(const BEMapSceneGrid &sceneGrid);
	BEMapSceneGrid &operator = (const BEMapSceneGrid &sceneGrid);

public:
	//ACCESSORS
	int getColumn() const { return m_column; }
	void *getGridData(int gridId) const;
	const BEGrid *getGrid(int gridId) const;
	const GeoPoint &getGridPosition(int gridId) const;
	const std::vector<BEGrid *> &getGrids() const { return m_grids; }
	const GeoSize &getGridSize() const;
	const GeoSize &getRect() const { return m_rect; }
	int getRow() const { return m_row; }
	bool isGridIdInRange(int gridId) const { return (gridId < static_cast<int>(m_grids.size()) && gridId >= 0); }

	//MANIPULATORS
	void removeData(int gridId);	
	void setColumn(int column) { m_column = column; }
	void setData(int gridId, void *object);
	void setRect(const GeoSize &rect) { m_rect = rect; }
	void setRow(int row) { m_row = row; }
	void visitEveryGrid(std::function<void (int gridId)> ftn);

private:
	GeoSize m_rect;
	int m_row;
	int m_column;
	std::vector<BEGrid *> m_grids;
};

#endif
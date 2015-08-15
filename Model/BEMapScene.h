#ifndef INCLUDED_BE_MAP_SCENE_H_
#define INCLUDED_BE_MAP_SCENE_H_

#include <vector>
#include "BEMapSceneGrid.h"

class BEBlock;
class GeoSize;
class BEIMapSceneView;
class BETank;
class BETankBullet;

class BEMapScene
{
public:
	BEMapScene(const GeoSize &rect, int row, int column);
	~BEMapScene();

private:
	BEMapScene(const BEMapScene &scene);
	BEMapScene &operator = (const BEMapScene &scene);

public:
	//ACCESSORS
	int getColumn() const { return m_sceneGrid.getColumn(); }
	const BEGrid *getGrid(int gridId) const { return m_sceneGrid.getGrid(gridId); }
	const GeoSize &getRect() const { return m_sceneGrid.getRect(); }
	int getRow() const { return m_sceneGrid.getRow(); }
	BEMapSceneGrid *getMapSceneGrid() { return &m_sceneGrid; }
	bool hasBlock(int blockId) const;

	//MANIPULATORS
	void addBlock(int blockId, int blockType);
	void addBullet(int blockId, BETank *tank, const GeoSize &size);
	void addPlayerTank(int blockId);
	void addView(BEIMapSceneView *view) { m_sceneViews.push_back(view); }
	void addEnemyTank(int blockId);
	void removeBlock(int blockId);
	void removeBullet(BETankBullet *bullet);
	void removeTank(BETank *tank);
	void removeView(BEIMapSceneView *view);
	void setColumn(int column) { m_sceneGrid.setColumn(column); }
	void setRect(const GeoSize &rect) { m_sceneGrid.setRect(rect); }
	void setRow(int row) { m_sceneGrid.setRow(row); }
	void updateScene(float dt);

private:	
	std::vector<BEIMapSceneView *> m_sceneViews;
	BEMapSceneGrid m_sceneGrid;
	std::vector<BETank *> m_tanks;
	std::vector<BETankBullet *> m_bullets;
};

#endif
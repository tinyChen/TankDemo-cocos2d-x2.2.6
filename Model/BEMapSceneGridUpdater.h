#ifndef INCLUDED_BE_MAP_SCENE_GRID_UPDATER_H_
#define INCLUDED_BE_MAP_SCENE_GRID_UPDATER_H_

class BEMapSceneGrid;
class BEBlock;

class BEMapSceneGridUpdater
{
public:
	static BEMapSceneGridUpdater *theUpdater() { static BEMapSceneGridUpdater *updater = new BEMapSceneGridUpdater(); return updater; }

private:
	BEMapSceneGridUpdater() : m_sceneGrid(nullptr) {}
	~BEMapSceneGridUpdater() {}

public:
	void updateSceneGridData(BEBlock *block);
	void setMapSceneGrid(BEMapSceneGrid *sceneGrid) { m_sceneGrid = sceneGrid; }

private:
	BEMapSceneGrid *m_sceneGrid;
};

#endif
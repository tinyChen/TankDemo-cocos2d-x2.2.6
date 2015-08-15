#ifndef INCLUDED_BE_TANK_PATH_FINDER_H_
#define INCLUDED_BE_TANK_PATH_FINDER_H_

class BEMapSceneGrid;
class BETank;

class BETankPathFinder
{
public:
	BETankPathFinder(BETank *tank, BEMapSceneGrid *sceneGrid) : m_sceneGrid(sceneGrid), m_tank(tank) {}
	~BETankPathFinder() {}

private:
	BETankPathFinder(const BETankPathFinder &finder);
	BETankPathFinder &operator = (const BETankPathFinder &finder);

public:
	void update(int *targetGridId, int *targetToward);

private:
	BEMapSceneGrid *m_sceneGrid;
	BETank *m_tank;	
};

#endif
#ifndef INCLUDED_BE_BLOCK_COLLISION_DECTECTOR_H_
#define INCLUDED_BE_BLOCK_COLLISION_DECTECTOR_H_

#include <unordered_map>
#include <functional>

class BEMapSceneGrid;
class BEBlock;


class BEBlockCollisionDectector
{
public:
	static BEBlockCollisionDectector *theDectector() { static BEBlockCollisionDectector *dectector = new BEBlockCollisionDectector; return dectector; }
	BEBlockCollisionDectector() : m_sceneGrid(nullptr) {}
	~BEBlockCollisionDectector() {}

public:
	void addBlock(BEBlock *block, std::function<void (BEBlock *, BEBlock *)> ftn);
	void removeBlock(BEBlock *block);
	void setMapSceneGrid(BEMapSceneGrid *sceneGrid) { m_sceneGrid = sceneGrid; }
	void update(float dt);

private:
	BEMapSceneGrid *m_sceneGrid;
	std::unordered_map<BEBlock *, std::function<void (BEBlock *, BEBlock *)> > m_blocks;
};

#endif
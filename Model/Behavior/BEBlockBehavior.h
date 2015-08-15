#ifndef INCLUDED_BE_BLOCK_BEHAVIOR_H_
#define INCLUDED_BE_BLOCK_BEHAVIOR_H_

class BEBlock;
class BEMapSceneGrid;

class BEBlockBehavior
{
public:
	BEBlockBehavior(BEMapSceneGrid *sceneGrid);
	virtual ~BEBlockBehavior();

private:
	BEBlockBehavior(const BEBlockBehavior &behavior);
	BEBlockBehavior &operator = (const BEBlockBehavior &behavior);

public:
	BEBlock *getBlock() const { return m_block; }
	float getInterval() const { return m_interval; }
	BEMapSceneGrid *getMapSceneGrid() const { return m_mapSceneGrid; }

	virtual void setBlock(BEBlock *block) { m_block = block; }
	void setInterval(float interval) { m_interval = interval; }	
	virtual void updateBehavior(float dt) = 0;

private:
	BEBlock *m_block;
	BEMapSceneGrid *m_mapSceneGrid;
	float m_interval;
};

#endif
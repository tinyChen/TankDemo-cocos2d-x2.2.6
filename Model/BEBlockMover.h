#ifndef INCLUDED_BE_BLOCK_MOVER_H_
#define INCLUDED_BE_BLOCK_MOVER_H_

#include <functional>

class BEBlock;
class BEMapSceneGrid;

class BEBlockMover
{
public:
	BEBlockMover(BEBlock *block, BEMapSceneGrid *sceneGrid)
		: m_block(block), m_targetGridId(-1), m_sceneGrid(sceneGrid), 
		m_callbackFtn(nullptr), m_timeCount(0.0f), m_movingSpeed(0.0f), m_targetToward(-1) {}
	~BEBlockMover() {}

private:
	BEBlockMover(const BEBlockMover &mover);
	BEBlockMover &operator = (const BEBlockMover &mover);

public:
	float getMovingSpeed() const { return m_movingSpeed; }

	void update(float dt);
	void setMovingSpeed(float movingSpeed) { m_movingSpeed = movingSpeed; }
	void setTankReachDestinationCallback(std::function<void (BEBlock *)> ftn) { m_callbackFtn = ftn; }
	void setTargetGridId(int gridId) { m_targetGridId = gridId; }
	void setTargetToward(int toward);


private:
	BEBlock *m_block;
	int m_targetGridId;
	int m_targetToward;
	float m_movingSpeed;
	BEMapSceneGrid *m_sceneGrid;
	std::function<void (BEBlock *)> m_callbackFtn;
	float m_timeCount;
};

#endif
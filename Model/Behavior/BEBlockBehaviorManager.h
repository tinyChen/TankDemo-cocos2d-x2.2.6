#ifndef INCLUDED_BE_BLOCK_BEHAVIOR_MANAGER_H_
#define INCLUDED_BE_BLOCK_BEHAVIOR_MANAGER_H_

#include <vector>
#include "DsList.h"

class BEBlockBehavior;
class BEBlock;

class BEBlockBehaviorManager
{
public:
	static BEBlockBehaviorManager *theMgr() { static BEBlockBehaviorManager *mgr = new BEBlockBehaviorManager(); return mgr; }

private:
	BEBlockBehaviorManager() {}
	~BEBlockBehaviorManager() {}

public:
	void addBehavior(BEBlockBehavior *behavior, BEBlock *target);
	void removeBehavior(BEBlock *block);
	void update(float dt);

private:
	DsList m_list;
};

#endif
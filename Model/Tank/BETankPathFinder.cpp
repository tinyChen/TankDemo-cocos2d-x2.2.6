#include "BETankPathFinder.h"
#include "BEGrid.h"
#include <vector>
#include "BEToward.h"
#include "BEMapSceneGrid.h"
#include "BETank.h"
#include "BEGridUtil.h"
#include <unordered_map>
#include <assert.h>
#include "BEUnobstructedBlock.h"
#include "LogUtil.h"
#include <math.h>


static int getReversedToward(int toward)
{	
	switch (toward)
	{
	case kBETowardLeft:
		return toward + kBETowardCount / 2; 
	case kBETowardUp:
		return toward + kBETowardCount / 2; 
		break;
	case kBETowardRight:
		return toward - kBETowardCount / 2; 
		break;
	case kBETowardDown:
		return toward - kBETowardCount / 2; 
		break;
	default:
		assert(false && "illegal toward");
	}
	return toward;
}

static void initTowardFlag(std::unordered_map<int, bool> *towardFlag)
{
	towardFlag->clear();
	for (int i = kBETowardLeft; i <= kBETowardDown; ++i)
	{
		towardFlag->insert(std::make_pair(i, false));
	}
}

static int findTowardByClockwise(std::unordered_map<int, bool> towardFlag, int curToward)
{
	int towardIndex = curToward;	
	for (int i = 0; i < kBETowardCount - 1; ++i)
	{
		++towardIndex;
		if (towardIndex >= kBETowardCount) towardIndex = 0;
		if (!towardFlag[towardIndex])
		{
			return towardIndex;
		}		
	}
	return -1;
}

static int findTowardRandomly(const std::unordered_map<int, bool> &towardFlag)
{
	return rand() % kBETowardCount;
}

static int findTowardForwadRandomly(std::unordered_map<int, bool> towardFlag, int curToward)
{
	int left = curToward - 1;
	if (left < 0) left = kBETowardCount - 1;
	int right = curToward + 1;
	if (right >= kBETowardCount) right = 0;
	int towardArray[] = { left, curToward, right};
	if (towardFlag[left] && towardFlag[curToward] && towardFlag[right])
	{
		return getReversedToward(curToward);
	}
	int randNum = rand() % 100 + 1;
	if (randNum >= 1 && randNum < 20)
	{
		return towardArray[0];
	}else if (randNum >= 20 && randNum < 80)
	{
		return towardArray[1];
	}else if (randNum >= 80 && randNum <= 100)
	{
		return towardArray[2];
	}
	return -1;
}

static int findToward(const std::unordered_map<int, bool> &towardFlag, int curToward)
{	
	return findTowardForwadRandomly(towardFlag, curToward);
}

static bool isAllTowardFound(const std::unordered_map<int, bool> &towardFlag)
{
	for (auto iter = towardFlag.begin(); iter != towardFlag.end(); ++iter)
	{
		if (!iter->second)
		{
			return false;
		}
	}
	return true;
}


static void getGridIdOnPath(BEMapSceneGrid *sceneGrid, BETank *tank, int *targetGridId, int *targetToward)
{
	*targetGridId = -1;
	*targetToward = -1;

	int toward = tank->getToward();
	std::unordered_map<int, bool> towardFlag;
	initTowardFlag(&towardFlag);

	toward = findToward(towardFlag, tank->getToward());
	do 
	{			
		int gridId = BEGridUtil::getNextGridIdByToward(sceneGrid, tank->getGridId(), toward);
		//LogUtil::log("toward = %d, gridId = %d", toward, gridId);
		towardFlag[toward] = true;
		if (sceneGrid->isGridIdInRange(gridId))
		{						
			BEBlock *block = (BEBlock *)(sceneGrid->getGridData(gridId));
			if (block == nullptr || dynamic_cast<BEUnobstructedBlock *>(block))
			{
				*targetGridId = gridId;
				*targetToward = toward;
				break;
			}
		}
		if (isAllTowardFound(towardFlag))
		{
			break;
		}

	} while ((toward = findToward(towardFlag, tank->getToward())) >= 0);
}

void BETankPathFinder::update(int *targetGridId, int *targetToward)
{
	getGridIdOnPath(m_sceneGrid, m_tank, targetGridId, targetToward);
}
#ifndef INCLUDED_BE_BLOCK_UTIL_H_
#define INCLUDED_BE_BLOCK_UTIL_H_

class BEBlock;
class BEBlockView;
class GeoSize;
class BEMapSceneGrid;
class GeoPoint;

struct BEBlockUtil
{
	static BEBlock *createBlock(int blockType, const GeoSize &rect);
	static BEBlock *createBlock(int blockType, int blockId, BEMapSceneGrid *sceneGrid, const GeoSize &size);
	static BEBlockView *createBlockView(int blockType, BEBlock *block);
	static void setBlockPositionByToward(BEBlock *block, float movingSpeed, int toward);
	static const GeoPoint &getBlockPositionByOffset(const GeoPoint &position, float offest, int toward);
};

#endif
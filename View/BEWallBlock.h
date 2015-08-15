#ifndef INCLUDED_BE_WALL_BLOCK_H_
#define INCLUDED_BE_WALL_BLOCK_H_

#include "BEBlockView.h"

class BEWallBlock : public BEBlockView
{
public:
	static BEWallBlock *create(BEBlock *block);

private:
	BEWallBlock(BEBlock *block);
	~BEWallBlock();

	bool init();
};

#endif
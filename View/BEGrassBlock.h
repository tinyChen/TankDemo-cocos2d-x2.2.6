#ifndef INCLUDED_BE_GRASS_BLOCK_H_
#define INCLUDED_BE_GRASS_BLOCK_H_

#include "BEBlockView.h"

class BEGrassBlock : public BEBlockView
{
public:
	static BEGrassBlock *create(BEBlock *block);

private:
	BEGrassBlock(BEBlock *block);
	~BEGrassBlock();

	bool init();
};

#endif
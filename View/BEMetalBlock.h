#ifndef INCLUDED_BE_METAL_BLOCK_H_
#define INCLUDED_BE_METAL_BLOCK_H_

#include "BEBlockView.h"

class BEMetalBlock : public BEBlockView
{
public:
	static BEMetalBlock *create(BEBlock *block);

private:
	BEMetalBlock(BEBlock *block);
	~BEMetalBlock();

	bool init();
};

#endif
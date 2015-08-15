#ifndef INCLUDED_BE_FRIABLE_BLOCK_H_
#define INCLUDED_BE_FRIABLE_BLOCK_H_

#include "BEObstructedBlock.h"

class BEFriableBlock : public BEObstructedBlock
{
public:
	BEFriableBlock(const GeoSize &rect) : BEObstructedBlock(rect) {}
	virtual ~BEFriableBlock();	
};

#endif
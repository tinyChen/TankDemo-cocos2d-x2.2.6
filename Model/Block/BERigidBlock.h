#ifndef INCLUDED_BE_RIGID_BLOCK_H_
#define INCLUDED_BE_RIGID_BLOCK_H_

#include "BEObstructedBlock.h"

class BERigidBlock : public BEObstructedBlock
{
public:
	BERigidBlock(const GeoSize &rect) : BEObstructedBlock(rect) {}
	virtual ~BERigidBlock();
};

#endif
#ifndef INCLUDED_BE_BLOCK_VIEW_H_
#define INCLUDED_BE_BLOCK_VIEW_H_

#include "cocos2d.h"

class BEBlock;

class BEBlockView : public cocos2d::CCNode
{
public:
	BEBlockView(BEBlock *block);
	virtual ~BEBlockView();

public:
	BEBlock *getBlock() const { return m_block; }

private:
	BEBlock *m_block;
};
#endif
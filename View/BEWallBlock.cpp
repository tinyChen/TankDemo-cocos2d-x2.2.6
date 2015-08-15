#include "BEWallBlock.h"

USING_NS_CC;

BEWallBlock::BEWallBlock(BEBlock *block) : BEBlockView(block)
{

}

BEWallBlock::~BEWallBlock()
{

}

bool BEWallBlock::init()
{
	const CCSize &size = getContentSize();
	CCLayerColor *layerColor = CCLayerColor::create(ccc4(162, 81, 0, 255));
	layerColor->setContentSize(getContentSize());
	layerColor->ignoreAnchorPointForPosition(false);
	layerColor->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(layerColor);

	return true;
}

BEWallBlock *BEWallBlock::create(BEBlock *block)
{
	BEWallBlock *metalBlock = new BEWallBlock(block);
	metalBlock->autorelease();
	metalBlock->init();
	return metalBlock;
}
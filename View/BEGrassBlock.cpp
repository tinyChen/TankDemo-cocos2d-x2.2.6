#include "BEGrassBlock.h"

USING_NS_CC;

BEGrassBlock::BEGrassBlock(BEBlock *block) : BEBlockView(block)
{

}

BEGrassBlock::~BEGrassBlock()
{

}

bool BEGrassBlock::init()
{
	const CCSize &size = getContentSize();
	CCLayerColor *layerColor = CCLayerColor::create(ccc4(0, 255, 0, 100));
	layerColor->setContentSize(getContentSize());
	layerColor->ignoreAnchorPointForPosition(false);
	layerColor->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(layerColor);

	return true;
}

BEGrassBlock *BEGrassBlock::create(BEBlock *block)
{
	BEGrassBlock *grassBlock = new BEGrassBlock(block);
	grassBlock->autorelease();
	grassBlock->init();
	return grassBlock;
}
#include "BEMetalBlock.h"

USING_NS_CC;

BEMetalBlock::BEMetalBlock(BEBlock *block) : BEBlockView(block)
{

}

BEMetalBlock::~BEMetalBlock()
{

}

bool BEMetalBlock::init()
{
	const CCSize &size = getContentSize();
	CCLayerColor *layerColor = CCLayerColor::create(ccc4(245, 245, 255, 200));
	layerColor->setContentSize(getContentSize());
	layerColor->ignoreAnchorPointForPosition(false);
	layerColor->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(layerColor);

	return true;
}

BEMetalBlock *BEMetalBlock::create(BEBlock *block)
{
	BEMetalBlock *metalBlock = new BEMetalBlock(block);
	metalBlock->autorelease();
	metalBlock->init();
	return metalBlock;
}
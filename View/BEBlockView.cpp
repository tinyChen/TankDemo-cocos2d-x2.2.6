#include "BEBlockView.h"
#include "BEBlock.h"
#include "GeoSize.h"

USING_NS_CC;

BEBlockView::BEBlockView(BEBlock *block) : m_block(block)
{
	const GeoSize &size = block->getSize();
	setContentSize(CCSize(size.width(), size.height()));
}

BEBlockView::~BEBlockView()
{

}

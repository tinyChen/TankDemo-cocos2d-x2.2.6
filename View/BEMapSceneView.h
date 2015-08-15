#ifndef INCLUDED_BE_MAP_SCENE_VIEW_H_
#define INCLUDED_BE_MAP_SCENE_VIEW_H_

#include "cocos2d.h"
#include "BEIMapSceneView.h"
#include <vector>

class BEMapScene;
class BEBlock;
class BEBlockView;

class BEMapSceneView : public BEIMapSceneView, public cocos2d::CCNode
{
public:
	static BEMapSceneView *create(BEMapScene *scene);

private:
	BEMapSceneView(BEMapScene *scene);
	~BEMapSceneView();

	//MANIPULATORS
	bool init();

private:
	void onBlockAdded(BEBlock *block, int blockType);
	void onBlockRemoved(BEBlock *block);

private:
	BEMapScene *m_mapScene;
	std::vector<BEBlockView *> m_blockViews;
};

#endif
#ifndef INCLUDED_BE_I_MAP_SCENE_VIEW_H_
#define INCLUDED_BE_I_MAP_SCENE_VIEW_H_

class BEBlock;

class BEIMapSceneView
{
public:
	virtual ~BEIMapSceneView();
	virtual void onBlockAdded(BEBlock *block, int blockType) {}
	virtual void onBlockRemoved(BEBlock *block) {}
};

#endif
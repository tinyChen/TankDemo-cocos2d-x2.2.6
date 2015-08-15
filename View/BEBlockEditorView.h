#ifndef INCLUDED_BE_BLOCK_EDITOR_VIEW_H_
#define INCLUDED_BE_BLOCK_EDITOR_VIEW_H_

#include "cocos2d.h"

class BEMapScene;

class BEBlockEditorView : public cocos2d::CCLayer
{
public:
	BEBlockEditorView(BEMapScene *mapScene);
	~BEBlockEditorView();

	static cocos2d::CCScene* theScene();
	static BEBlockEditorView *create(BEMapScene *scene);

private:
	BEBlockEditorView(const BEBlockEditorView &view);
	BEBlockEditorView &operator = (const BEBlockEditorView &view);

	//MANIPULATORS
	bool init();
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void onEnter();
	void onExit();
	void update(float delta);

private:
	BEMapScene *m_mapScene;
};

#endif
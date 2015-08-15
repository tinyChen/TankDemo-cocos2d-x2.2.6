#ifndef INCLUDED_BE_BLOCK_CREATOR_H_
#define INCLUDED_BE_BLOCK_CREATOR_H_

class BEBlock;
class BETankBullet;
class BEMapScene;
class GeoSize;
class BETank;
class BEMapSceneGrid;

class BEMapSceneUtil
{
public:
	static void addBlock(int blockId, int blockType);
	static void addBullet(int blockId, BETank *tank, const GeoSize &size);
	static void addPlayerTank(int blockId);
	static void addEnemyTank(int blockId);
	static BEMapScene *getMapScene() { return s_mapScene; }
	static BEMapSceneGrid *getMapSceneGrid();
	static void removeBullet(BETankBullet *bullet);
	static void removeTank(BETank *tank);
	static void removeBlock(int blockId);
	static void setMapScene(BEMapScene *mapScene) { s_mapScene = mapScene; }
	
private:
	static BEMapScene *s_mapScene;	
};

#endif
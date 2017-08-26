#pragma once
#include "gameNode.h"

class block;
class unitManager;

struct PICKAX
{
	image* img;
	int x, y;
};

class pickax : public gameNode
{
private:
	PICKAX _pick;
	int _pickCnt;
	int _pickFrameCnt;
	bool _isSwing;
	bool _isGround;

	int _currentX;
	int _currentY;

	block* _block;
	unitManager* _um;

public:
	pickax();
	~pickax();

	HRESULT init(int pickCnt);
	void release();
	void update(bool isMaou, bool dialEnd);
	void render();

	void pickaxMove();
	void pickaxAttack();
	void pickFrameUpdate();

	int getPickCnt() { return _pickCnt; }
	int getPickX() { return _pick.x; }
	int getPickY() { return _pick.y; }
	int getPickI() { return _currentX; }
	int getPickJ() { return _currentY; }
	bool getIsGround() { return _isGround; }

	void setPickX(int x) { _currentY = x; }
	void setPickY(int y) { _currentX = y; }

	void setBlockMemoryLink(block* block) { _block = block; }
	void setunitManagerMemoryLink(unitManager* unitManagerLink) { _um = unitManagerLink; }

};


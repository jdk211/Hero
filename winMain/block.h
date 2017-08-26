#pragma once
#include "gameNode.h"

enum BLOCKSTATE
{
	BLOCK_IDLE1,
	BLOCK_IDLE2,
	BLOCK_SLIME1_1,
	BLOCK_SLIME1_2,
	BLOCK_SLIME2_1,
	BLOCK_SLIME2_2,
	BLOCK_BUG1_1,
	BLOCK_BUG1_2,
	BLOCK_BUG2_1,
	BLOCK_BUG2_2,
	BLOCK_TURTLE1,
	BLOCK_TURTLE2,
	BLOCK_EVIL1,
	BLOCK_EVIL2,
	BLOCK_SOUL1_1,
	BLOCK_SOUL1_2,
	BLOCK_SOUL2_1,
	BLOCK_SOUL2_2,
	BLOCK_WITCH1,
	BLOCK_WITCH2,
	BLOCK_UNKNOWN,
	UNDERGROUND
};

struct BLOCK
{
	int x, y;		//위치
	int cnt;		//블럭이 가진 몬스터 카운트
	int floor;		//블럭 층
	int idleCnt;	//두종류의 기본 블럭모양
	image* img;		//이미지
	image* shadow;	//그림자
	RECT rc;		//렉트
	BLOCKSTATE state;//상태

	bool left;
	bool right;
	bool up;
	bool down;
};

class block : public gameNode
{
private:
	BLOCK _block[BLOCK_MAX_Y][BLOCK_MAX_X]; // 0번째 줄에 61블럭

public:
	block();
	~block();

	HRESULT init();
	void release();
	void update();
	void render();

	int getBlockX(int i, int j) { return _block[i][j].x; }
	int getBlockY(int i, int j) { return _block[i][j].y; }
	int getCBlockX(int i, int j) { return (_block[i][j].rc.left + _block[i][j].rc.right) / 2; }
	int getCBlockY(int i, int j) { return (_block[i][j].rc.top + _block[i][j].rc.bottom) / 2; }
	int getBlockFloor(int i, int j) { return _block[i][j].floor; }
	int getBlockCnt(int i, int j) { return _block[i][j].cnt; }
	bool getBlockLeft(int i, int j) { return _block[i][j].left; }
	bool getBlockRight(int i, int j) { return _block[i][j].right; }
	bool getBlockUp(int i, int j) { return _block[i][j].up; }
	bool getBlockDown(int i, int j) { return _block[i][j].down; }
	BLOCKSTATE getBlockState(int i, int j) { return _block[i][j].state; }
	RECT getBlockRc(int i, int j) { return _block[i][j].rc; }

	void setBlockLeft(int i, int j, bool state) { _block[i][j].left = state; }
	void setBlockRight(int i, int j, bool state) { _block[i][j].right = state; }
	void setBlockUp(int i, int j, bool state) { _block[i][j].up = state; }
	void setBlockDown(int i, int j, bool state) { _block[i][j].down = state; }
	void setBlockStateUnder(int i, int j) { _block[i][j].state = UNDERGROUND; _block[i][j].img = NULL; }

};


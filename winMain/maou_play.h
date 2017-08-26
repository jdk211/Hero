#pragma once
#include "gameNode.h"

enum MAOUSTATE
{
	MAOU_IDLE,
	MAOU_MOVE,
	MAOU_ARREST
};

struct PLAYMAOU
{
	int x, y;
	image* img;
	animation* ani;
	MAOUSTATE state;
	MAOUSTATE beforeState;
};

class maou_play : public gameNode
{
private:
	PLAYMAOU _maou;

public:
	maou_play();
	~maou_play();

	HRESULT init(int state);
	void release();
	void update();
	void render();

	MAOUSTATE getMaouState() { return _maou.state; }
	int getMaouX() { return _maou.x; }
	int getMaouY() { return _maou.y; }

	void setMaouXY(int x, int y) { _maou.x = x; _maou.y = y; }
	void setMaouState(MAOUSTATE state) { _maou.state = state; }
};


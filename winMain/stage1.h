#pragma once
#include "gameNode.h"
#include "playScene.h"
#include "king.h"
#include "princess.h"
#include "flag.h"

class stage1 : public gameNode
{
private:
	playScene* _play;
	king* _king;
	princess* _princess;
	flag* _flag;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();
};


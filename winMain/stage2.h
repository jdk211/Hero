#pragma once
#include "gameNode.h"
#include "playScene.h"
#include "king.h"
#include "princess.h"
#include "flag.h"

class stage2 : public gameNode
{
	playScene* _play;
	king* _king;
	princess* _princess;
	flag* _flag;

public:
	stage2();
	~stage2();

	HRESULT init();
	void release();
	void update();
	void render();
};


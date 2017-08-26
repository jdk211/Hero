#pragma once

#include "gameNode.h"
//#include "loadingScene.h"
#include "titleScene.h"
#include "introScene.h"
#include "worldScene.h"
#include "gameOverScene.h"
#include "stage1.h"
#include "stage2.h"

class gameStudy : public gameNode
{
private:
	bool _showFrame;

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addSource();
};


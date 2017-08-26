#pragma once
#include "gameNode.h"
#include "talk_box.h"

class introScene : public gameNode
{
private:
	talk_box* _dial;

public:
	introScene();
	~introScene();

	HRESULT init();
	void release();
	void update();
	void render();
};


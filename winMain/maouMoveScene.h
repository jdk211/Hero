#pragma once
#include "gameNode.h"
#include "talk_box.h"

//용사 등장 후 마왕 대사와 마왕 위치 변경씬
class maouMoveScene : public gameNode
{
private:
	talk_box* _dial;
	
	bool _dialEnd;

public:
	maouMoveScene();
	~maouMoveScene();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getDialEnd() { return _dialEnd; }
};


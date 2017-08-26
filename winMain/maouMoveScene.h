#pragma once
#include "gameNode.h"
#include "talk_box.h"

//��� ���� �� ���� ���� ���� ��ġ �����
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


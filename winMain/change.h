#pragma once
#include "gameNode.h"
// ��� ���� ��
class change : public gameNode
{
private:
	image* _img;
	int _frameCnt;
	bool _isEnd;

public:
	change();
	~change();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void frameCnt();

	bool getIsEnd() { return _isEnd; }
};


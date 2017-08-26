#pragma once
#include "gameNode.h"

enum eBUTTON
{
	START,
	OPTION,
	BGM,
	SE,
	END,
	CURSOR,
	BTNMAX
};

struct stBUTTON
{
	image* img;
	RECT rc;
};

class titleScene : public gameNode
{
private:
	vector<string> _vOption;

	stBUTTON _btn[BTNMAX];

	int _y;

	bool _selectNum;	//1�̸� OPTIONȭ��
	bool _isStart;		//���� Ŀ���� START�� �ִ�
	bool _isBgm;		//���� Ŀ���� BGM�� �ִ�

public:
	titleScene();
	~titleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
};


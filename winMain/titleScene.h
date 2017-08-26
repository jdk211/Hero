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

	bool _selectNum;	//1이면 OPTION화면
	bool _isStart;		//현재 커서가 START에 있니
	bool _isBgm;		//현재 커서가 BGM에 있니

public:
	titleScene();
	~titleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
};


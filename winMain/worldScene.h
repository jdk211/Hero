#pragma once
#include "gameNode.h"
#include "talk_box.h"
#include "maou_play.h"

#define MAXSTAGE 5

struct STAGE
{
	int x, y;
	string stageScene;
	char* stageName;
	bool clear;
};

class worldScene : public gameNode
{
private:
	talk_box* _dial;		//마왕 대사
	maou_play* _maou;//마왕 움직일 커서
	STAGE _stage[MAXSTAGE];	//스테이지 위치, 이름, 이동씬 이름

	int _cnt;				//알파값 낮출 카운트
	int _alphaCnt;			//알파 값
	int _stageNum;			//스테이지 이동 번호
	
public:
	worldScene();
	~worldScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void alphaFrame();
};


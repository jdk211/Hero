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
	talk_box* _dial;		//���� ���
	maou_play* _maou;//���� ������ Ŀ��
	STAGE _stage[MAXSTAGE];	//�������� ��ġ, �̸�, �̵��� �̸�

	int _cnt;				//���İ� ���� ī��Ʈ
	int _alphaCnt;			//���� ��
	int _stageNum;			//�������� �̵� ��ȣ
	
public:
	worldScene();
	~worldScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void alphaFrame();
};


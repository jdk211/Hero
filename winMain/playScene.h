#pragma once
#include "gameNode.h"
#include "maou_play.h"
#include "talk_box.h"
#include "pickax.h"
#include "appearScene.h"
#include "maouMoveScene.h"
#include "maouPositionScene.h"
#include "heroManager.h"
#include "unitManager.h"
#include "block.h"

class playScene : public gameNode
{
private:
	talk_box* _dial;			//처음 들어왔을때 대사
	appearScene* _appearScene;	//용사 등장 씬
	maouMoveScene* _maouScene;	//용사가 도착한 후 마왕을 옮기는 씬에서 대사
	maouPositionScene* _maouPositionSc; //마왕의 위치 조정시

	heroManager* _stageHero;	//히어로
	maou_play* _maou;			//마왕
	unitManager* _um;			//몬스터
	pickax* _pickax;			//곡괭이
	block* _block;				//블럭

	int _stageNum;
	bool _isPlay;

	string _startBgm;

	bool _heroIn;		//용사가 목표에 도착했는지
	bool _isMove;		//
	bool _isSetMaou;	//용사 도착 후 대사 끝난 뒤 마왕의 위치 변경했는지
	bool _isChange;		//곡괭이와 마왕의 위치 변경
	bool _isPosition;	//마왕의 위치에 만족하는지 물어보는씬
	bool _heroInSnd;	//목표 도달시 사운드
	bool _heroArrest;	//마왕 잡으면 사운드

public:
	playScene();
	~playScene();

	HRESULT init(string dial, string folderName, string startBgm, int stageNumber);
	void release();
	void update();
	void render();

	void setMaou();
	void setIsPlay() { _isPlay = !_isPlay; }
};


#pragma once
#include "gameNode.h"

class heroManager;

class appearScene : public gameNode
{
private:
	heroManager* _hm;

	RECT _rc;
	image* _heroImg;
	string _heroName;
	string _heroMoveImg;
	float _x, _y;
	int _blindCnt;
	int _blindTotal;
	int _frameCnt;
	int _cntTotal;
	
	float _goalCdn; //좌표
	float _goalDis;	//거리
	float _goalTime; //도달시간

	bool _intro;
	bool _isGoal;
	bool _isPlay;
	bool _isBlind;

public:
	appearScene();
	~appearScene();

	HRESULT init(string imgName1, string imgName2, string heroName);
	void release();
	void update();
	void render();

	void move();

	void frameCnt();

	bool getIsGoal() { return _isGoal; }
	bool getIntro() { return _intro; }
	string getHeroName() { return _heroName; }

	void setHeroManagerMemoryLink(heroManager* heroManagerLink) { _hm = heroManagerLink; }
};


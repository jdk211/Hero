#pragma once

#include "gameNode.h"

#include <vector>
#include <map>

enum MAOUDIALSTATE
{
	IDLE,
	EXIC,
	OMG,
	OTL,
	SAD
};

class maou
{
public:
	MAOUDIALSTATE state;
	string dial;
	string voice;

	maou() {}
	~maou() {}
};

class talk_box : public gameNode
{
private:
	vector<string> _vDialTemp;
	vector<maou*> _vDialogue;

	string _folderName;

	int _cnt;					//문자 한글자씩 나오는 카운트
	int _maouX, _maouY;			//마왕 얼굴 위치
	int _boxX, _boxY;			//박스 위치
	int _textX, _textY;			//글자 위치
	int _width, _height;		//문자열 박스 크기
	int _endPointX, _endPointY; //문자 끝나면 나오는 포인터 위치
	int _fontSize;				//글자 크기
	int _fontSpace;				//글자 공간
	int _txtCnt;				//한글자씩 나오는 시간 카운터
	int _txtSpd;				//한글자씩 나오는 속도
	int _i;						//현재 문자열 위치

	bool _isDialEnd;			//모든 문자열 출력이 끝났는지
	bool _endPointOn;			//endpoint 깜박이기
	float _pointTime;			//endpoint getElapsedTime 받아주는 시간
	float _pointSpd;			//endpoint 깜박거리는 기준 시간

	bool _firstDialSnd;			//처음 대사 시작

public:
	talk_box();
	~talk_box();

	HRESULT init(string txtName, string folderName);
	void release();
	void update();
	void render();

	void loadTXT(string txtName);
	void addVoice();
	void keyControl();
	void txtRead();
	void hidePoint();
	bool isEndPoint();

	bool getIsDialEnd() { return _isDialEnd; }
	
	void setTxtSpd(int spd) { _txtSpd = spd; }
};


#pragma once
#include "gameNode.h"
#include "talk_box.h"

class maouPositionScene : public gameNode
{
private:
	RECT _rc[2];
	string _dial;

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
	int _ynBoxX, _ynBoxY;

	int _arrNum;				//Yes 0, No 1

public:
	maouPositionScene();
	~maouPositionScene();

	HRESULT init();
	void release();
	void update();
	void render();

	int getYesOrNo() { return _arrNum; }
};


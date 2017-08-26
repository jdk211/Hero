#pragma once
#include "gameNode.h"
#include "talk_box.h"

class maouPositionScene : public gameNode
{
private:
	RECT _rc[2];
	string _dial;

	int _cnt;					//���� �ѱ��ھ� ������ ī��Ʈ
	int _maouX, _maouY;			//���� �� ��ġ
	int _boxX, _boxY;			//�ڽ� ��ġ
	int _textX, _textY;			//���� ��ġ
	int _width, _height;		//���ڿ� �ڽ� ũ��
	int _endPointX, _endPointY; //���� ������ ������ ������ ��ġ
	int _fontSize;				//���� ũ��
	int _fontSpace;				//���� ����
	int _txtCnt;				//�ѱ��ھ� ������ �ð� ī����
	int _txtSpd;				//�ѱ��ھ� ������ �ӵ�
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


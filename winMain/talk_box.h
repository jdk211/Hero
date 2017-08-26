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
	int _i;						//���� ���ڿ� ��ġ

	bool _isDialEnd;			//��� ���ڿ� ����� ��������
	bool _endPointOn;			//endpoint �����̱�
	float _pointTime;			//endpoint getElapsedTime �޾��ִ� �ð�
	float _pointSpd;			//endpoint ���ڰŸ��� ���� �ð�

	bool _firstDialSnd;			//ó�� ��� ����

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


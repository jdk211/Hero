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
	talk_box* _dial;			//ó�� �������� ���
	appearScene* _appearScene;	//��� ���� ��
	maouMoveScene* _maouScene;	//��簡 ������ �� ������ �ű�� ������ ���
	maouPositionScene* _maouPositionSc; //������ ��ġ ������

	heroManager* _stageHero;	//�����
	maou_play* _maou;			//����
	unitManager* _um;			//����
	pickax* _pickax;			//���
	block* _block;				//��

	int _stageNum;
	bool _isPlay;

	string _startBgm;

	bool _heroIn;		//��簡 ��ǥ�� �����ߴ���
	bool _isMove;		//
	bool _isSetMaou;	//��� ���� �� ��� ���� �� ������ ��ġ �����ߴ���
	bool _isChange;		//��̿� ������ ��ġ ����
	bool _isPosition;	//������ ��ġ�� �����ϴ��� ����¾�
	bool _heroInSnd;	//��ǥ ���޽� ����
	bool _heroArrest;	//���� ������ ����

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


#include "stdafx.h"
#include "gameStudy.h"

gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);

	_showFrame = false; //timeManager ���

	addSource(); //���� �̹���, ����

	SCENEMANAGER->addScene("title", new titleScene); //Ÿ��Ʋ ��
	SCENEMANAGER->addScene("intro", new introScene); //��Ʈ�� ��
	SCENEMANAGER->addScene("world", new worldScene); //���� ��
	SCENEMANAGER->addScene("stage1", new stage1); //stage1 ��
	SCENEMANAGER->addScene("stage2", new stage2); //stage2 ��
	SCENEMANAGER->addScene("gameover", new gameOverScene); //���ӿ��� ��

	//SCENEMANAGER->changeScene("title"); //���� Ÿ��Ʋ ��
	SCENEMANAGER->changeScene("stage1");

	return S_OK;
}

void gameStudy::release()
{
	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
	EFFECTMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown('R')) _showFrame = !_showFrame; //�����Ӱ� �ð� �����ִ� Ű

	gameNode::update();
}

void gameStudy::render()
{
	//����ۿ��� �ѷ���
	/*HDC backDC = this->getBackBuffer()->getMemDC();*/
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	SetBkMode(getMemDC(), TRANSPARENT);
	//============================================================
	SCENEMANAGER->render();
	EFFECTMANAGER->render();

	if (_showFrame)
	{
		TIMEMANAGER->render(getMemDC());

		//���콺 ��ǥ
		char str2[32];
		sprintf_s(str2, "%d, %d", _ptMouse.x, _ptMouse.y);
		MY_UTIL::TextOutPlus(getMemDC(), _ptMouse.x, _ptMouse.y - 10, str2, 10, FONTCOLOR, 100, "����9");
	}
	//============================================================
	//����ۿ� �ִ� �׸��� HDC�� �׸���
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
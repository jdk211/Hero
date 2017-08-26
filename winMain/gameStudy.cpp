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

	_showFrame = false; //timeManager 출력

	addSource(); //공용 이미지, 사운드

	SCENEMANAGER->addScene("title", new titleScene); //타이틀 씬
	SCENEMANAGER->addScene("intro", new introScene); //인트로 씬
	SCENEMANAGER->addScene("world", new worldScene); //월드 씬
	SCENEMANAGER->addScene("stage1", new stage1); //stage1 씬
	SCENEMANAGER->addScene("stage2", new stage2); //stage2 씬
	SCENEMANAGER->addScene("gameover", new gameOverScene); //게임오버 씬

	//SCENEMANAGER->changeScene("title"); //시작 타이틀 씬
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

	if (KEYMANAGER->isOnceKeyDown('R')) _showFrame = !_showFrame; //프레임과 시간 보여주는 키

	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려줌
	/*HDC backDC = this->getBackBuffer()->getMemDC();*/
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	SetBkMode(getMemDC(), TRANSPARENT);
	//============================================================
	SCENEMANAGER->render();
	EFFECTMANAGER->render();

	if (_showFrame)
	{
		TIMEMANAGER->render(getMemDC());

		//마우스 좌표
		char str2[32];
		sprintf_s(str2, "%d, %d", _ptMouse.x, _ptMouse.y);
		MY_UTIL::TextOutPlus(getMemDC(), _ptMouse.x, _ptMouse.y - 10, str2, 10, FONTCOLOR, 100, "도담9");
	}
	//============================================================
	//백버퍼에 있는 그림을 HDC에 그리자
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
#include "stdafx.h"
#include "appearScene.h"


appearScene::appearScene()
{
}


appearScene::~appearScene()
{
}

HRESULT appearScene::init(string imgName1, string imgName2, string heroName)
{
	IMAGEMANAGER->addFrameImage("appearblind", "hero/appearScene.bmp", 16252, WINSIZEY, 17, 1, true, TRANSCOLOR);

	_heroImg = IMAGEMANAGER->findImage(imgName1);
	_heroMoveImg = imgName2;
	_heroName = heroName;

	_x = 550.f;
	_y = 200.f;
	_goalTime = 10.f;
	_goalDis = 36 * 16;
	_goalCdn = 36 * 31;

	_rc = RectMakeCenter(_x, _y, _heroImg->getFrameWidth(), _heroImg->getFrameHeight());

	_intro = false;
	_isGoal = false;
	_isBlind = false;
	_isPlay = true;

	_frameCnt = 0;
	_cntTotal = 0;
	_blindCnt = 0;
	_blindTotal = 0;

	return S_OK;
}

void appearScene::release()
{
}

void appearScene::update()
{
	_rc = RectMakeCenter(_x, _y, _heroImg->getFrameWidth(), _heroImg->getFrameHeight());

	frameCnt();

	if (_isPlay)
	{
		SOUNDMANAGER->play("appearScene", _bgmVolume);
		_isPlay = !_isPlay;
	}

	if (KEYMANAGER->isOnceKeyDown('Z') && _isBlind)
	{
		SOUNDMANAGER->stop("appearScene");
		_intro = true;
	}

	if (_intro && !_isGoal)
	{
		_heroImg = IMAGEMANAGER->findImage(_heroMoveImg);
		move();
	}

	if (_x >= _goalCdn) _isGoal = true;
}

void appearScene::render()
{
	if (!_isGoal) _heroImg->frameRender(getMemDC(), CAMERA->getUnitViewX(_rc.left), CAMERA->getUnitViewY(_rc.top), _frameCnt, 0);
	if (!_intro) IMAGEMANAGER->findImage("appearblind")->frameRender(getMemDC(), 0, 0, _blindCnt, 0);
	if (_isBlind && !_intro)
	{
		MY_UTIL::TextOutPlus(getMemDC(), CAMERA->getUnitViewX(WINSIZEX - 200), CAMERA->getUnitViewY(35), "PRESS 'Z' BUTTON", 15, FONTCOLOR, 1000, "도담9");
		MY_UTIL::TextOutPlus(getMemDC(), CAMERA->getUnitViewX(CENTERX - 100), CAMERA->getUnitViewY(30), _heroName.c_str(), 25, FONTCOLOR, 1000, "도담9");
	}
}

void appearScene::move()
{
	_x += (_goalDis / _goalTime) * TIMEMANAGER->getElapsedTime();
}

void appearScene::frameCnt()
{
	_cntTotal++;

	if (_cntTotal % 10 == 0)
	{
		if (_heroImg->getFrameX() >= _heroImg->getMaxFrameX())
		{
			_frameCnt = 0;
			_cntTotal = 0;
		}
		else _frameCnt++;
	}

	if (IMAGEMANAGER->findImage("appearblind")->getFrameX() != IMAGEMANAGER->findImage("appearblind")->getMaxFrameX()) _blindTotal++;
	if (_blindTotal % 5 == 0)
	{
		if (IMAGEMANAGER->findImage("appearblind")->getFrameX() >= IMAGEMANAGER->findImage("appearblind")->getMaxFrameX())
		{
			_isBlind = true;
			IMAGEMANAGER->findImage("appearblind")->getMaxFrameX();
		}
		else _blindCnt++;
	}
}

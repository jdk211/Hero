#include "stdafx.h"
#include "maou_play.h"


maou_play::maou_play()
{
}


maou_play::~maou_play()
{
}

HRESULT maou_play::init(int state)
{
	IMAGEMANAGER->addFrameImage("maou_play_idle", "play/maou_idle.bmp", 120, 38, 3, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("maou_play_move", "play/maou_move.bmp", 71, 70, 2, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("maou_play_arrest", "play/maou_arrest.bmp", 62, 38, 3, 1, true, TRANSCOLOR);

	_maou.x = 100;
	_maou.y = 100;

	_maou.beforeState = _maou.state = (MAOUSTATE)state;

	_maou.img = new image;

	if (_maou.state == MAOU_IDLE) _maou.img = IMAGEMANAGER->findImage("maou_play_idle");
	if (_maou.state == MAOU_MOVE) _maou.img = IMAGEMANAGER->findImage("maou_play_move");

	_maou.ani = new animation;
	_maou.ani->init(_maou.img->getWidth(), _maou.img->getHeight(), _maou.img->getFrameWidth(), _maou.img->getFrameHeight());
	_maou.ani->setDefPlayFrame(true, true);
	_maou.ani->setFPS(5); 

	_maou.ani->start();

	return S_OK;
}

void maou_play::release()
{
}

void maou_play::update()
{
	if (_maou.state == MAOU_IDLE) _maou.img = IMAGEMANAGER->findImage("maou_play_idle");
	if (_maou.state == MAOU_MOVE) _maou.img = IMAGEMANAGER->findImage("maou_play_move");
	if (_maou.state == MAOU_ARREST) _maou.img = IMAGEMANAGER->findImage("maou_play_arrest");

	if (_maou.beforeState != _maou.state)
	{
		_maou.ani = new animation;
		_maou.ani->init(_maou.img->getWidth(), _maou.img->getHeight(), _maou.img->getFrameWidth(), _maou.img->getFrameHeight());
		_maou.ani->setDefPlayFrame(true, true);
		_maou.ani->setFPS(5);

		_maou.ani->start();

		_maou.beforeState = _maou.state;
	}

	_maou.ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void maou_play::render()
{
	if (_maou.state == MAOU_IDLE) _maou.img->aniRender(getMemDC(), CAMERA->getObjectX(_maou.x), CAMERA->getObjectY(_maou.y), _maou.ani);
	else if (_maou.state == MAOU_MOVE) _maou.img->aniRender(getMemDC(), CAMERA->getObjectX(_maou.x + 5), CAMERA->getObjectY(_maou.y - _maou.img->getFrameHeight() / 2), _maou.ani);
	else if (_maou.state == MAOU_ARREST) _maou.img->aniRender(getMemDC(), CAMERA->getObjectX(_maou.x + 10), CAMERA->getObjectY(_maou.y), _maou.ani);
}	
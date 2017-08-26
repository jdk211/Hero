#include "stdafx.h"
#include "change.h"


change::change()
{
}


change::~change()
{
}

HRESULT change::init()
{
	_img = IMAGEMANAGER->addFrameImage("curtain", "play/curtain.bmp", 18164, 516, 19, 1, true, TRANSCOLOR);
	
	_isEnd = false;

	_frameCnt = 0;

	return S_OK;
}

void change::release()
{
}

void change::update()
{
	frameCnt();
}

void change::render()
{
	_img->frameRender(getMemDC(), 0, 0, _frameCnt, 0);
}

void change::frameCnt()
{
	_frameCnt++;

	if (_frameCnt % 5 == 0)
	{
		if (_img->getMaxFrameX() < _img->getFrameX())
		{
			_isEnd = true;
		}
		else
		{
			_img->setFrameX(_img->getFrameX() + 1);
		}
	}
}


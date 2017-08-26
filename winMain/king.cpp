#include "stdafx.h"
#include "king.h"


king::king()
{
}

king::~king()
{
}

HRESULT king::init()
{
	_img = new image;
	_img = IMAGEMANAGER->addFrameImage("king", "map_object/king.bmp", 90, 19, 3, 1, true, TRANSCOLOR);

	_ani = new animation;
	_ani->init(90, 19, 30, 19);
	_ani->setDefPlayFrame(true, true);
	_ani->setFPS(3);
	_ani->start();

	return S_OK;
}

void king::release()
{
}

void king::update()
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void king::render()
{
	_img->aniRender(getMemDC(), CAMERA->getUnitViewX(460), CAMERA->getUnitViewY(139), _ani);
}

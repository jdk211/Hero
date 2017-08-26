#include "stdafx.h"
#include "flag.h"


flag::flag()
{
}


flag::~flag()
{
}

HRESULT flag::init()
{
	_flag1 = new image;
	_flag1 = IMAGEMANAGER->addFrameImage("flag1", "map_object/flag.bmp", 40, 24, 2, 1, true, TRANSCOLOR);

	_flag2 = new image;
	_flag2 = IMAGEMANAGER->addFrameImage("flag2", "map_object/flag2.bmp", 40, 24, 2, 1, true, TRANSCOLOR);

	_ani = new animation;
	_ani->init(40, 24, 20, 24);
	_ani->setDefPlayFrame(true, true);
	_ani->setFPS(3);
	_ani->start();

	return S_OK;
}

void flag::release()
{
}

void flag::update()
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void flag::render()
{
	_flag1->aniRender(getMemDC(), CAMERA->getUnitViewX(422), CAMERA->getUnitViewY(84), _ani);
	_flag2->aniRender(getMemDC(), CAMERA->getUnitViewX(500), CAMERA->getUnitViewY(84), _ani);
}

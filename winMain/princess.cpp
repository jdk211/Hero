#include "stdafx.h"
#include "princess.h"


princess::princess()
{
}


princess::~princess()
{
}

HRESULT princess::init()
{
	_img = new image;
	_img = IMAGEMANAGER->addFrameImage("princess", "map_object/princess.bmp", 90, 19, 3, 1, true, TRANSCOLOR);

	_ani = new animation;
	_ani->init(90, 19, 30, 19);
	_ani->setDefPlayFrame(true, true);
	_ani->setFPS(3);
	_ani->start();

	return S_OK;
}

void princess::release()
{
}

void princess::update()
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void princess::render()
{
	_img->aniRender(getMemDC(), CAMERA->getUnitViewX(496), CAMERA->getUnitViewY(139), _ani);
}

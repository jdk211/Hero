#include "stdafx.h"
#include "stage2.h"


stage2::stage2()
{
}


stage2::~stage2()
{
}

HRESULT stage2::init()
{
	IMAGEMANAGER->addImage("stage_1_map", "stage_1/stage_1_map.bmp", 2232, 1512, false, false);
	SOUNDMANAGER->addSound("stage1_bgm", "stage_1/stage_1_bgm.mp3", true, true);

	_play = new playScene;
	_play->init("stage_1/stage_1_dialogue.txt", "stage_1", "stage1_bgm", 1);

	_princess = new princess;
	_king = new king;
	_flag = new flag;

	_princess->init();
	_king->init();
	_flag->init();

	return S_OK;
}

void stage2::release()
{
	_play->release();
	SAFE_DELETE(_play);
}

void stage2::update()
{
	_play->update();
	_princess->update();
	_king->update();
	_flag->update();
}

void stage2::render()
{
	IMAGEMANAGER->findImage("stage_1_map")->render(getMemDC(), CAMERA->getViewStartX(), CAMERA->getViewStartY());

	_princess->render();
	_king->render();
	_flag->render();
	_play->render();
}

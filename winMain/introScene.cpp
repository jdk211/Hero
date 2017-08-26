#include "stdafx.h"
#include "introScene.h"


introScene::introScene()
{
}


introScene::~introScene()
{
}

HRESULT introScene::init()
{
	_dial = new talk_box;
	_dial->init("worldScene/intro_dialogue.txt", "worldScene");

	return S_OK;
}

void introScene::release()
{
	_dial->release();
	SAFE_DELETE(_dial);
}

void introScene::update()
{
	_dial->update();

	if (_dial->getIsDialEnd())
	{
		SCENEMANAGER->changeScene("world");
	}
}

void introScene::render()
{
	_dial->render();
}
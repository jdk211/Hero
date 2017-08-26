#include "stdafx.h"
#include "maouMoveScene.h"


maouMoveScene::maouMoveScene()
{
}

maouMoveScene::~maouMoveScene()
{
}

HRESULT maouMoveScene::init()
{
	_dial = new talk_box;
	_dial->init("play/heroInDial.txt", "play");
	_dial->setTxtSpd(2);

	_dialEnd = false;

	return S_OK;
}

void maouMoveScene::release()
{
	_dial->release();
	SAFE_DELETE(_dial);
}

void maouMoveScene::update()
{
	if(!_dial->getIsDialEnd()) _dial->update();
	else
	{
		_dialEnd = true;
	}
}

void maouMoveScene::render()
{
	if (!_dial->getIsDialEnd()) _dial->render();
}

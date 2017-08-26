#include "stdafx.h"
#include "maouPositionScene.h"

maouPositionScene::maouPositionScene()
{
}

maouPositionScene::~maouPositionScene()
{
}

HRESULT maouPositionScene::init()
{
	IMAGEMANAGER->addImage("YorN", "textbox/selectYesNo.bmp", 141, 32, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("selectPoint", "textbox/select_point.bmp", 12, 20, true, TRANSCOLOR);

	_maouX = 34;
	_maouY = 409;
	_boxX = 28;
	_boxY = 405;
	_ynBoxX = 765;
	_ynBoxY = 480;
	_textX = 190;
	_textY = 420;
	_endPointX = 885;
	_endPointY = 485;
	_width = 670;
	_height = 150;
	_fontSize = 24;
	_fontSpace = _fontSize * 0.5;

	_arrNum = 1;

	_rc[0] = RectMake(_ynBoxX + 35, _ynBoxY + 6, 10, 10);
	_rc[1] = RectMake(_ynBoxX + 90, _ynBoxY + 6, 10, 10);

	_dial = "여기가 베스트란 말씀이시죠?";

	return S_OK;
}

void maouPositionScene::release()
{
}

void maouPositionScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_arrNum != 0) SOUNDMANAGER->play("ctl_move", _seVolume);
		_arrNum = 0;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_arrNum != 1) SOUNDMANAGER->play("ctl_move", _seVolume);
		_arrNum = 1;
	}
}

void maouPositionScene::render()
{
	IMAGEMANAGER->findImage("t_box")->render(getMemDC(), _boxX, _boxY);
	IMAGEMANAGER->findImage("maou_idle")->render(getMemDC(), _maouX, _maouY);
	IMAGEMANAGER->findImage("YorN")->render(getMemDC(), _ynBoxX, _ynBoxY);
	IMAGEMANAGER->findImage("selectPoint")->render(getMemDC(), _rc[_arrNum].left - 20, _rc[_arrNum].top);

	MY_UTIL::DrawTextPlus(getMemDC(), _textX, _textY, _width, _height, _dial.c_str(), _fontSize, FONTCOLOR, 1000, "도담9");
	MY_UTIL::DrawTextPlus(getMemDC(), _rc[0].left, _rc[0].top, _width, _height, "응", 20, FONTCOLOR, 1000, "도담9");
	MY_UTIL::DrawTextPlus(getMemDC(), _rc[1].left, _rc[1].top, _width, _height, "아니", 20, FONTCOLOR, 1000, "도담9");
}

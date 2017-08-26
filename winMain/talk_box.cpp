#include "stdafx.h"
#include "talk_box.h"

talk_box::talk_box()
{
}

talk_box::~talk_box()
{
}

HRESULT talk_box::init(string txtName, string folderName)
{
	_folderName = folderName;

	IMAGEMANAGER->addImage("t_box", "textbox/talk_box.bmp", 900, 102, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("end_point", "textbox/talk_point.bmp", 29, 15, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("maou_idle", "textbox/maou_idle.bmp", 125, 94, false, false);
	IMAGEMANAGER->addImage("maou_excit", "textbox/maou_excited.bmp", 125, 94, false, false);
	IMAGEMANAGER->addImage("maou_omg", "textbox/maou_omg.bmp", 125, 94, false, false);
	IMAGEMANAGER->addImage("maou_otl", "textbox/maou_otl.bmp", 125, 94, false, false);
	IMAGEMANAGER->addImage("maou_sad", "textbox/maou_sad.bmp", 125, 94, false, false);

	_cnt = 0;

	_maouX = 34;
	_maouY = 409;
	_boxX = 28;
	_boxY = 405;
	_textX = 190;
	_textY = 420;
	_endPointX = 885;
	_endPointY = 485;
	_width = 670;
	_height = 150;
	_fontSize = 24;
	_fontSpace = _fontSize * 0.5;
	_txtCnt = 0;
	_txtSpd = 5;
	_i = 0;

	loadTXT(txtName);
	addVoice();

	_firstDialSnd = true;
	_isDialEnd = false;
	_endPointOn = true;
	_pointTime = 0.f;
	_pointSpd = 0.7f;

	return S_OK;
}

void talk_box::release()
{
	_vDialogue.clear();
}

void talk_box::update()
{
	if (_firstDialSnd)
	{
		SOUNDMANAGER->play(_vDialogue[_cnt]->voice, _seVolume);
		_firstDialSnd = !_firstDialSnd;
	}
	txtRead();
	keyControl();
	hidePoint();
}

void talk_box::render()
{
	if (_vDialogue[_cnt]->state == IDLE) IMAGEMANAGER->findImage("maou_idle")->render(getMemDC(), _maouX, _maouY);
	else if (_vDialogue[_cnt]->state == EXIC) IMAGEMANAGER->findImage("maou_excit")->render(getMemDC(), _maouX, _maouY);
	else if (_vDialogue[_cnt]->state == OMG) IMAGEMANAGER->findImage("maou_omg")->render(getMemDC(), _maouX, _maouY);
	else if (_vDialogue[_cnt]->state == OTL) IMAGEMANAGER->findImage("maou_otl")->render(getMemDC(), _maouX, _maouY);
	else if (_vDialogue[_cnt]->state == SAD) IMAGEMANAGER->findImage("maou_sad")->render(getMemDC(), _maouX, _maouY);

	IMAGEMANAGER->findImage("t_box")->render(getMemDC(), _boxX, _boxY);

	int len = strlen(_vDialogue[_cnt]->dial.c_str());
	char* backChr = new char[len + 1];

	for (int i = 0; i < len + 1; i++)
	{
		backChr[i] = NULL;
	}

	for (int k = 0; k < _i + 1; k++)
	{
		backChr[k] = _vDialogue[_cnt]->dial.at(k);
	}

	if (isEndPoint())
	{
		if(_endPointOn) IMAGEMANAGER->findImage("end_point")->render(getMemDC(), _endPointX, _endPointY);
	}

	MY_UTIL::DrawTextPlus(getMemDC(), _textX, _textY, _width, _height, backChr, _fontSize, FONTCOLOR, 1000, "µµ´ã9");

	SAFE_DELETE_ARRAY(backChr);
}

void talk_box::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		int len = strlen(_vDialogue[_cnt]->dial.c_str());
		if (!isEndPoint())
		{
			SOUNDMANAGER->stop(_vDialogue[_cnt]->voice);
			_i = len - 1;
		}
		else
		{
			if (_cnt < _vDialogue.size() - 1)
			{
				SOUNDMANAGER->stop(_vDialogue[_cnt]->voice);
				_cnt++;
				_i = 0;
				_pointTime = 0.f;
				_endPointOn = true;
				SOUNDMANAGER->play(_vDialogue[_cnt]->voice, _seVolume);
			}
			else
			{
				_isDialEnd = true;
			}
		}
	}
}

void talk_box::txtRead()
{
	_txtCnt++;

	if (_txtCnt % _txtSpd == 0 && _i < strlen(_vDialogue[_cnt]->dial.c_str()) - 1)
	{
		_i++;
		_txtCnt = 0;
	}
}

void talk_box::hidePoint()
{
	if (isEndPoint())
	{
		_pointTime += TIMEMANAGER->getElapsedTime();
		if (_pointTime > _pointSpd)
		{
			_endPointOn = !_endPointOn;
			_pointTime = 0;
		}
	}
}

void talk_box::loadTXT(string txtName)
{
	_vDialTemp = TXTDATA->txtLoad(txtName.c_str());

	for (unsigned int i = 0; i < _vDialTemp.size(); i++)
	{
		if (_vDialTemp[i] == "|")
		{
			maou* maou_dial;

			maou_dial = new maou;

			maou_dial->state = (MAOUDIALSTATE)atoi(_vDialTemp[i + 1].c_str());
			maou_dial->voice = _vDialTemp[i + 2].c_str();
			maou_dial->dial = _vDialTemp[i + 3].c_str();

			_vDialogue.push_back(maou_dial);
		}
	}
}

void talk_box::addVoice()
{
	for (unsigned int i = 0; i < _vDialogue.size(); i++)
	{
		SOUNDMANAGER->addSound(_vDialogue[i]->voice, _folderName + "/" + _vDialogue[i]->voice + ".mp3", false, false);
	}
}

bool talk_box::isEndPoint()
{
	int len = strlen(_vDialogue[_cnt]->dial.c_str());
	if (_i == len - 1) return true;
	else return false;
}
#include "stdafx.h"
#include "titleScene.h"

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	_y = 355; //��ġ

	_vOption = TXTDATA->txtLoad("option.txt");
	
	_bgmVolume = atof(_vOption[0].c_str());
	_seVolume = atof(_vOption[1].c_str());

	IMAGEMANAGER->addImage("title_bg", "titleScene/title(956x516).bmp", 956, 516, false, false); // ���
	SOUNDMANAGER->addSound("titleScene_bgm", "titleScene/titleScene_bgm.mp3", true, true); //�����

	_selectNum = FALSE;
	_isStart = TRUE;
	_isBgm = FALSE;

	//��ư �̹���
	_btn[START].img = IMAGEMANAGER->addImage("start", "titleScene/start.bmp", 53, 19, true, TRANSCOLOR);
	_btn[OPTION].img = IMAGEMANAGER->addImage("option", "titleScene/option.bmp", 74, 23, true, TRANSCOLOR);
	_btn[BGM].img = IMAGEMANAGER->addImage("bgm", "titleScene/bgm.bmp", 49, 19, true, TRANSCOLOR);
	_btn[SE].img = IMAGEMANAGER->addImage("se", "titleScene/se.bmp", 28, 19, true, TRANSCOLOR);
	_btn[CURSOR].img = IMAGEMANAGER->addImage("cursor", "titleScene/cursor_yubi.bmp", 28, 19, true, TRANSCOLOR);

	//TITLE ȭ�� START OPTION��ư �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		_btn[i].rc = RectMake(340 + i * 200, _y, _btn[i].img->getWidth(), _btn[i].img->getHeight());
	}
	//�ɼǿ��� BGM SE ��ư �ʱ�ȭ
	for (int i = 2; i < 4; i++)
	{
		_btn[i].rc = RectMake(450, _y + ((i % 2) * 25), _btn[i].img->getWidth(), _btn[i].img->getHeight());
	}
	//Ŀ�� ��ġ �ʱ�ȭ
	_btn[CURSOR].rc = RectMake(_btn[START].rc.left - _btn[CURSOR].img->getWidth() - 10, _btn[START].rc.top, _btn[CURSOR].img->getWidth(), _btn[CURSOR].img->getHeight());

	SOUNDMANAGER->play("titleScene_bgm", _bgmVolume);

	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	keyControl();

	char str[32];
	sprintf_s(str, "%f", _bgmVolume);
	_vOption[0] = str;
	sprintf_s(str, "%f", _seVolume);
	_vOption[1] = str;

	TXTDATA->txtSave("option.txt", _vOption);
}

void titleScene::render()
{
	IMAGEMANAGER->findImage("title_bg")->render(getMemDC());

	if (!_selectNum)
	{
		_btn[CURSOR].img->render(getMemDC(), _btn[CURSOR].rc.left, _btn[CURSOR].rc.top);
		for (int i = 0; i < 2; i++)
		{
			_btn[i].img->render(getMemDC(), _btn[i].rc.left, _btn[i].rc.top);
		}
		char* cstr = "�̵� : �� �� �� ��, ����(Ȯ��) : Z, ���ư���(���) : X";
		MY_UTIL::DrawTextPlus(getMemDC(), 0, 475, WINSIZEX, 200, cstr, 22, FONTCOLOR, 1000, "����9", false, DT_CENTER);
	}
	else
	{
		_btn[CURSOR].img->render(getMemDC(), _btn[CURSOR].rc.left, _btn[CURSOR].rc.top);
		for (int i = 1; i < END; i++)
		{
			_btn[i].img->render(getMemDC(), _btn[i].rc.left, _btn[i].rc.top);
		}
		char str[32];
		sprintf_s(str, "%d", FLOAT_TO_INT(_bgmVolume * 10));
		MY_UTIL::TextOutPlus(getMemDC(), _btn[BGM].rc.right + 13, _btn[BGM].rc.top - 2, str, 24, FONTCOLOR, 1000, "����9");
		sprintf_s(str, "%d", FLOAT_TO_INT(_seVolume * 10));
		MY_UTIL::TextOutPlus(getMemDC(), _btn[BGM].rc.right + 13, _btn[SE].rc.top - 2, str, 24, FONTCOLOR, 1000, "����9");
		char* cstr = "�̵� : �� ��, �������� : �� ��, ���ư���(���) : X";
		MY_UTIL::DrawTextPlus(getMemDC(), 0, 475, WINSIZEX, 200, cstr, 22, FONTCOLOR, 1000, "����9", false, DT_CENTER);
	}	
}

void titleScene::keyControl()
{
	//Ű�� ������ �Ҹ��� ����.
	//if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)) SOUNDMANAGER->play("select_move", _seVolume);

	if (!_selectNum)
	{
		for (int i = 0; i < 2; i++)
		{
			_btn[i].rc = RectMake(340 + i * 200, 355, _btn[i].img->getWidth(), _btn[i].img->getHeight());
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_btn[CURSOR].rc.left != _btn[START].rc.left - _btn[CURSOR].img->getWidth() - 10) SOUNDMANAGER->play("select_move", _seVolume);
			_btn[CURSOR].rc = RectMake(_btn[START].rc.left - _btn[CURSOR].img->getWidth() - 10, _btn[START].rc.top, _btn[CURSOR].img->getWidth(), _btn[CURSOR].img->getHeight());
			_isStart = TRUE;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_btn[CURSOR].rc.left != _btn[OPTION].rc.left - _btn[CURSOR].img->getWidth() - 10) SOUNDMANAGER->play("select_move", _seVolume);
			_btn[CURSOR].rc = RectMake(_btn[OPTION].rc.left - _btn[CURSOR].img->getWidth() - 10, _btn[OPTION].rc.top, _btn[CURSOR].img->getWidth(), _btn[CURSOR].img->getHeight());
			_isStart = FALSE;
		}
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (_isStart)
			{
				SOUNDMANAGER->play("select_ok", _seVolume);//SCENEMANAGER->changeScene("stageScene");
				SOUNDMANAGER->stop("titleScene_bgm");
				SCENEMANAGER->changeScene("intro");
			}
			else
			{
				SOUNDMANAGER->play("select_ok", _seVolume);
				_btn[CURSOR].rc = RectMake(_btn[BGM].rc.left - _btn[CURSOR].img->getWidth() - 10, _btn[BGM].rc.top, _btn[CURSOR].img->getWidth(), _btn[CURSOR].img->getHeight());
				_isStart = FALSE;
				_isBgm = TRUE;
				_selectNum = TRUE;
			}
		}
	}
	else
	{
		_btn[OPTION].rc = RectMake(330, _y - 3, _btn[OPTION].img->getWidth(), _btn[OPTION].img->getHeight());
		_btn[BGM].rc = RectMake(450, _y, _btn[BGM].img->getWidth(), _btn[BGM].img->getHeight());
		_btn[SE].rc = RectMake(450, _y + 25, _btn[SE].img->getWidth(), _btn[SE].img->getHeight());

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_btn[CURSOR].rc.top != _btn[BGM].rc.top) SOUNDMANAGER->play("select_move", _seVolume);
			_btn[CURSOR].rc = RectMake(_btn[BGM].rc.left - _btn[CURSOR].img->getWidth() - 10, _btn[BGM].rc.top, _btn[CURSOR].img->getWidth(), _btn[CURSOR].img->getHeight());
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_btn[CURSOR].rc.top != _btn[SE].rc.top) SOUNDMANAGER->play("select_move", _seVolume);
			_btn[CURSOR].rc = RectMake(_btn[SE].rc.left - _btn[CURSOR].img->getWidth() - 10, _btn[SE].rc.top, _btn[CURSOR].img->getWidth(), _btn[CURSOR].img->getHeight());
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_btn[CURSOR].rc.top == _btn[BGM].rc.top)
			{
				_bgmVolume += 0.1f;
				if (_bgmVolume >= 1.1f)
				{
					_bgmVolume = 0.0f;
				}
				SOUNDMANAGER->volume();
			}
			if (_btn[CURSOR].rc.top == _btn[SE].rc.top)
			{
				_seVolume += 0.1f;
				if (_seVolume >= 1.1f)
				{
					_seVolume = 0.0f;
				}
			}
			SOUNDMANAGER->play("volume_se",_seVolume);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_btn[CURSOR].rc.top == _btn[BGM].rc.top)
			{
				_bgmVolume -= 0.1f;
				if (_bgmVolume <= -0.1f)
				{
					_bgmVolume = 1.0f;
				}
				SOUNDMANAGER->volume();
			}
			if (_btn[CURSOR].rc.top == _btn[SE].rc.top)
			{
				_seVolume -= 0.1f;
				if (_seVolume <= -0.1f)
				{
					_seVolume = 1.0f;
				}
			}
			SOUNDMANAGER->play("volume_se", _seVolume);
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("select_cancel", _seVolume);
			_selectNum = FALSE;
			_btn[CURSOR].rc = RectMake(_btn[START].rc.left - _btn[CURSOR].img->getWidth() - 10, _btn[START].rc.top, _btn[CURSOR].img->getWidth(), _btn[CURSOR].img->getHeight());
			_isStart = TRUE;
			_isBgm = FALSE;
		}
	}
}

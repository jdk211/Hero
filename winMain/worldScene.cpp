#include "stdafx.h"
#include "worldScene.h"


worldScene::worldScene()
{
}


worldScene::~worldScene()
{
}

HRESULT worldScene::init()
{
	IMAGEMANAGER->addImage("stage_board", "worldScene/stage_board2.bmp", 320, 114, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("world_bg", "worldScene/worldmap.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("world_alpha", "worldScene/world_alpha.bmp", WINSIZEX, WINSIZEY, false, false);
	SOUNDMANAGER->addSound("worldScene_bgm", "worldScene/worldScene_bgm.mp3", true, true);

	_dial = new talk_box;
	_dial->init("worldScene/world_dialogue.txt", "worldScene");

	_dial->setTxtSpd(2);

	_cnt = 0;
	_alphaCnt = 255;

	_stageNum = 0;

	_maou = new maou_play;
	_maou->init(1);

	_stage[0].x = 187;
	_stage[0].y = 287;
	_stage[0].stageName = "에리어 1 반 겔릭";
	_stage[0].stageScene = "stage1";
	_stage[0].clear = false;

	_stage[1].x = 196;
	_stage[1].y = 162;
	_stage[1].stageName = "에리어 2 데젤";
	_stage[1].stageScene = "stage2";
	_stage[1].clear = false;

	_stage[2].x = 321;
	_stage[2].y = 70;
	_stage[2].stageName = "에리어 3 야카갈라";
	_stage[2].stageScene = "stage3";
	_stage[2].clear = false;

	_stage[3].x = 722;
	_stage[3].y = 94;
	_stage[3].stageName = "에리어 4 애시풀";
	_stage[3].stageScene = "stage4";
	_stage[3].clear = false;

	_stage[4].x = 799;
	_stage[4].y = 268;
	_stage[4].stageName = "에리어 5 인더스티어";
	_stage[4].stageScene = "stage5";
	_stage[4].clear = false;

	_maou->setMaouXY(_stage[_stageNum].x, _stage[_stageNum].y);

	SOUNDMANAGER->play("worldScene_bgm", _bgmVolume);

	return S_OK;
}

void worldScene::release()
{
	_dial->release();
	SAFE_DELETE(_dial);
	_maou->release();
	SAFE_DELETE(_maou);
}

void worldScene::update()
{
	alphaFrame();
	if (_alphaCnt < 0)
	{
		if(!_dial->getIsDialEnd()) _dial->update();
		else
		{
			_maou->update();
			_maou->setMaouXY(_stage[_stageNum].x, _stage[_stageNum].y);
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				SOUNDMANAGER->play("ctl_move", _seVolume);
				_stageNum--;
				if (_stageNum < 0)
				{
					_stageNum = 0;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				SOUNDMANAGER->play("ctl_move", _seVolume);
				_stageNum++;
				if (_stageNum >= 5)
				{
					_stageNum = 4;
				}
			}
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				SOUNDMANAGER->play("stage_ok", _seVolume);
				SOUNDMANAGER->stop("worldScene_bgm");
				SCENEMANAGER->changeScene(_stage[_stageNum].stageScene);
			}
			if (KEYMANAGER->isOnceKeyDown('X'))
			{
				SOUNDMANAGER->play("select_cancel", _seVolume);
				SOUNDMANAGER->stop("worldScene_bgm");
				SCENEMANAGER->changeScene("title");
			}
		}
	}
}

void worldScene::render()
{
	IMAGEMANAGER->findImage("world_bg")->render(getMemDC());
	
	if(_alphaCnt > 0) IMAGEMANAGER->findImage("world_alpha")->alphaRender(getMemDC(), 0, 0, _alphaCnt);
	else
	{
		if (!_dial->getIsDialEnd()) _dial->render();
		else
		{
			
			IMAGEMANAGER->findImage("stage_board")->alphaRender(getMemDC(), 570, 15, 90);
			_maou->render();
			
			MY_UTIL::DrawTextPlus(getMemDC(), 580, 30, 300, 100, _stage[_stageNum].stageName, 24, FONTCOLOR, 1000, "도담9", false, DT_CENTER);

			char* str = "이동 : ← → ↑ ↓, 선택 : Z, 취소 : X";
			MY_UTIL::DrawTextPlus(getMemDC(), 20, 480, 915, 200, str, 22, FONTCOLOR, 1000, "도담9", true, DT_CENTER);
		}
	}
}

void worldScene::alphaFrame()
{
	if (_alphaCnt > 0)
	{
		_cnt++;
		if (_cnt % 15 == 0)
		{
			_alphaCnt -= 10;
			_cnt = 0;
		}
	}
}

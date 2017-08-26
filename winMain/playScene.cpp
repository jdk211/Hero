#include "stdafx.h"
#include "playScene.h"


playScene::playScene()
{
}


playScene::~playScene()
{
}

HRESULT playScene::init(string dial, string folderName, string startBgm, int stageNumber)
{
	_startBgm = startBgm;
	_stageNum = stageNumber;

	SOUNDMANAGER->addSound(startBgm, "play/" + startBgm + ".mp3", true, true);
	SOUNDMANAGER->addSound("play_pickax_bgm", "play/play_pickax_bgm.mp3", true, true);
	IMAGEMANAGER->addImage("dig_army", "play/DigArmy_k.bmp", 150, 113, true, TRANSCOLOR);

	_dial = new talk_box;
	_dial->init(dial, folderName);
	_dial->setTxtSpd(2);

	_maouScene = new maouMoveScene;
	_maouScene->init();

	_maouPositionSc = new maouPositionScene;
	_maouPositionSc->init();

	_block = new block;
	_block->init();

	_pickax = new pickax;
	_pickax->setBlockMemoryLink(_block);
	_pickax->init(290);

	_maou = new maou_play;
	_maou->init(0);
	_maou->setMaouXY(_block->getBlockX(3, 32) - 3, _block->getBlockY(3, 32) - 3);

	_um = new unitManager;
	_um->init();
	_um->setBlockMemoryLink(_block);
	_pickax->setunitManagerMemoryLink(_um);

	_stageHero = new heroManager;
	_stageHero->setBlockMemoryLink(_block);
	_stageHero->setUnitManagerMemoryLink(_um);
	_stageHero->setMaouMemoryLink(_maou);
	_stageHero->init(_stageNum);
	_um->setHeroMemoryLink(_stageHero);

	_appearScene = new appearScene;
	_appearScene->init(_stageHero->getVHero()[0]->getApSceneName1(), _stageHero->getVHero()[0]->getApSceneName2(), _stageHero->getVHero()[0]->getHeroName());

	_isPlay = true;
	_heroIn = false;
	_isMove = true;
	_isSetMaou = false;
	_isChange = false;
	_isPosition = false;
	_heroInSnd = false;
	_heroArrest = false;

	SOUNDMANAGER->play(startBgm, _bgmVolume);

	return S_OK;
}

void playScene::release()
{
	_dial->release();
	SAFE_DELETE(_dial);
	_pickax->release();
	SAFE_DELETE(_pickax);
	_block->release();
	SAFE_DELETE(_block);
	_maou->release();
	SAFE_DELETE(_maou);
	_stageHero->release();
	SAFE_DELETE(_stageHero);
	_um->release();
	SAFE_DELETE(_um);
	_appearScene->release();
	SAFE_DELETE(_appearScene);
	_maouScene->release();
	SAFE_DELETE(_maouScene);
	_maouPositionSc->release();
	SAFE_DELETE(_maouPositionSc);
}

void playScene::update()
{
	//시작 대사
	if (!_dial->getIsDialEnd()) _dial->update();
	//대사 끝나면 용사 등장
	else if (!_appearScene->getIntro())
	{
		SOUNDMANAGER->stop(_startBgm);
		_appearScene->update();
	}
	//용사 등장씬 끝나고
	else
	{
		SOUNDMANAGER->stop("appearScene");
		//용사가 목표 지점까지 오기 전에 업데이트
		if (!_appearScene->getIsGoal()) _appearScene->update();
		//목표 지점에 도착
		else
		{
			if (!_heroInSnd)
			{
				SOUNDMANAGER->stop("play_pickax_bgm");
				SOUNDMANAGER->play("hero_in", _bgmVolume);
				_heroInSnd = true;
			}
			_heroIn = true;
		}
		//목표 지점에 도착하면 마왕 세팅
		if (_heroIn && !_isSetMaou)
		{
			_maouScene->update();
			_isMove = false;
			if (_maouScene->getDialEnd()) setMaou();
		}
		//마왕 세팅 끝난 후
		else if (_isSetMaou)
		{
			_isMove = true;
			_heroIn = false;
			if (_appearScene->getIsGoal()) _stageHero->update();
		}

		if (!_isPosition)_pickax->update(_isMove, _maouScene->getDialEnd());
		if (_isPosition) _maouPositionSc->update();

		_um->update(_isMove);
		_block->update();
		_maou->update();

		if (_stageHero->getHeroSize() != 0)
		{
			if (_stageHero->getVHero()[0]->getIsTarget())
			{
				if (!_heroArrest)
				{
					SOUNDMANAGER->stop("hero_in_play");
					SOUNDMANAGER->play("hero_arrest", _bgmVolume);
					_heroArrest = true;
				}
			}
		}
		
		if (_isPlay)
		{
			SOUNDMANAGER->play("play_pickax_bgm", _bgmVolume);
			_isPlay = !_isPlay;
		}
	}

	CAMERA->update();
}

void playScene::render()
{
	_block->render();
	if (!_dial->getIsDialEnd()) { CAMERA->setViewX(36 * 31, 252); _dial->render(); }
	else if (!_appearScene->getIntro())
	{
		CAMERA->setViewX(0, 252);
		_appearScene->render();
	}
	else
	{
		//각각의 오브젝트들
		_appearScene->render();
		_um->render();
		_maou->render();
		if (_maou->getMaouState() != MAOU_MOVE) _pickax->render();
		if (_heroIn)
		{
			_maouScene->render();
			CAMERA->setViewX(_maou->getMaouX(), _maou->getMaouY());
		}
		if (_isPosition) _maouPositionSc->render();	//선택한 영역이 맞는지
		if (!_appearScene->getIsGoal()) _appearScene->render();
		else _stageHero->render();

		if (_isMove)
		{
			//내가 팔 수 있는 블럭 수 출력
			IMAGEMANAGER->findImage("dig_army")->alphaRender(getMemDC(), 783, 390, 100);
			char istr[32];
			sprintf_s(istr, "%3d", _pickax->getPickCnt());
			MY_UTIL::TextOutPlus(getMemDC(), 844, 400, istr, 24, RGB(255, 255, 0), 1000, "도담9");
			sprintf_s(istr, "%3d", _um->getVMonsterSize());
			MY_UTIL::TextOutPlus(getMemDC(), 844, 470, istr, 24, RGB(255, 255, 0), 1000, "도담9");
		}
	}
}

void playScene::setMaou()
{
	if (!_isChange) //카메라 체인지
	{
		_pickax->setPickX(3);
		_pickax->setPickY(32);
		_isChange = true;
	}
	else
	{
		if (_heroIn) _maou->setMaouState(MAOU_MOVE);

		_maou->setMaouXY(_pickax->getPickX(), _pickax->getPickY());

		if (!_isPosition)
		{
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				if (_pickax->getIsGround())
				{
					SOUNDMANAGER->play("stage_ok", _seVolume);
					_maouPositionSc->update();

					_isPosition = true;
				}
				else
				{
					SOUNDMANAGER->play("cant_break_block", _seVolume);
				}
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				if (_maouPositionSc->getYesOrNo() == 0)			//yes
				{
					_stageHero->getVHero()[0]->setHeroX(36 * 31);
					_stageHero->getVHero()[0]->setHeroY(36 * 7);
					_stageHero->getVHero()[0]->setHeroI(31);
					_stageHero->getVHero()[0]->setHeroJ(1);
					_stageHero->getVHero()[0]->setHeroState(HERO_MOVE_CHECK);

					_isSetMaou = true;
					_isPosition = false;

					_stageHero->getVHero()[0]->setTargetI(_pickax->getPickI());
					_stageHero->getVHero()[0]->setTargetJ(_pickax->getPickJ());

					_maou->setMaouState(MAOU_IDLE);

					SOUNDMANAGER->play("hero_in_play", _bgmVolume);
				}
				else if (_maouPositionSc->getYesOrNo() == 1)	//no
				{
					_isPosition = false;
				}
			}
		}
		
	}
}

#include "stdafx.h"
#include "bug.h"


bug::bug()
{
}


bug::~bug()
{
}

HRESULT bug::init(float x, float y, int i, int j)
{
	//SOUNDMANAGER->addSound("bug_attack", "monster/slime/bug_attack.mp3", false, false);

	IMAGEMANAGER->addFrameImage("bug_appear", "monster/bug/bug_appear.bmp", 180, 36, 5, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("bug_idle", "monster/bug/bug_idle.bmp", 36, 36, 1, 1, true, TRANSCOLOR);

	//IMAGEMANAGER->addFrameImage("bug_move_right", "monster/slime/bug_move_right.bmp", 360, 36, 10, 1, true, TRANSCOLOR);
	//IMAGEMANAGER->addFrameImage("bug_move_left", "monster/slime/bug_move_left.bmp", 360, 36, 10, 1, true, TRANSCOLOR);
	//IMAGEMANAGER->addFrameImage("bug_move_up_down", "monster/slime/bug_up_down.bmp", 396, 36, 11, 1, true, TRANSCOLOR);

	//IMAGEMANAGER->addFrameImage("bug_attack_right", "monster/slime/bug_attack_right.bmp", 114, 36, 3, 1, true, TRANSCOLOR);
	//IMAGEMANAGER->addFrameImage("bug_attack_left", "monster/slime/bug_attack_left.bmp", 114, 36, 3, 1, true, TRANSCOLOR);
	//IMAGEMANAGER->addFrameImage("bug_attack_up_down", "monster/slime/bug_attack_up_down.bmp", 228, 36, 6, 1, true, TRANSCOLOR);

	//IMAGEMANAGER->addFrameImage("bug_die", "monster/slime/bug_die.bmp", 720, 36, 20, 1, true, TRANSCOLOR);
	//IMAGEMANAGER->addFrameImage("bug_attack_die", "monster/slime/bug_attack_die.bmp", 595, 36, 8, 1, true, TRANSCOLOR);

	_bug.name = "厕撇国饭";

	_bug.bfMove = _bug.beForeState = _bug.state = MON_APPEAR;

	_bug.img = new image;
	_bug.img = IMAGEMANAGER->findImage("bug_appear");

	_bug.moveSpd = 0.3f;
	_bug.attack = 1;
	_bug.timeAttack = 2;
	_coolDownTime = 0;
	_bug.hp = 5;
	_bug.x = x;
	_bug.y = y;

	_bug.crtI = i;
	_bug.crtJ = j;

	_bug.target = 0;
	_bug.isAttack = false;
	_bug.isMoving = false;
	_bug.seed = false;
	_bug.consume = false;

	_bug.rc = RectMakeCenter(_bug.x + BLOCKHALFSIZE, _bug.y + BLOCKHALFSIZE, _bug.img->getFrameWidth(), _bug.img->getFrameHeight());

	_bug.frameCnt = 0;
	_bug.cntDiv = 5;

	return S_OK;
}

void bug::release()
{
}

void bug::update(bool isMove)
{
	if (_bug.state != _bug.beForeState)
	{
		_bug.frameCnt = 0;
		_bug.beForeState = _bug.state;
	}
	/*
	if (_bug.state != MON_DIE && _bug.state != MON_DYING)
	{
		if (isMove) move();
		attack();
	}

	*/
	imgChange();
	frameCnt();
	die();
}

void bug::render()
{
	_bug.img->frameRender(getMemDC(), CAMERA->getUnitViewX(_bug.rc.left),
		CAMERA->getUnitViewY(_bug.rc.top - 1), _bug.frameCnt, 0);
}

void bug::frameCnt()
{
	_bug.rc = RectMakeCenter(_bug.x + BLOCKHALFSIZE, _bug.y + BLOCKHALFSIZE, _bug.img->getFrameWidth(), _bug.img->getFrameHeight());

	_bug.cnt++;
	if (_bug.cnt % _bug.cntDiv == 0)
	{
		if (_bug.img->getMaxFrameX() <= _bug.frameCnt)
		{
			_bug.frameCnt = 0;

			if (_bug.state == MON_APPEAR)
			{
				_bug.state = MON_IDLE;
			}
			//else if ((_bug.state >= MON_ATTACK_LEFT && _bug.state <= MON_ATTACK_DOWN))
			//{
			//	_bug.state = _bug.bfMove;
			//}
			//else if (_bug.state == MON_IDLE)
			//{
			//	_bug.state = MON_MOVE_CHECK;
			//}
			else if (_bug.state == MON_DYING)
			{
				_bug.state = MON_DIE;
			}

			////框流捞绰 家府
			//if (MY_UTIL::inScreen(this->getMonX(), this->getMonY()))
			//{
			//	if (_bug.state >= MON_MOVE_LEFT && _bug.state <= MON_MOVE_DOWN)
			//	{
			//		SOUNDMANAGER->play("slime_move", _seVolume);
			//	}
			//	else
			//	{
			//		SOUNDMANAGER->stop("slime_move");
			//	}
			//}
		}
		else
		{
			_bug.frameCnt++;
		}
		_bug.cnt = 0;
	}
}

void bug::imgChange()
{
	if (_bug.state == MON_IDLE) _bug.img = IMAGEMANAGER->findImage("bug_idle");
}

void bug::move()
{
}

void bug::attack()
{
}

void bug::die()
{
	if (_bug.hp <= 0 && _bug.state != MON_DIE && _bug.state != MON_DYING)
	{
		_bug.state = MON_DYING;
		_bug.img = IMAGEMANAGER->findImage("bug_appear");
	}
}

void bug::checkMove()
{
}

void bug::checkMove(eMONSTERSTATE state)
{
}

void bug::checkBlock()
{
}

void bug::moveLeft()
{
}

void bug::moveRight()
{
}

void bug::moveUp()
{
}

void bug::moveDown()
{
}

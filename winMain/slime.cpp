#include "stdafx.h"
#include "slime.h"
#include "block.h"
#include "heroManager.h"

slime::slime()
{
}


slime::~slime()
{
}

HRESULT slime::init(float x, float y, int i, int j)
{
	SOUNDMANAGER->addSound("slime_attack", "monster/slime/slime_attack.mp3", false, false);

	IMAGEMANAGER->addFrameImage("slime_appear", "monster/slime/slime_appear.bmp", 228, 36, 6, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("slime_idle", "monster/slime/slime_idle.bmp", 180, 36, 5, 1, true, TRANSCOLOR);

	IMAGEMANAGER->addFrameImage("slime_move_right", "monster/slime/slime_move_right.bmp", 360, 36, 10, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("slime_move_left", "monster/slime/slime_move_left.bmp", 360, 36, 10, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("slime_move_up_down", "monster/slime/slime_up_down.bmp", 396, 36, 11, 1, true, TRANSCOLOR);

	IMAGEMANAGER->addFrameImage("slime_attack_right", "monster/slime/slime_attack_right.bmp", 114, 36, 3, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("slime_attack_left", "monster/slime/slime_attack_left.bmp", 114, 36, 3, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("slime_attack_up_down", "monster/slime/slime_attack_up_down.bmp", 228, 36, 6, 1, true, TRANSCOLOR);

	IMAGEMANAGER->addFrameImage("slime_die", "monster/slime/slime_die.bmp", 720, 36, 20, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("slime_attack_die", "monster/slime/slime_attack_die.bmp", 595, 36, 8, 1, true, TRANSCOLOR);

	_slime.name = "꿈틀이끼";

	_slime.bfMove = _slime.beForeState = _slime.state = MON_APPEAR;

	_slime.img = new image;
	_slime.img = IMAGEMANAGER->findImage("slime_appear");

	_slime.moveSpd = 0.3f;
	_slime.attack = 1;
	_slime.timeAttack = 2;
	_coolDownTime = 0;
	_slime.hp = 5;
	_slime.x = x;
	_slime.y = y;

	_slime.crtI = i;
	_slime.crtJ = j;

	_slime.target = 0;
	_slime.isAttack = false;
	_slime.isMoving = false;
	_slime.seed = false;
	_slime.consume = false;

	_slime.rc = RectMakeCenter(_slime.x + BLOCKHALFSIZE, _slime.y + BLOCKHALFSIZE, _slime.img->getFrameWidth(), _slime.img->getFrameHeight());

	_slime.frameCnt = 0;
	_slime.cntDiv = 5;


	return S_OK;
}

void slime::release()
{
}

void slime::update(bool isMove)
{
	if (_slime.state != _slime.beForeState)
	{
		_slime.frameCnt = 0;
		_slime.beForeState = _slime.state;
	}

	if (_slime.state != MON_DIE && _slime.state != MON_DYING)
	{
		if(isMove) move();
		attack();
	}

	imgChange();
	frameCnt();
	die();
}

void slime::render()
{
	_slime.img->frameRender(getMemDC(), CAMERA->getUnitViewX(_slime.rc.left),
		CAMERA->getUnitViewY(_slime.rc.top - 1), _slime.frameCnt, 0);
}

void slime::frameCnt()
{
	_slime.rc = RectMakeCenter(_slime.x + BLOCKHALFSIZE, _slime.y + BLOCKHALFSIZE, _slime.img->getFrameWidth(), _slime.img->getFrameHeight());

	_slime.cnt++;
	if (_slime.cnt % _slime.cntDiv == 0)
	{
		if (_slime.img->getMaxFrameX() <= _slime.frameCnt)
		{
			_slime.frameCnt = 0;

			if (_slime.state == MON_APPEAR)
			{
				_slime.state = MON_IDLE;
			}
			else if ((_slime.state >= MON_ATTACK_LEFT && _slime.state <= MON_ATTACK_DOWN))
			{
				_slime.state = _slime.bfMove;
			}
			else if (_slime.state == MON_IDLE)
			{
				_slime.state = MON_MOVE_CHECK;
			}
			else if (_slime.state == MON_DYING)
			{
				_slime.state = MON_DIE;
			}

			//움직이는 소리
			if (MY_UTIL::inScreen(this->getMonX(), this->getMonY()))
			{
				if (_slime.state >= MON_MOVE_LEFT && _slime.state <= MON_MOVE_DOWN)
				{
					SOUNDMANAGER->play("slime_move", _seVolume);
				}
				else
				{
					SOUNDMANAGER->stop("slime_move");
				}
			}
		}
		else
		{
			_slime.frameCnt++;
		}
		_slime.cnt = 0;
	}
}

void slime::attack()
{
	float disX = 0;
	float disY = 0;

	if (_slime.state != MON_DIE && _slime.state != MON_DYING)
	{
		for (int i = 0; i < _hm->getHeroSize(); i++)
		{
			disX = this->getMonX() - _hm->getVHero()[i]->getHeroX();
			disY = this->getMonY() - _hm->getVHero()[i]->getHeroY();

			if ((disY >= -10 && disY <= 10) && (disX <= -BLOCKHALFSIZE && disX >= -BLOCKSIZE) && !_slime.isAttack) //우
			{
				if (_slime.state >= MON_MOVE_LEFT && _slime.state <= MON_MOVE_DOWN) _slime.bfMove = _slime.state;
				_slime.target = i;
				_slime.state = MON_ATTACK_RIGHT;
				_slime.isAttack = false;
			}
			else if ((disY >= -10 && disY <= 10) && (disX >= BLOCKHALFSIZE && disX <= BLOCKSIZE) && !_slime.isAttack) //좌
			{
				if (_slime.state >= MON_MOVE_LEFT && _slime.state <= MON_MOVE_DOWN) _slime.bfMove = _slime.state;
				_slime.target = i;
				_slime.state = MON_ATTACK_LEFT;
				_slime.isAttack = false;
			}
			else if ((disY <= -BLOCKHALFSIZE && disY >= -BLOCKSIZE) && (disX >= -10 && disX <= 10) && !_slime.isAttack) //아래
			{
				if (_slime.state >= MON_MOVE_LEFT && _slime.state <= MON_MOVE_DOWN) _slime.bfMove = _slime.state;
				_slime.target = i;
				_slime.state = MON_ATTACK_DOWN;
				_slime.isAttack = false;
			}
			else if ((disY >= BLOCKHALFSIZE && disY <= BLOCKSIZE) && (disX >= -10 && disX <= 10) && !_slime.isAttack) //위
			{
				if (_slime.state >= MON_MOVE_LEFT && _slime.state <= MON_MOVE_DOWN) _slime.bfMove = _slime.state;
				_slime.target = i;
				_slime.state = MON_ATTACK_UP;
				_slime.isAttack = false;
			}
		}
	}

	if (_slime.state >= MON_ATTACK_LEFT && _slime.state <= MON_ATTACK_DOWN)
	{
		_coolDownTime += TIMEMANAGER->getElapsedTime();

		_slime.img = IMAGEMANAGER->findImage("slime_idle");

		if (_hm->getVHero()[_slime.target]->getHeroState() == HERO_DIE)
		{
			_slime.isAttack = false;
			_slime.state = MON_IDLE;
		}

		if (_slime.timeAttack < _coolDownTime && (_slime.state >= MON_ATTACK_LEFT && _slime.state <= MON_ATTACK_DOWN))
		{
			if (_slime.isAttack) return;

			EFFECTMANAGER->play("hero_damage_effect", _hm->getVHero()[_slime.target]->getHeroX(), _hm->getVHero()[_slime.target]->getHeroY());

			if (_slime.state == MON_ATTACK_RIGHT)
			{
				_slime.frameCnt = 0;
				_slime.cnt = 0;
				_slime.img = IMAGEMANAGER->findImage("slime_attack_right");
			}
			else if (_slime.state == MON_ATTACK_LEFT)
			{
				_slime.frameCnt = 0;
				_slime.cnt = 0;
				_slime.img = IMAGEMANAGER->findImage("slime_attack_left");
			}
			else if (_slime.state == MON_ATTACK_UP || _slime.state == MON_ATTACK_DOWN)
			{
				_slime.frameCnt = 0;
				_slime.cnt = 0;
				_slime.img = IMAGEMANAGER->findImage("slime_attack_up_down");
			}

			if (MY_UTIL::inScreen(this->getMonX(), this->getMonY()))
			{
				SOUNDMANAGER->play("slime_attack", _seVolume);
			}
			else
			{
				SOUNDMANAGER->stop("slime_attack");
			}

			_hm->getVHero()[_slime.target]->setHeroHP(_slime.attack);
			_slime.isAttack = true;
			_coolDownTime = 0;
		}
		else _slime.isAttack = false;
	}
}

void slime::die()
{
	if (_slime.hp <= 0 && _slime.state != MON_DIE && _slime.state != MON_DYING)
	{
		_slime.state = MON_DYING;
		_slime.img = IMAGEMANAGER->findImage("slime_attack_die");
	}
}


void slime::move()
{
	if (_slime.state == MON_MOVE_CHECK) checkMove();

	if (_slime.state == MON_MOVE_RIGHT) _slime.x += _slime.moveSpd;
	else if (_slime.state == MON_MOVE_LEFT) _slime.x -= _slime.moveSpd;
	else if (_slime.state == MON_MOVE_UP) _slime.y -= _slime.moveSpd;
	else if (_slime.state == MON_MOVE_DOWN) _slime.y += _slime.moveSpd;

	if (_slime.state >= MON_MOVE_LEFT && _slime.state <= MON_MOVE_DOWN)
	{
		if ((this->getMonX() == _block->getCBlockX(_slime.nxtJ, _slime.nxtI)
			&& (_slime.state == MON_MOVE_RIGHT || _slime.state == MON_MOVE_LEFT)) ||
			(this->getMonY() == _block->getCBlockY(_slime.nxtJ, _slime.nxtI)
				&& (_slime.state == MON_MOVE_UP || _slime.state == MON_MOVE_DOWN)))
		{
			_slime.crtJ = _slime.nxtJ;
			_slime.crtI = _slime.nxtI;
		}
		checkBlock();
	}
}

void slime::checkMove()
{
	if (_block->getBlockState(_slime.crtJ, _slime.crtI + 1) == UNDERGROUND) moveRight();
	else if (_block->getBlockState(_slime.crtJ + 1, _slime.crtI) == UNDERGROUND) moveDown();
	else if (_block->getBlockState(_slime.crtJ, _slime.crtI - 1) == UNDERGROUND) moveLeft();
	else if (_block->getBlockState(_slime.crtJ - 1, _slime.crtI) == UNDERGROUND) moveUp();
}

void slime::checkMove(eMONSTERSTATE state)
{
	int rndNum;

	bool left, right, up, down = false;

	if (_block->getBlockState(_slime.crtJ, _slime.crtI - 1) == UNDERGROUND) left = true;
	else left = false;
	if (_block->getBlockState(_slime.crtJ, _slime.crtI + 1) == UNDERGROUND) right = true;
	else right = false;
	if (_block->getBlockState(_slime.crtJ - 1, _slime.crtI) == UNDERGROUND) up = true;
	else up = false;
	if (_block->getBlockState(_slime.crtJ + 1, _slime.crtI) == UNDERGROUND) down = true;
	else down = false;

	if (state == MON_MOVE_LEFT)
	{
		if (!left && right && !up && !down)
		{
			moveRight();
		}
		else if (!left && right && up && down)
		{
			rndNum = RND->getInt(3);

			if (rndNum == 0) moveRight();
			else if (rndNum == 1) moveUp();
			else if (rndNum == 2) moveDown();
		}
		else if (!left && right && !up && down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveRight();
			else if (rndNum == 1) moveDown();
		}
		else if (!left && right && up && !down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveRight();
			else if (rndNum == 1) moveUp();
		}
	}
	else if (state == MON_MOVE_RIGHT)
	{
		if (left && !right && !up && !down)
		{
			moveLeft();
		}
		else if (left && !right && up && down)
		{
			rndNum = RND->getInt(3);

			if (rndNum == 0) moveLeft();
			else if (rndNum == 1) moveUp();
			else if (rndNum == 2) moveDown();
		}
		else if (left && !right && !up && down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveLeft();
			else if (rndNum == 1) moveDown();
		}
		else if (left && !right && up && !down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveLeft();
			else if (rndNum == 1) moveUp();
		}
	}
	else if (state == MON_MOVE_UP)
	{
		if (!left && !right && !up && down)
		{
			moveDown();
		}
		else if (left && right && !up && down)
		{
			rndNum = RND->getInt(3);

			if (rndNum == 0) moveDown();
			else if (rndNum == 1) moveLeft();
			else if (rndNum == 2) moveRight();
		}
		else if (!left && right && !up && down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveDown();
			else if (rndNum == 1) moveRight();
		}
		else if (left && !right && !up && down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveDown();
			else if (rndNum == 1) moveLeft();
		}
	}
	else if (state == MON_MOVE_DOWN)
	{
		if (!left && !right && up && !down)
		{
			moveUp();
		}
		else if (left && right && up && !down)
		{
			rndNum = RND->getInt(3);

			if (rndNum == 0) moveUp();
			else if (rndNum == 1) moveLeft();
			else if (rndNum == 2) moveRight();
		}
		else if (!left && right && up && !down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveUp();
			else if (rndNum == 1) moveRight();
		}
		else if (left && !right && up && !down)
		{
			rndNum = RND->getInt(2);

			if (rndNum == 0) moveUp();
			else if (rndNum == 1) moveLeft();
		}
	}
}

void slime::checkBlock()
{
	//if 블럭이 있으면 state를 바꿔서 갈 길을 다시 찾아준다.
	//else 앞에 블럭이 없는 길이라면 가던 길로 계속 가게한다.
	switch (_slime.state)
	{
	case MON_MOVE_LEFT:
		if (_block->getBlockState(_slime.crtJ, _slime.crtI - 1) != UNDERGROUND) checkMove(MON_MOVE_LEFT);
		else _slime.nxtI = _slime.crtI - 1;
		break;
	case MON_MOVE_RIGHT:
		if (_block->getBlockState(_slime.crtJ, _slime.crtI + 1) != UNDERGROUND) checkMove(MON_MOVE_RIGHT);
		else _slime.nxtI = _slime.crtI + 1;
		break;
	case MON_MOVE_UP:
		if (_block->getBlockState(_slime.crtJ - 1, _slime.crtI) != UNDERGROUND) checkMove(MON_MOVE_UP);
		else _slime.nxtJ = _slime.crtJ - 1;
		break;
	case MON_MOVE_DOWN:
		if (_block->getBlockState(_slime.crtJ + 1, _slime.crtI) != UNDERGROUND) checkMove(MON_MOVE_DOWN);
		else _slime.nxtJ = _slime.crtJ + 1;
		break;
	default:
		break;
	}
}

void slime::moveLeft()
{
	_slime.state = MON_MOVE_LEFT;
	_slime.nxtJ = _slime.crtJ;
	_slime.nxtI = _slime.crtI - 1;
}

void slime::moveRight()
{
	_slime.state = MON_MOVE_RIGHT;
	_slime.nxtJ = _slime.crtJ;
	_slime.nxtI = _slime.crtI + 1;
}

void slime::moveUp()
{
	_slime.state = MON_MOVE_UP;
	_slime.nxtJ = _slime.crtJ - 1;
	_slime.nxtI = _slime.crtI;
}

void slime::moveDown()
{
	_slime.state = MON_MOVE_DOWN;
	_slime.nxtJ = _slime.crtJ + 1;
	_slime.nxtI = _slime.crtI;
}

void slime::imgChange()
{
	if (_slime.state == MON_IDLE) _slime.img = IMAGEMANAGER->findImage("slime_idle");
	else if (_slime.state == MON_MOVE_LEFT) _slime.img = IMAGEMANAGER->findImage("slime_move_left");
	else if (_slime.state == MON_MOVE_RIGHT) _slime.img = IMAGEMANAGER->findImage("slime_move_right");
	else if (_slime.state == MON_MOVE_UP) _slime.img = IMAGEMANAGER->findImage("slime_move_up_down");
	else if (_slime.state == MON_MOVE_DOWN) _slime.img = IMAGEMANAGER->findImage("slime_move_up_down");
}
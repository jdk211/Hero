#include "stdafx.h"
#include "stage_1_hero.h"
#include "unitManager.h"
#include "block.h"
#include "maou_play.h"

stage_1_hero::stage_1_hero()
{
}


stage_1_hero::~stage_1_hero()
{
}

HRESULT stage_1_hero::init(float x, float y, int i, int j)
{
	IMAGEMANAGER->addFrameImage("hero_1_idle", "hero/stage_1/hero_1_idle.bmp", 77, 57, 1, 1, true, TRANSCOLOR);

	IMAGEMANAGER->addFrameImage("hero_1_move_right", "hero/stage_1/hero_1_right.bmp", 320, 36, 6, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("hero_1_move_left", "hero/stage_1/hero_1_left.bmp", 318, 36, 6, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("hero_1_move_down", "hero/stage_1/hero_1_down.bmp", 619, 57, 8, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("hero_1_move_up", "hero/stage_1/hero_1_up.bmp", 490, 50, 7, 1, true, TRANSCOLOR);

	IMAGEMANAGER->addFrameImage("hero_1_attack_right", "hero/stage_1/hero_1_attack_right.bmp", 376, 36, 4, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("hero_1_attack_left", "hero/stage_1/hero_1_attack_left.bmp", 376, 36, 4, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("hero_1_attack_up", "hero/stage_1/hero_1_attack_up.bmp", 264, 45, 3, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("hero_1_attack_down", "hero/stage_1/hero_1_attack_down.bmp", 251, 58, 4, 1, true, TRANSCOLOR);

	SOUNDMANAGER->addSound("hero_attack", "hero/stage_1/hero_attack.mp3", false, false);

	_appearSceneImgName1 = "hero_1_move_down";
	_appearSceneImgName2 = "hero_1_move_right";

	_hero.bfMove = _hero.beForeState = _hero.state = HERO_APPEAR;

	_hero.x = x;
	_hero.y = y;
	_hero.name = "풋내기 용사 하지메";

	_hero.isAttack = false;
	_hero.targetOn = false;
	_hero.changeState = false;
	_hero.target = 0;
	_hero.attack = 1;
	_hero.frameCnt = 0;
	_hero.moveSpd = 0.5f;
	_hero.cnt = 0;
	_hero.hp = 50;
	_hero.img = IMAGEMANAGER->findImage("hero_1_idle");
	_hero.rc = RectMakeCenter(_hero.x + BLOCKHALFSIZE, _hero.y + BLOCKHALFSIZE, _hero.img->getFrameWidth(), _hero.img->getFrameHeight());

	_hero.crtI = i;
	_hero.crtJ = j;

	_targetI = 0;
	_targetJ = 0;

	return S_OK;
}

void stage_1_hero::release()
{
}

void stage_1_hero::update()
{
	if (_hero.state != HERO_APPEAR)
	{
		if (_hero.state != _hero.beForeState)
		{
			_hero.frameCnt = 0;
			_hero.beForeState = _hero.state;
		}

		if (_hero.state != HERO_DIE)
		{
			if (!_hero.targetOn)
			{
				move();
				stateMove();
				maouArrest();
			}
			//else returnMove();

			attack();
		}

		imgChange();
		frameCnt();
		die();
	}
}

void stage_1_hero::render()
{
	_hero.img->frameRender(getMemDC(), CAMERA->getUnitViewX(_hero.rc.left),
		CAMERA->getUnitViewY(_hero.rc.top - 1), _hero.frameCnt, 0);

	MY_UTIL::TestText(getMemDC(), 100, 100, _hero.state);
	MY_UTIL::TestText(getMemDC(), 100, 120, _hero.changeState);
}

void stage_1_hero::frameCnt()
{
	_hero.rc = RectMakeCenter(_hero.x + BLOCKHALFSIZE, _hero.y + BLOCKHALFSIZE, _hero.img->getFrameWidth(), _hero.img->getFrameHeight());

	_hero.cnt++;
	if (_hero.cnt % 10 == 0)
	{
		if (_hero.img->getMaxFrameX() <= _hero.frameCnt)
		{
			_hero.frameCnt = 0;

			if (_hero.state == HERO_APPEAR)
			{
				_hero.state = HERO_IDLE;
				_hero.isAttack = false;
			}
			else if ((_hero.state >= HERO_ATTACK_LEFT && _hero.state <= HERO_ATTACK_DOWN))
			{
				_hero.state = _hero.bfMove;
				_hero.isAttack = false;
			}
			else if (_hero.state >= HERO_MOVE_LEFT && _hero.state <= HERO_MOVE_DOWN)
			{
				_hero.isAttack = false;
			}
			else if (_hero.state == HERO_IDLE)
			{
				_hero.state = HERO_MOVE_CHECK;
				_hero.isAttack = false;
			}
		}
		else
		{
			_hero.frameCnt++;
		}
		_hero.cnt = 0;
	}
}

void stage_1_hero::imgChange()
{
	if (_hero.state == HERO_IDLE) _hero.img = IMAGEMANAGER->findImage("hero_1_idle");
	else if (_hero.state == HERO_MOVE_LEFT) _hero.img = IMAGEMANAGER->findImage("hero_1_move_left");
	else if (_hero.state == HERO_MOVE_RIGHT) _hero.img = IMAGEMANAGER->findImage("hero_1_move_right");
	else if (_hero.state == HERO_MOVE_UP) _hero.img = IMAGEMANAGER->findImage("hero_1_move_up");
	else if (_hero.state == HERO_MOVE_DOWN) _hero.img = IMAGEMANAGER->findImage("hero_1_move_down");

	else if (_hero.state == HERO_ATTACK_LEFT) _hero.img = IMAGEMANAGER->findImage("hero_1_attack_left");
	else if (_hero.state == HERO_ATTACK_RIGHT) _hero.img = IMAGEMANAGER->findImage("hero_1_attack_right");
	else if (_hero.state == HERO_ATTACK_UP) _hero.img = IMAGEMANAGER->findImage("hero_1_attack_up");
	else if (_hero.state == HERO_ATTACK_DOWN) _hero.img = IMAGEMANAGER->findImage("hero_1_attack_down");
}

void stage_1_hero::maouArrest()
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((i == 0 && j == 0) || (i == 1 && j == -1) || (i == 1 && j == 1) || (i == -1 && j == -1) || (i == -1 && j == 1)) continue;

			if (_hero.crtI == _targetI + i && _hero.crtJ == _targetJ + j)
			{
				_hero.targetOn = true;
				_hero.state = HERO_IDLE;
				_maou->setMaouState(MAOU_ARREST);
			}
		}
	}

}

void stage_1_hero::attack()
{
	float disX = 0;
	float disY = 0;

	for (int i = 0; i < _um->getVMonster().size(); i++)
	{
		disX = this->getHeroX() - _um->getVMonster()[i]->getMonX();
		disY = this->getHeroY() - _um->getVMonster()[i]->getMonY();

		if ((disY >= -14 && disY <= 14) && (disX <= -BLOCKHALFSIZE && disX >= -BLOCKSIZE) && !_hero.isAttack) //우
		{
			if (_um->getVMonster()[i]->getMonState() == MON_DIE || _um->getVMonster()[i]->getMonState() == MON_DYING) continue;
			if (_hero.state >= HERO_MOVE_LEFT && _hero.state <= HERO_MOVE_DOWN) _hero.bfMove = _hero.state;
			_hero.state = HERO_ATTACK_RIGHT;
			_hero.target = i;
			_hero.isAttack = false;
		}
		else if ((disY >= -14 && disY <= 14) && (disX >= BLOCKHALFSIZE && disX <= BLOCKSIZE) && !_hero.isAttack) //좌
		{
			if (_um->getVMonster()[i]->getMonState() == MON_DIE || _um->getVMonster()[i]->getMonState() == MON_DYING) continue;
			if (_hero.state >= HERO_MOVE_LEFT && _hero.state <= HERO_MOVE_DOWN) _hero.bfMove = _hero.state;
			_hero.state = HERO_ATTACK_LEFT;
			_hero.target = i;
			_hero.isAttack = false;
		}
		else if ((disY <= -BLOCKHALFSIZE && disY >= -BLOCKSIZE) && (disX >= -14 && disX <= 14) && !_hero.isAttack) //아래
		{
			if (_um->getVMonster()[i]->getMonState() == MON_DIE || _um->getVMonster()[i]->getMonState() == MON_DYING) continue;
			if (_hero.state >= HERO_MOVE_LEFT && _hero.state <= HERO_MOVE_DOWN) _hero.bfMove = _hero.state;
			_hero.state = HERO_ATTACK_DOWN;
			_hero.target = i;
			_hero.isAttack = false;
		}
		else if ((disY >= BLOCKHALFSIZE && disY <= BLOCKSIZE) && (disX >= -14 && disX <= 14) && !_hero.isAttack) //위
		{
			if (_um->getVMonster()[i]->getMonState() == MON_DIE || _um->getVMonster()[i]->getMonState() == MON_DYING) continue;
			if (_hero.state >= HERO_MOVE_LEFT && _hero.state <= HERO_MOVE_DOWN) _hero.bfMove = _hero.state;
			_hero.state = HERO_ATTACK_UP;
			_hero.target = i;
			_hero.isAttack = false;
		}
	}

	if (_hero.state >= HERO_ATTACK_LEFT && _hero.state <= HERO_ATTACK_DOWN)
	{
		if (_um->getVMonster()[_hero.target]->getMonState() == MON_DYING)
		{
			_hero.isAttack = false;
			_hero.img = IMAGEMANAGER->findImage("hero_1_idle");
		}
		else if (_hero.frameCnt == 2 && (_hero.state >= HERO_ATTACK_LEFT && _hero.state <= HERO_ATTACK_DOWN))
		{
			if (_hero.isAttack) return;

			if (_um->getVMonster()[_hero.target]->getMonName() == "꿈틀이끼") EFFECTMANAGER->play("slime_damage_effect", _um->getVMonster()[_hero.target]->getMonX(), _um->getVMonster()[_hero.target]->getMonY());

			if (MY_UTIL::inScreen(this->getHeroX(), this->getHeroY()))
			{
				SOUNDMANAGER->play("hero_attack", _seVolume);
			}
			else
			{
				SOUNDMANAGER->stop("hero_attack");
			}

			_um->getVMonster()[_hero.target]->setMonHP(_hero.attack);
			_hero.isAttack = true;
		}
		else _hero.isAttack = false;
	}
}

void stage_1_hero::die()
{
	if (_hero.hp <= 0) _hero.state = HERO_DIE;
}

void stage_1_hero::returnMove()
{
	_hero.state = HERO_MOVE_UP;

	if (_hero.state == HERO_MOVE_LEFT) _hero.x -= _hero.moveSpd;
	else if (_hero.state == HERO_MOVE_DOWN) _hero.y += _hero.moveSpd;
	else if (_hero.state == HERO_MOVE_RIGHT) _hero.x += _hero.moveSpd;
	else if (_hero.state == HERO_MOVE_UP) _hero.y -= _hero.moveSpd;
}

void stage_1_hero::stateMove()
{
	if (_hero.state == HERO_MOVE_CHECK) targetMove();

	if (!_hero.changeState)
	{
		if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) == UNDERGROUND &&	// +
			_block->getBlockState(_hero.crtJ + 1, _hero.crtI) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ, _hero.crtI + 1) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ - 1, _hero.crtI) == UNDERGROUND)
		{
			if (_hero.state == HERO_MOVE_DOWN)
			{
				if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_RIGHT)
			{
				if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_LEFT)
			{
				if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if(_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_UP)
			{
				if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
			}
		}
		else if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) != UNDERGROUND && //ㅏ
			_block->getBlockState(_hero.crtJ + 1, _hero.crtI) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ, _hero.crtI + 1) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ - 1, _hero.crtI) == UNDERGROUND)
		{
			if (_hero.state == HERO_MOVE_UP)
			{
				if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_DOWN)
			{

				if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_LEFT)
			{
				if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
			}
		}
		else if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) == UNDERGROUND && //ㅓ
			_block->getBlockState(_hero.crtJ + 1, _hero.crtI) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ, _hero.crtI + 1) != UNDERGROUND &&
			_block->getBlockState(_hero.crtJ - 1, _hero.crtI) == UNDERGROUND)
		{
			if (_hero.state == HERO_MOVE_UP)
			{
				if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_DOWN)
			{
				if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_RIGHT)
			{
				if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
			}
		}
		else if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) == UNDERGROUND && // ㅗ
			_block->getBlockState(_hero.crtJ + 1, _hero.crtI) != UNDERGROUND &&
			_block->getBlockState(_hero.crtJ, _hero.crtI + 1) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ - 1, _hero.crtI) == UNDERGROUND)
		{
			if (_hero.state == HERO_MOVE_DOWN)
			{
				if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_LEFT)
			{
				if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_RIGHT)
			{
				if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockUp(_hero.crtJ, _hero.crtI))
				{
					moveUp();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
			}
		}
		else if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) == UNDERGROUND && // ㅜ
			_block->getBlockState(_hero.crtJ + 1, _hero.crtI) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ, _hero.crtI + 1) == UNDERGROUND &&
			_block->getBlockState(_hero.crtJ - 1, _hero.crtI) != UNDERGROUND)
		{
			if (_hero.state == HERO_MOVE_RIGHT)
			{
				if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_LEFT)
			{
				if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
				else if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
			}
			else if (_hero.state == HERO_MOVE_UP)
			{
				if (_block->getBlockRight(_hero.crtJ, _hero.crtI))
				{
					moveRight();
					_hero.changeState = true;
				}
				else if (_block->getBlockLeft(_hero.crtJ, _hero.crtI))
				{
					moveLeft();
					_hero.changeState = true;
				}
				else if (_block->getBlockDown(_hero.crtJ, _hero.crtI))
				{
					moveDown();
					_hero.changeState = true;
				}
			}
		}
	}
	if (_hero.state >= HERO_MOVE_LEFT && _hero.state <= HERO_MOVE_DOWN)
	{
		if ((this->getHeroX() == _block->getCBlockX(_hero.nxtJ, _hero.nxtI)
			&& (_hero.state == HERO_MOVE_RIGHT || _hero.state == HERO_MOVE_LEFT)) ||
			(this->getHeroY() == _block->getCBlockY(_hero.nxtJ, _hero.nxtI)
				&& (_hero.state == HERO_MOVE_UP || _hero.state == HERO_MOVE_DOWN)))
		{
			if (_hero.state == HERO_MOVE_LEFT)
			{
				_block->setBlockLeft(_hero.crtJ, _hero.crtI, false);
			}
			else if (_hero.state == HERO_MOVE_RIGHT)
			{
				_block->setBlockRight(_hero.crtJ, _hero.crtI, false);
			}
			else if (_hero.state == HERO_MOVE_DOWN)
			{
				_block->setBlockDown(_hero.crtJ, _hero.crtI, false);
			}
			else if (_hero.state == HERO_MOVE_UP)
			{
				_block->setBlockUp(_hero.crtJ, _hero.crtI, false);
			}

			_hero.changeState = false;
			
			_hero.crtJ = _hero.nxtJ;
			_hero.crtI = _hero.nxtI;
		}

		checkBlock();
	}
}

void stage_1_hero::move()
{
	if (_hero.state == HERO_MOVE_LEFT) _hero.x -= _hero.moveSpd;
	else if (_hero.state == HERO_MOVE_DOWN) _hero.y += _hero.moveSpd;
	else if (_hero.state == HERO_MOVE_RIGHT) _hero.x += _hero.moveSpd;
	else if (_hero.state == HERO_MOVE_UP) _hero.y -= _hero.moveSpd;
}

void stage_1_hero::checkBlock()
{
	//if 블럭이 있으면 state를 바꿔서 갈 길을 다시 찾아준다.
	//else 앞에 블럭이 없는 길이라면 가던 길로 계속 가게한다.
	switch (_hero.state)
	{
	case HERO_MOVE_LEFT:
		if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) != UNDERGROUND) targetMove(HERO_MOVE_LEFT);
		else _hero.nxtI = _hero.crtI - 1;
		break;
	case HERO_MOVE_RIGHT:
		if (_block->getBlockState(_hero.crtJ, _hero.crtI + 1) != UNDERGROUND) targetMove(HERO_MOVE_RIGHT);
		else _hero.nxtI = _hero.crtI + 1;
		break;
	case HERO_MOVE_UP:
		if (_block->getBlockState(_hero.crtJ - 1, _hero.crtI) != UNDERGROUND) targetMove(HERO_MOVE_UP);
		else _hero.nxtJ = _hero.crtJ - 1;
		break;
	case HERO_MOVE_DOWN:
		if (_block->getBlockState(_hero.crtJ + 1, _hero.crtI) != UNDERGROUND) targetMove(HERO_MOVE_DOWN);
		else _hero.nxtJ = _hero.crtJ + 1;
		break;
	default:
		break;
	}
}

void stage_1_hero::targetMove()
{
	if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) == UNDERGROUND) moveLeft();
	else if (_block->getBlockState(_hero.crtJ + 1, _hero.crtI) == UNDERGROUND) moveDown();
	else if (_block->getBlockState(_hero.crtJ, _hero.crtI + 1) == UNDERGROUND) moveRight();
	else if (_block->getBlockState(_hero.crtJ - 1, _hero.crtI) == UNDERGROUND) moveUp();
}

void stage_1_hero::targetMove(eHEROSTATE state)
{
	bool left, right, up, down = false;

	if (_block->getBlockState(_hero.crtJ, _hero.crtI - 1) == UNDERGROUND) left = true;
	else left = false;
	if (_block->getBlockState(_hero.crtJ, _hero.crtI + 1) == UNDERGROUND) right = true;
	else right = false;
	if (_block->getBlockState(_hero.crtJ - 1, _hero.crtI) == UNDERGROUND) up = true;
	else up = false;
	if (_block->getBlockState(_hero.crtJ + 1, _hero.crtI) == UNDERGROUND) down = true;
	else down = false;

	if (state == HERO_MOVE_LEFT)
	{
		if (!left && right && !up && !down)
		{
			moveRight();
		}
		else if (!left && right && up && down)
		{
			moveDown();
		}
		else if (!left && right && !up && down)
		{
			moveDown();
		}
		else if (!left && right && up && !down)
		{
			moveUp();
		}
	}
	else if (state == HERO_MOVE_RIGHT)
	{
		if (left && !right && !up && !down)
		{
			moveLeft();
		}
		else if (left && !right && up && down)
		{
			moveDown();
		}
		else if (left && !right && !up && down)
		{
			moveDown();
		}
		else if (left && !right && up && !down)
		{
			moveUp();
		}
	}
	else if (state == HERO_MOVE_UP)
	{
		if (!left && !right && !up && down)
		{
			moveDown();
		}
		else if (left && right && !up && down)
		{
			moveRight();
		}
		else if (!left && right && !up && down)
		{
			moveRight();
		}
		else if (left && !right && !up && down)
		{
			moveLeft();
		}

	}
	else if (state == HERO_MOVE_DOWN)
	{
		if (left && right && up && !down)
		{
			moveLeft();
		}
		else if (!left && right && up && !down)
		{
			moveRight();
		}
		else if (left && !right && up && !down)
		{
			moveLeft();
		}
		else if (!left && !right && up && !down)
		{
			moveUp();
		}
	}
}

void stage_1_hero::moveLeft()
{
	_hero.state = HERO_MOVE_LEFT;
	_hero.nxtJ = _hero.crtJ;
	_hero.nxtI = _hero.crtI - 1;
}

void stage_1_hero::moveDown()
{
	_hero.state = HERO_MOVE_DOWN;
	_hero.nxtJ = _hero.crtJ + 1;
	_hero.nxtI = _hero.crtI;
}

void stage_1_hero::moveRight()
{
	_hero.state = HERO_MOVE_RIGHT;
	_hero.nxtJ = _hero.crtJ;
	_hero.nxtI = _hero.crtI + 1;
}

void stage_1_hero::moveUp()
{
	_hero.state = HERO_MOVE_UP;
	_hero.nxtJ = _hero.crtJ - 1;
	_hero.nxtI = _hero.crtI;
}
#include "stdafx.h"
#include "pickax.h"
#include "block.h"
#include "unitManager.h"

pickax::pickax()
{
}


pickax::~pickax()
{
}

HRESULT pickax::init(int pickCnt)
{
	EFFECTMANAGER->addEffect("floor_1_break", "play/effect1.bmp", 1800, 339, 360, 339, 5, 0.05, 5);
	EFFECTMANAGER->addEffect("floor_2_break", "play/effect2.bmp", 1800, 298, 360, 298, 5, 0.05, 5);
	EFFECTMANAGER->addEffect("floor_3_break", "play/effect3.bmp", 1800, 343, 360, 343, 5, 0.05, 5);
	EFFECTMANAGER->addEffect("floor_4_break", "play/effect4.bmp", 1800, 342, 360, 342, 5, 0.05, 5);

	IMAGEMANAGER->addFrameImage("pickax", "play/pickax2.bmp", 40, 47, 1, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage("swing_pickax", "play/swing_pickax.bmp", 120, 47, 3, 1, true, TRANSCOLOR);

	SOUNDMANAGER->addSound("pickax_move", "play/pickax_move.mp3", false, false);
	SOUNDMANAGER->addSound("air_pickax", "play/air_pickax.mp3", false, false);
	SOUNDMANAGER->addSound("break_block", "play/break_block.mp3", false, false);
	SOUNDMANAGER->addSound("cant_break_block", "play/cant_break_block.mp3", false, false);

	_pick.img = new image;
	_pick.img = IMAGEMANAGER->findImage("pickax");

	_isSwing = false;

	_currentX = 31;
	_currentY = 1;

	_pick.x = _block->getBlockX(_currentX, _currentY);
	_pick.y = _block->getBlockY(_currentX, _currentY);

	_pickCnt = pickCnt;
	_isGround = false;

	return S_OK;
}

void pickax::release()
{

}

void pickax::update(bool isMaou, bool dialEnd) //true 여야 작동
{
	EFFECTMANAGER->update();

	if (isMaou)
	{
		pickaxMove();

		if (KEYMANAGER->isOnceKeyDown('A') && _pickCnt > 0)
		{
			pickaxAttack();
			_isSwing = true;
		}

		if (_isSwing)
		{
			pickFrameUpdate();
		}
	}
	else
	{
		if(dialEnd) pickaxMove();

		if (_block->getBlockState(_currentY, _currentX) == UNDERGROUND) _isGround = true;
		else _isGround = false;
	}
}

void pickax::render()
{
	EFFECTMANAGER->render();
	CAMERA->setViewX(_pick.x, _pick.y);
	_pick.img->frameRender(getMemDC(), CAMERA->getUnitViewX(_pick.x + _pick.img->getFrameWidth() / 2),
	CAMERA->getUnitViewY((_pick.y - _pick.img->getFrameHeight() / 2) - 5), _pick.img->getFrameX(), 0);
}

void pickax::pickaxMove()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_currentX -= 1;
		SOUNDMANAGER->play("pickax_move", _seVolume);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_currentX += 1;
		SOUNDMANAGER->play("pickax_move", _seVolume);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_currentY -= 1;
		SOUNDMANAGER->play("pickax_move", _seVolume);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_currentY += 1;
		SOUNDMANAGER->play("pickax_move", _seVolume);
	}

	if (_currentX < 1) _currentX = 1;
	if (_currentX > BLOCK_MAX_X - 2) _currentX = BLOCK_MAX_X - 2;
	if (_currentY < 1) _currentY = 1;
	if (_currentY > BLOCK_MAX_Y - 2) _currentY = BLOCK_MAX_Y - 2;

	_pick.x = _block->getBlockX(_currentY, _currentX);
	_pick.y = _block->getBlockY(_currentY, _currentX);
}

void pickax::pickaxAttack()
{
	_pick.img = IMAGEMANAGER->findImage("swing_pickax");

	bool isGround = false;
	int i = -1;

	while (i < 2)
	{
		if (_block->getBlockState(_currentY + i, _currentX) == UNDERGROUND) isGround = true;
		else if (_block->getBlockState(_currentY, _currentX + i) == UNDERGROUND) isGround = true;
		i++;
	}

	if (isGround && _block->getBlockState(_currentY, _currentX) != UNDERGROUND)
	{
		switch (_block->getBlockFloor(_currentY, _currentX))
		{
		case 1:
			EFFECTMANAGER->play("floor_1_break", _block->getBlockX(_currentY, _currentX) + 16, 
				_block->getBlockY(_currentY, _currentX) + 82);
			break;

		case 2:
			EFFECTMANAGER->play("floor_2_break", _block->getBlockX(_currentY, _currentX) + 16,
				_block->getBlockY(_currentY, _currentX) + 82);
			break;

		case 3:
			EFFECTMANAGER->play("floor_3_break", _block->getBlockX(_currentY, _currentX) + 16,
				_block->getBlockY(_currentY, _currentX) + 82);
			break;

		case 4:
			EFFECTMANAGER->play("floor_4_break", _block->getBlockX(_currentY, _currentX) + 16,
				_block->getBlockY(_currentY, _currentX) + 82);
			break;

		default:
			break;
		}

		if (_block->getBlockState(_currentY, _currentX - 1) == UNDERGROUND)
		{
			_block->setBlockLeft(_currentY, _currentX, true);
			_block->setBlockRight(_currentY, _currentX - 1, true);
		}
		if (_block->getBlockState(_currentY, _currentX + 1) == UNDERGROUND)
		{
			_block->setBlockRight(_currentY, _currentX, true);
			_block->setBlockLeft(_currentY, _currentX + 1, true);
		}
		if (_block->getBlockState(_currentY - 1, _currentX) == UNDERGROUND)
		{
			_block->setBlockUp(_currentY, _currentX, true);
			_block->setBlockDown(_currentY - 1, _currentX, true);
		}
		if (_block->getBlockState(_currentY + 1, _currentX) == UNDERGROUND)
		{
			_block->setBlockDown(_currentY, _currentX, true);
			_block->setBlockUp(_currentY + 1, _currentX , true);
		}

		_block->setBlockStateUnder(_currentY, _currentX);
		SOUNDMANAGER->play("break_block", _seVolume);
		
		if (_block->getBlockCnt(_currentY, _currentX) >= 3 && _block->getBlockCnt(_currentY, _currentX) < 10)
		{
			SOUNDMANAGER->play("slime_appear", _seVolume);
			_um->addSlime(_block->getBlockX(_currentY, _currentX), _block->getBlockY(_currentY, _currentX), _currentX, _currentY);
		}
		else if (_block->getBlockCnt(_currentY, _currentX) >= 10)
		{
			_um->addBug(_block->getBlockX(_currentY, _currentX), _block->getBlockY(_currentY, _currentX), _currentX, _currentY);
		}


		_pickCnt--;
	}
	else if (_block->getBlockState(_currentY, _currentX) == UNDERGROUND) SOUNDMANAGER->play("air_pickax", _seVolume);
	else if (!isGround) SOUNDMANAGER->play("cant_break_block", _seVolume);

}

void pickax::pickFrameUpdate()
{
	_pickFrameCnt++;
	if (_pickFrameCnt % 3 == 0)
	{
		if (_pick.img->getMaxFrameX() <= _pick.img->getFrameX())
		{
			_pick.img->setFrameX(0);
			_pick.img = IMAGEMANAGER->findImage("pickax");
			_isSwing = !_isSwing;
		}
		else
		{
			_pick.img->setFrameX(_pick.img->getFrameX() + 1);
		}
	}
}

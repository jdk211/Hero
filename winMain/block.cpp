#include "stdafx.h"
#include "block.h"


block::block()
{
}


block::~block()
{
}

HRESULT block::init()
{
	IMAGEMANAGER->addImage("block_shadow", "play/block/block_shadow.bmp", 48, 48, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_idle_1_1", "play/block/block_idle_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_1_1_1", "play/block/block_slime_1_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_1_1_2", "play/block/block_slime_1_1_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_1_1_1", "play/block/block_bug_1_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_1_1_2", "play/block/block_bug_1_1_2.bmp", 36, 36, true, TRANSCOLOR);

	IMAGEMANAGER->addImage("block_idle_1_2", "play/block/block_idle_1_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_1_2_1", "play/block/block_slime_1_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_1_2_2", "play/block/block_slime_1_2_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_1_2_1", "play/block/block_bug_1_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_1_2_2", "play/block/block_bug_1_2_2.bmp", 36, 36, true, TRANSCOLOR);

	IMAGEMANAGER->addImage("block_idle_2_1", "play/block/block_idle_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_2_1_1", "play/block/block_slime_2_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_2_1_2", "play/block/block_slime_2_1_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_2_1_1", "play/block/block_bug_2_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_2_1_2", "play/block/block_bug_2_1_2.bmp", 36, 36, true, TRANSCOLOR);

	IMAGEMANAGER->addImage("block_idle_2_2", "play/block/block_idle_2_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_2_2_1", "play/block/block_slime_2_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_2_2_2", "play/block/block_slime_2_2_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_2_2_1", "play/block/block_bug_2_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_2_2_2", "play/block/block_bug_2_2_2.bmp", 36, 36, true, TRANSCOLOR);

	IMAGEMANAGER->addImage("block_idle_3_1", "play/block/block_idle_3_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_3_1_1", "play/block/block_slime_3_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_3_1_2", "play/block/block_slime_3_1_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_3_1_1", "play/block/block_bug_3_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_3_1_2", "play/block/block_bug_3_1_2.bmp", 36, 36, true, TRANSCOLOR);

	IMAGEMANAGER->addImage("block_idle_3_2", "play/block/block_idle_3_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_3_2_1", "play/block/block_slime_3_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_3_2_2", "play/block/block_slime_3_2_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_3_2_1", "play/block/block_bug_3_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_3_2_2", "play/block/block_bug_3_2_2.bmp", 36, 36, true, TRANSCOLOR);

	IMAGEMANAGER->addImage("block_idle_4_1", "play/block/block_idle_4_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_4_1_1", "play/block/block_slime_4_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_4_1_2", "play/block/block_slime_4_1_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_4_1_1", "play/block/block_bug_4_1_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_4_1_2", "play/block/block_bug_4_1_2.bmp", 36, 36, true, TRANSCOLOR);

	IMAGEMANAGER->addImage("block_idle_4_2", "play/block/block_idle_4_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_4_2_1", "play/block/block_slime_4_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_slime_4_2_2", "play/block/block_slime_4_2_2.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_4_2_1", "play/block/block_bug_4_2_1.bmp", 36, 36, true, TRANSCOLOR);
	IMAGEMANAGER->addImage("block_bug_4_2_2", "play/block/block_bug_4_2_2.bmp", 36, 36, true, TRANSCOLOR);

	//블럭 시작 위치 x 36, y 252
	int startX = 0;
	int startY = 252 - 36;
	int blockSize = 36;
	int floorCnt = 0;

	for (int i = 0; i < BLOCK_MAX_Y; i++)
	{
		if ((i - 1) % 8 == 0) floorCnt++;
		for (int j = 0; j < BLOCK_MAX_X; j++)
		{
			_block[i][j].left = _block[i][j].right = _block[i][j].up = _block[i][j].down = false;

			_block[i][j].x = startX + j * blockSize;
			_block[i][j].y = startY + i * blockSize;
			_block[i][j].floor = floorCnt;
			_block[i][j].idleCnt = RND->getInt(2);
			_block[i][j].rc = RectMake(_block[i][j].x, _block[i][j].y, blockSize, blockSize);

			if (RND->getInt(10) < 3) _block[i][j].cnt = RND->getInt(11);
			else _block[i][j].cnt = 0;

			if ((i >= 1 && i < 4) && j == 31 || (i == 3 && j == 32)) _block[i][j].state = UNDERGROUND;
			else if (i == 0 || j == 0 || i == BLOCK_MAX_Y - 1 || j == BLOCK_MAX_X - 1) _block[i][j].state = BLOCK_UNKNOWN;
			else
			{
				if (_block[i][j].idleCnt == 0) _block[i][j].state = BLOCK_IDLE1;
				else if (_block[i][j].idleCnt == 1) _block[i][j].state = BLOCK_IDLE2;
			}

			_block[1][31].down = true;
			_block[2][31].down = true;
			_block[2][31].up = true;
			_block[3][31].up = true;
			_block[3][31].right = true;
			_block[3][32].left = true;

			if (_block[i][j].state == UNDERGROUND || _block[i][j].state == BLOCK_UNKNOWN) continue;

			_block[i][j].img = new image;
			_block[i][j].shadow = new image;
			_block[i][j].shadow = IMAGEMANAGER->findImage("block_shadow");

			if (_block[i][j].cnt <= 10)
			{
				switch (_block[i][j].floor)
				{
				case 1:
					if (_block[i][j].idleCnt == 0)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_1_1");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_1_1_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_1_1_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_1_1_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_1_1_2");
					}

					if (_block[i][j].idleCnt == 1)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_1_2");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_1_2_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_1_2_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_1_2_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_1_2_2");
					}
					break;
				case 2:
					if (_block[i][j].idleCnt == 0)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_2_1");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_2_1_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_2_1_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_2_1_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_2_1_2");
					}

					if (_block[i][j].idleCnt == 1)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_2_2");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_2_2_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_2_2_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_2_2_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_2_2_2");
					}
					break;
				case 3:
					if (_block[i][j].idleCnt == 0)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_3_1");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_3_1_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_3_1_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_3_1_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_3_1_2");
					}

					if (_block[i][j].idleCnt == 1)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_3_2");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_3_2_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_3_2_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_3_2_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_3_2_2");
					}																													  
					break;
				case 4:
					if (_block[i][j].idleCnt == 0)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_4_1");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_4_1_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_4_1_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_4_1_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_4_1_2");
					}

					if (_block[i][j].idleCnt == 1)
					{
						if (_block[i][j].cnt < 3) _block[i][j].img = IMAGEMANAGER->findImage("block_idle_4_2");
						else if (_block[i][j].cnt >= 3 && _block[i][j].cnt < 6)  _block[i][j].img = IMAGEMANAGER->findImage("block_slime_4_2_1");
						else if (_block[i][j].cnt >= 6 && _block[i][j].cnt < 10) _block[i][j].img = IMAGEMANAGER->findImage("block_slime_4_2_2");
						else if (_block[i][j].cnt >= 10 && _block[i][j].cnt < 13) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_4_2_1");
						else if (_block[i][j].cnt >= 13 && _block[i][j].cnt < 16) _block[i][j].img = IMAGEMANAGER->findImage("block_bug_4_2_2");
					}
					break;
				}
			}
		}
	}


	return S_OK;
}

void block::release()
{
}

void block::update()
{
}

void block::render()
{
	for (int i = 0; i < BLOCK_MAX_Y; i++)
	{
		for (int j = 0; j < BLOCK_MAX_X; j++)
		{
			/*MY_UTIL::TestText(getMemDC(), CAMERA->getObjectX(_block[i][j].x), CAMERA->getObjectY(_block[i][j].y), _block[i][j].left);
			MY_UTIL::TestText(getMemDC(), CAMERA->getObjectX(_block[i][j].x), CAMERA->getObjectY(_block[i][j].y + 20), _block[i][j].right);
			MY_UTIL::TestText(getMemDC(), CAMERA->getObjectX(_block[i][j].x + 20), CAMERA->getObjectY(_block[i][j].y), _block[i][j].up);
			MY_UTIL::TestText(getMemDC(), CAMERA->getObjectX(_block[i][j].x + 20), CAMERA->getObjectY(_block[i][j].y + 20), _block[i][j].down);*/

			if (_block[i][j].state == UNDERGROUND || _block[i][j].state == BLOCK_UNKNOWN) continue;

			_block[i][j].shadow->render(getMemDC(), CAMERA->getObjectX(_block[i][j].x - 4), CAMERA->getObjectY(_block[i][j].y) - 4);
			_block[i][j].img->render(getMemDC(), CAMERA->getObjectX(_block[i][j].x), CAMERA->getObjectY(_block[i][j].y));
		}
	}
}

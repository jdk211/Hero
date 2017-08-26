#include "stdafx.h"
#include "unitManager.h"
#include "block.h"
#include "heroManager.h"

unitManager::unitManager()
{
}


unitManager::~unitManager()
{
}

HRESULT unitManager::init()
{

	return S_OK;
}

void unitManager::release()
{
}

void unitManager::update(bool isMove)
{
	for (_viMonsterMg = _vMonsterMg.begin(); _viMonsterMg != _vMonsterMg.end(); )
	{
		if ((*_viMonsterMg)->getMonState() == MON_DIE) _viMonsterMg = _vMonsterMg.erase(_viMonsterMg);
		else
		{
			(*_viMonsterMg)->update(isMove);
			_viMonsterMg++;
		}
	}
}

void unitManager::render()
{
	for (_viMonsterMg = _vMonsterMg.begin(); _viMonsterMg != _vMonsterMg.end(); _viMonsterMg++)
	{
		if ((*_viMonsterMg)->getMonState() == MON_DIE) continue;

		(*_viMonsterMg)->render();
	}
}

void unitManager::addSlime(float x, float y, int i, int j)
{
	monster* addSlime;
	addSlime = new slime;
	addSlime->init(x, y, i, j);
	addSlime->setBlockMemoryLink(_block);
	addSlime->setHeroMemoryLink(_hm);

	_vMonsterMg.push_back(addSlime);
}

void unitManager::addBug(float x, float y, int i, int j)
{
	monster* addBug;
	addBug = new bug;
	addBug->init(x, y, i, j);
	addBug->setBlockMemoryLink(_block);
	addBug->setHeroMemoryLink(_hm);

	_vMonsterMg.push_back(addBug);
}

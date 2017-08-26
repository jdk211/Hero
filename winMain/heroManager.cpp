#include "stdafx.h"
#include "heroManager.h"
#include "block.h"
#include "unitManager.h"
#include "maou_play.h"

heroManager::heroManager()
{
}


heroManager::~heroManager()
{
}

HRESULT heroManager::init(int stageNumber)
{
	addHero(stageNumber);

	return S_OK;
}

void heroManager::release()
{
}

void heroManager::update()
{
	for (_viHeroMg = _vHeroMg.begin(); _viHeroMg != _vHeroMg.end(); )
	{
		if ((*_viHeroMg)->getHeroState() == HERO_DIE) _viHeroMg = _vHeroMg.erase(_viHeroMg);
		else
		{
			(*_viHeroMg)->update();
			_viHeroMg++;
		}
	}
}

void heroManager::render()
{
	for (_viHeroMg = _vHeroMg.begin(); _viHeroMg != _vHeroMg.end(); _viHeroMg++)
	{
		(*_viHeroMg)->render();
	}
}

void heroManager::addHero(int stageNumber)
{
	if (stageNumber == 1)
	{
		hero* addHero;
		addHero = new stage_1_hero;
		addHero->init(36 * 31, 36 * 5, 31, 1);
		addHero->setBlockMemoryLink(_block);
		addHero->setUnitManagerMemoryLink(_um);
		addHero->setMaouMemoryLink(_maou);

		_vHeroMg.push_back(addHero);
	}
}

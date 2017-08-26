#pragma once
#include "gameNode.h"
#include "hero.h"
#include "stage_1_hero.h"

class block;
class unitManager;
class maou_play;

class heroManager : public gameNode
{
private:
	vector<hero*> _vHeroMg;
	vector<hero*>::iterator _viHeroMg;

	block* _block;
	unitManager* _um;
	maou_play* _maou;

public:
	heroManager();
	~heroManager();

	HRESULT init(int stageNumber);
	void release();
	void update();
	void render();

	void addHero(int stageNumber);

	int getHeroSize() { return _vHeroMg.size(); }
	vector<hero*> getVHero() { return _vHeroMg; }

	void setBlockMemoryLink(block* linkBlock) { _block = linkBlock; }
	void setMaouMemoryLink(maou_play* maouLink) { _maou = maouLink; }
	void setUnitManagerMemoryLink(unitManager* unitManagerLink) { _um = unitManagerLink; }
};


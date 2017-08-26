#pragma once
#include "gameNode.h"
#include "monster.h"
#include "slime.h"
#include "bug.h"

class block;
class heroManager;

class unitManager : public gameNode
{
private:
	vector<monster*> _vMonsterMg;
	vector<monster*>::iterator _viMonsterMg;

	block* _block;
	heroManager* _hm;

public:
	unitManager();
	~unitManager();

	HRESULT init();
	void release();
	void update(bool isMove);
	void render();

	void addSlime(float x, float y, int i, int j);
	void addBug(float x, float y, int i, int j);
	void removeMonster(int i) { _vMonsterMg.erase(_vMonsterMg.begin() + i); }

	vector<monster*> getVMonster() { return _vMonsterMg; }
	int getVMonsterSize() { return _vMonsterMg.size(); }

	void setBlockMemoryLink(block* blockLink) { _block = blockLink; }
	void setHeroMemoryLink(heroManager* hmLink) { _hm = hmLink; }
};


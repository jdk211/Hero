#pragma once
#include "monster.h"

class slime : public monster
{
private:
	stMONSTERINFO _slime;

public:
	slime();
	~slime();

	virtual HRESULT init(float x, float y, int i, int j);
	virtual void release();
	virtual void update(bool isMove);
	virtual void render();

	virtual void frameCnt();
	virtual void imgChange();
	virtual void move();
	virtual void attack();
	virtual void die();
	//움직임 제어
	virtual void checkMove();
	virtual void checkMove(eMONSTERSTATE state);
	virtual void checkBlock();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void moveUp();
	virtual void moveDown();

	virtual float getMonX() { return (_slime.rc.left + _slime.rc.right) / 2; }
	virtual float getMonY() { return (_slime.rc.top + _slime.rc.bottom) / 2; }
	virtual int getMonHp() { return _slime.hp; }
	virtual int getMonFrameCnt() { return _slime.frameCnt; }
	virtual string getMonName() { return _slime.name; }
	virtual eMONSTERSTATE getMonState() { return _slime.state; }

	virtual void setMonHP(int i) { _slime.hp -= i; }
	virtual void setHeroMemoryLink(heroManager* hmLink) { _hm = hmLink; }
};


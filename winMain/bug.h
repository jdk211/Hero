#pragma once
#include "monster.h"
class bug : public monster
{
private:
	stMONSTERINFO _bug;

public:
	bug();
	~bug();

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

	virtual float getMonX() { return (_bug.rc.left + _bug.rc.right) / 2; }
	virtual float getMonY() { return (_bug.rc.top + _bug.rc.bottom) / 2; }
	virtual int getMonHp() { return _bug.hp; }
	virtual int getMonFrameCnt() { return _bug.frameCnt; }
	virtual string getMonName() { return _bug.name; }
	virtual eMONSTERSTATE getMonState() { return _bug.state; }

	virtual void setMonHP(int i) { _bug.hp -= i; }
	virtual void setHeroMemoryLink(heroManager* hmLink) { _hm = hmLink; }
};


#pragma once
#include "gameNode.h"

class block;
class unitManager;
class maou_play;

enum eHEROSTATE
{
	HERO_APPEAR,
	HERO_IDLE,
	HERO_MOVE_CHECK,
	HERO_MOVE_LEFT,
	HERO_MOVE_RIGHT,
	HERO_MOVE_UP,
	HERO_MOVE_DOWN,
	HERO_ATTACK_LEFT,
	HERO_ATTACK_RIGHT,
	HERO_ATTACK_UP,
	HERO_ATTACK_DOWN,
	HERO_DIE
};

class hero : public gameNode
{
protected:
	struct stHEROINFO
	{
		image* img;
		string name;
		eHEROSTATE state;
		eHEROSTATE beForeState;
		eHEROSTATE bfMove;
		RECT rc;
		bool isAttack;
		bool targetOn;	//마왕을 잡은 상태인지 true는 잡은상태, false는 아닌 상태
		bool changeState; //이동 변경이 있었는지
		int crtI, crtJ;		//현재 블럭 배열 번호
		int nxtI, nxtJ;		//다음 블럭 배열 번호
		int frameCnt;
		int cnt;
		int hp;
		int attack;
		int target;
		
		float x, y;
		float moveSpd;
	};
	block* _block;
	unitManager* _um;
	maou_play* _maou;
	
	stHEROINFO _hero;

	string _appearSceneImgName1;
	string _appearSceneImgName2;

	int _targetI, _targetJ;
	
public:
	hero();
	~hero();

	virtual HRESULT init(float x, float y, int i, int j);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void frameCnt();
	virtual void imgChange();
	virtual	void returnMove();	//마왕을 잡고 돌아오는 함수
	virtual void targetMove();	//마왕을 향해서 걸어가는 함수
	virtual void targetMove(eHEROSTATE state);	//마왕을 향해서 걸어가는 함수 2
	virtual void stateMove(); 	//현재 용사의 상태에 따라 걸어가는 함수
	virtual void move();
	virtual void checkBlock();	//움직일때 블럭 검사
	virtual void maouArrest();	//마왕 체포
	virtual void attack();
	virtual void die();

	virtual void moveLeft();
	virtual void moveDown();
	virtual void moveRight();
	virtual void moveUp();

	virtual string getApSceneName1() { return _appearSceneImgName1; }
	virtual string getApSceneName2() { return _appearSceneImgName2; }
	virtual string getHeroName() { return _hero.name; }
	virtual float getHeroX() { return (_hero.rc.left + _hero.rc.right) / 2; }
	virtual float getHeroY() { return (_hero.rc.top + _hero.rc.bottom) / 2; }
	virtual bool getIsTarget() { return _hero.targetOn; }
	virtual int getHeroHP() { return _hero.hp; }
	virtual eHEROSTATE getHeroState() { return _hero.state; }

	virtual void setHeroHP(int i) { _hero.hp -= i; }
	virtual void setHeroState(eHEROSTATE state) { _hero.state = state; }
	virtual void setHeroX(float x) { _hero.x = x; }
	virtual void setHeroY(float y) { _hero.y = y; }
	virtual void setHeroI(int i) { _hero.crtI = i; }
	virtual void setHeroJ(int j) { _hero.crtJ = j; }
	virtual void setTargetI(int i) { _targetI = i; }
	virtual void setTargetJ(int j) { _targetJ = j; }

	void setBlockMemoryLink(block* blockLink) { _block = blockLink; }
	void setMaouMemoryLink(maou_play* maouLink) { _maou = maouLink; }
	void setUnitManagerMemoryLink(unitManager* unitManagerLink) { _um = unitManagerLink; }
};


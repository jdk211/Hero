#pragma once
#include "gameNode.h"

class block;
class heroManager;

enum eMONSTERSTATE
{
	MON_APPEAR,
	MON_IDLE,
	MON_MOVE_CHECK,
	MON_MOVE_LEFT,
	MON_MOVE_RIGHT,
	MON_MOVE_UP,
	MON_MOVE_DOWN,
	MON_ATTACK_LEFT,
	MON_ATTACK_RIGHT,
	MON_ATTACK_UP,
	MON_ATTACK_DOWN,
	MON_SEED,
	MON_CONSUME,
	MON_DYING,
	MON_DIE
};

class monster : public gameNode
{
protected:
	struct stMONSTERINFO
	{
		image* img;
		eMONSTERSTATE state;
		eMONSTERSTATE beForeState;
		eMONSTERSTATE bfMove;
		RECT rc;
		string name;
		int crtI, crtJ;		//���� �� �迭 ��ȣ
		int nxtI, nxtJ;		//���� �� �迭 ��ȣ
		bool isMoving;		//�̵�������
		int cnt;			//�̹��� ������ cnt % cntDiv == 0
		int cntDiv;			//�̹��� ������ cnt % cntDiv == 0
		int frameCnt;		//�̹��� ������ ��ȣ
		int hp;				//ü��
		int attack;			//���ݷ�
		int timeAttack;		//���� ��Ÿ��
		int target;			//���� �� Ÿ��
		bool isAttack;		//����������
		bool consume;		//�̳��� ��������
		bool seed;			//�̳��� �Ѹ�����
		float x, y;			//���� ��ǥ
		float moveSpd;		//������ ���ǵ�
	};

	block* _block;
	heroManager* _hm;
	stMONSTERINFO _monster;

	float _coolDownTime;

public:
	monster();
	~monster();

	virtual HRESULT init(float x, float y, int i, int j);
	virtual void release();
	virtual void update(bool isMove);
	virtual void render();

	virtual void frameCnt();
	virtual void imgChange();
	virtual void move();
	virtual void attack();
	virtual void die();
	//������ ����
	virtual void checkMove();
	virtual void checkMove(eMONSTERSTATE state);
	virtual void checkBlock();
	virtual void left();
	virtual void right();
	virtual void up();
	virtual void down();

	virtual float getMonX() { return (_monster.rc.left + _monster.rc.right) / 2; }
	virtual float getMonY() { return (_monster.rc.top + _monster.rc.bottom) / 2; }
	virtual int getMonHp() { return _monster.hp; }
	virtual int getMonFrameCnt() { return _monster.frameCnt; }
	virtual string getMonName() { return _monster.name; }
	virtual eMONSTERSTATE getMonState() { return _monster.state; }

	virtual void setMonHP(int i) { _monster.hp -= i; }
	
	virtual void setBlockMemoryLink(block* linkBlock) { _block = linkBlock; }
	virtual void setHeroMemoryLink(heroManager* hmLink) { _hm = hmLink; }
};


#pragma once
#include "gameNode.h"
class map_object : public gameNode
{
protected:
	image* _img;
	animation* _ani;
	int _x, _y;

public:
	map_object();
	~map_object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};


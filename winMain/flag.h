#pragma once
#include "map_object.h"

class flag :public map_object
{
private:
	image* _flag1;
	image* _flag2;

public:
	flag();
	~flag();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
};


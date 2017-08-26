#pragma once
#include "map_object.h"
class king : public map_object
{
public:
	king();
	~king();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};


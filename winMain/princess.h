#pragma once
#include "map_object.h"

class princess : public map_object
{

public:
	princess();
	~princess();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
};


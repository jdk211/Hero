#pragma once
#include "singletonBase.h"

class viewCamera : public singletonBase<viewCamera>
{
private:
	float _mapWidth, _mapHeight;
	float _cameraX, _cameraY;

public:
	viewCamera();
	~viewCamera();

	HRESULT init(float width, float height);
	void update();

	void setViewX(float x, float y) { _cameraX = x; _cameraY = y; }
	float getViewStartX(); // ī�޶�X ������
	float getViewStartY(); // ī�޶�Y ������
	float getObjectX(float x);
	float getObjectY(float y);
	float getUnitViewX(float x);
	float getUnitViewY(float y);

	float getCameraX() { return _cameraX; }
	float getCameraY() { return _cameraY; }
};


#include "stdafx.h"
#include "viewCamera.h"


viewCamera::viewCamera()
{
}


viewCamera::~viewCamera()
{
}

HRESULT viewCamera::init(float width, float height)
{
	_mapWidth = width;
	_mapHeight = height;

	_cameraX = CENTERX;
	_cameraY = CENTERY;

	return S_OK;
}

void viewCamera::update()
{
	if (_cameraX < CENTERX) _cameraX = CENTERX; //哭率 场
	else if (_cameraX >= _mapWidth - CENTERX) _cameraX = _mapWidth - CENTERX;//坷弗率 场
	if (_cameraY < CENTERY) _cameraY = CENTERY;
	else if (_cameraY >= _mapHeight - CENTERY) _cameraY = _mapHeight - CENTERY;
}

float viewCamera::getViewStartX()
{
	float startX = CENTERX - _cameraX;

	return startX;
}

float viewCamera::getViewStartY()
{
	float startY = CENTERY - _cameraY;

	return startY;
}

float viewCamera::getObjectX(float x)
{
	return CENTERX - (_cameraX - x);
}

float viewCamera::getObjectY(float y)
{
	return CENTERY - (_cameraY - y);
}

float viewCamera::getUnitViewX(float x)
{
	if (_cameraX < CENTERX) return x;
	else if (_cameraX >= _mapWidth - CENTERX) return CENTERX + (CENTERX - (_mapWidth - x));
	else return CENTERX - (_cameraX - x);
}

float viewCamera::getUnitViewY(float y)
{
	if (_cameraY < CENTERY) return  y;
	else if (_cameraY >= _mapHeight - CENTERY) return CENTERY + (CENTERY - (_mapHeight - y));
	else return CENTERY - (_cameraY - y);
}


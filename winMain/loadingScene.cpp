#include "stdafx.h"
#include "loadingScene.h"

loadingScene::loadingScene()
{
}

loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	return S_OK;
}

void loadingScene::release()
{
}

void loadingScene::update()
{
}

void loadingScene::render()
{
	MY_UTIL::TextOutPlus(getMemDC(), 30, 500, "LOADING...", 24, FONTCOLOR, 1000, "µµ´ã9");
}

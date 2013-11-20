//============================================================================
// Name        : MapScene.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : MapScene in cocos2dx C++, Ansi-style
//============================================================================

#include "MapScene.h"

USING_NS_CC;


MapScene::MapScene(void)
{
}


MapScene::~MapScene(void)
{
}

MapScene* MapScene::create()
{
  MapScene* pMapScene = new MapScene();
  if(pMapScene && pMapScene->init())
  {
    pMapScene->autorelease();
    return pMapScene;
  }
  else
  {
    CC_SAFE_DELETE(pMapScene);
    return NULL;
  }
}

bool MapScene::init()
{
  
  if(!Scene::create())
  {
    return false;
  }

  mMapLayer = MapLayer::create(this);
  addChild(mMapLayer, 1);

  


  return true;
}
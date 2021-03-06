//============================================================================
// Name        : MapLayer.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : MapLayer in cocos2dx C++, Ansi-style
//============================================================================

#include "MapLayer.h"

USING_NS_CC;

MapLayer* MapLayer::create(MapScene* pMapScene)
{
  MapLayer* pMapLayer = new MapLayer();
  if(pMapLayer && pMapLayer->init(pMapScene))
  {
    pMapLayer->autorelease();
    return pMapLayer;
  }
  else
  {
    CC_SAFE_DELETE(pMapLayer);
    return NULL;
  }

}

bool MapLayer::init(MapScene* pMapScene)
{
  
  /////////////////////////
  if(!Layer::create())
  {
    return false;
  }
  //Load music
  //SoundLoader::preloadMusic();
  SoundLoader::playMusic("music/background_start.wav", true);
 
  mMapScene = pMapScene;
  addChild(BackgroundGame::create("numbers.jpg", this), 1);

  addChild(MenuStart::create(this), 2);


  return true;
}


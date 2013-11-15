//============================================================================
// Name        : MapLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : MapLayer in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __MAP_LAYER__
#define __MAP_LAYER__

#include "cocos2d.h"
#include "MapScene.h"
#include "BackgroundGame.h"
#include "MenuStart.h"
#include "ConnectServer.h"

class MapScene;
class MapLayer : public cocos2d::Layer
{
  MapScene* mMapScene;
  

public:
  MapLayer(void);
  ~MapLayer(void);
  
  static MapLayer* create(MapScene* pMapScene);
  virtual bool init(MapScene* pMapScene);
  
};

#endif
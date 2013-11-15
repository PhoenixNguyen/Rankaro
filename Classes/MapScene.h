//============================================================================
// Name        : MapScene.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : MapScene in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __MAP_SCENE__
#define __MAP_SCENE__

#include "cocos2d.h"
#include "MapLayer.h"
#include "MenuStart.h"
#include "CheckinLayer.h"
#include "ConnectServer.h"

class MapLayer;
class ConnectionLayer;
class MapScene : public cocos2d::Scene
{
  MapLayer* mMapLayer;

public:
  MapScene(void);
  ~MapScene(void);

  static MapScene* create();
  virtual bool init();
  static ConnectionLayer* mConnect;
};

#endif


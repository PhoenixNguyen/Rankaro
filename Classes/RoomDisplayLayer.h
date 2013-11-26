//============================================================================
// Name        : RoomDisplayLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : RoomDisplayLayer in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __ROOM_DISPLAY_LAYER__
#define __ROOM_DISPLAY_LAYER__

#include "cocos2d.h"
#include "BackgroundGame.h"
#include "Config.h"
#include "GameLayer.h"
#include "MapScene.h"
#include "Player.h"
#include "CheckinLayer.h"

class RoomDisplayLayer : public cocos2d::Layer
{
  cocos2d::Sprite* mSpriteList[9];

public:
  RoomDisplayLayer(void);
  ~RoomDisplayLayer(void);

  static cocos2d::Scene* scene();
  static RoomDisplayLayer* create();
  virtual bool init();

  void addRoom();
  void ccTouchesEnded(cocos2d::Set* pTouched, cocos2d::Event* pEvent);

};

#endif
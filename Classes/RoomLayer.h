//============================================================================
// Name        : RoomLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : RoomLayer in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __ROOM_LAYER__
#define __ROOM_LAYER__

#include "cocos2d.h"
#include "BackgroundGame.h"
#include "Config.h"
#include "GameLayer.h"
#include "MapScene.h"

class RoomLayer : public cocos2d::Layer
{
  static cocos2d::MenuItem* mMenuPlayer1;
  cocos2d::MenuItem* mMenuPlayer2;
  cocos2d::MenuItem* mMenuPlayer3;
  cocos2d::MenuItem* mMenuPlayer4;

  static cocos2d::Menu* mMenu;
  static RoomLayer* mLayer;
public:
  RoomLayer(void);
  ~RoomLayer(void);

  static cocos2d::Scene* scene();
  static RoomLayer* create();
  virtual bool init();

  void sendState(cocos2d::Object* pSender);

  static void setLastUsername(std::string pName);
  void addToMenu(std::string pName);
};

#endif

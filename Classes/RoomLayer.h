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
#include "Player.h"
#include "CheckinLayer.h"

class RoomLayer : public cocos2d::Layer
{
  
  static cocos2d::MenuItem* mMenuPlayer[];

  static cocos2d::Menu* mMenu;
  
  CC_SYNTHESIZE(bool, mMyself, Myself);

public:
  //List Player
  static Player* mPlayerList[];

  static int mUser;
  static RoomLayer* mLayer;
  //RoomLayer(void);
  ~RoomLayer(void);

  static cocos2d::Scene* scene();
  static RoomLayer* create();
  virtual bool init();

  void sendState(cocos2d::Object* pSender);

  static void setLastUsername(std::string pName, std::string pID);
  static void setFirstUsername();

  void addToMenu(std::string pName, std::string pID, bool pMyself );

  //State
  static void setLastState(std::string pID);
  static void setFirstState();

  //Start game
  static void startGame();

  //Room full
  static void roomFull();
};

#endif

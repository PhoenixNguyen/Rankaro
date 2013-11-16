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
  int mUser;
  
  static cocos2d::MenuItem* mMenuPlayer[];

  static cocos2d::Menu* mMenu;
  
  CC_SYNTHESIZE(bool, mMyself, Myself);
  CC_SYNTHESIZE(std::string, mMyID, MyID);
public:
  //Set player map with ID
  std::map<std::string, int> mPlayer;

  static RoomLayer* mLayer;
  RoomLayer(void);
  ~RoomLayer(void);

  static cocos2d::Scene* scene();
  static RoomLayer* create();
  virtual bool init();

  void sendState(cocos2d::Object* pSender);

  static void setLastUsername(std::string pName, std::string pID);
  void setFirstUsername();

  void addToMenu(std::string pName, std::string pID, bool pMyself );

  //State
  static void setLastState(std::string pID);
  void setFirstState();

  //Start game
  static void startGame();
};

#endif

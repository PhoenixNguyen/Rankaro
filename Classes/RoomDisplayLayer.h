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
#include "SoundLoader.h"

class RoomDisplayLayer : public cocos2d::Layer
{
  static cocos2d::Sprite* mSpriteList[9];
  static cocos2d::Sprite* mSpriteListNumber[9];
  static RoomDisplayLayer* mLayer;
  //CC_SYNTHESIZE(bool, mRoomStatus, RoomStatus);
  static bool mRoomStatus;
  static cocos2d::LabelBMFont* mLabel[9];
  static cocos2d::CCLabelTTF* mLabel2[9];
public:
  /*RoomDisplayLayer(void);
  ~RoomDisplayLayer(void);*/

  static cocos2d::Scene* scene();
  static RoomDisplayLayer* create();
  virtual bool init();

  static void addRoom();
  void ccTouchesEnded(cocos2d::Set* pTouched, cocos2d::Event* pEvent);

  static void roomStatus(bool* pBool);
  static void addSprite(int pNumber, bool pStatus = true);
  static void addNumberInRoom(int* pNumber);

  static bool getRoomStatus();
  static void setRoomStatus(bool);

  void switchLayer(cocos2d::Object* pSender);
};

#endif
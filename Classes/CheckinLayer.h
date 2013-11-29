//============================================================================
// Name        : CheckinLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : CheckinLayer in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __CHECKIN_LAYER__
#define __CHECKIN_LAYER__

#include "cocos2d.h"
#include "BackgroundGame.h"
#include "GUI\CCEditBox\CCEditBox.h"
#include "RoomLayer.h"
#include "Config.h"
#include "MapLayer.h"
#include "ConnectServer.h"
#include "RoomDisplayLayer.h"
#include "SoundLoader.h"

class ConnectionLayer;
class CheckinLayer : public cocos2d::Layer
{
  cocos2d::extension::EditBox* mEditBox;
  cocos2d::MenuItem* mSend;
public:
  ~CheckinLayer(void);

  static cocos2d::Scene* scene();
  static CheckinLayer* create();
  virtual bool init();

  void sendName(Object* pSender);

  //Init Connection
  static ConnectionLayer* mConnect;

  //switch Layer
  void switchLayer(cocos2d::Object* psender);

};

#endif
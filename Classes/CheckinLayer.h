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
#include "RoomLayer.h"
#include "Config.h"
#include "MapLayer.h"
#include "ConnectServer.h"
#include "RoomDisplayLayer.h"
#include "SoundLoader.h"
#include "cocos-ext.h"

class ConnectionLayer;
class CheckinLayer : public cocos2d::Layer , public cocos2d::extension::EditBoxDelegate
{
  cocos2d::extension::EditBox* mEditBox;
  cocos2d::MenuItem* mSend;
  cocos2d::TextFieldTTF* mTextField;
public:
  ~CheckinLayer(void);
	CheckinLayer();
  static cocos2d::Scene* scene();
  static CheckinLayer* create();
  virtual bool init();

  void sendName(Object* pSender);

  //Init Connection
  static ConnectionLayer* mConnect;

  //switch Layer
  void switchLayer(cocos2d::Object* psender);
	void addSendMenu();

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
  virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
  virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
  virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
	
};

#endif
//============================================================================
// Name        : MenuStart.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : MenuStart in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __MENU_START__
#define __MENU_START__

#include "cocos2d.h"
#include "Config.h"
#include "CheckinLayer.h"

class MenuStart : public cocos2d::MenuItem
{

public:
  MenuStart(void);
  ~MenuStart(void);

  static MenuStart* create(cocos2d::Object* pTarget);
  virtual bool init(cocos2d::Object* pTarget);

  void startGame(Object* pSender);
  void help(Object* pSender);
  void contact(Object* pSender);
  void exitGame(Object* pSender);

};

#endif
//============================================================================
// Name        : BackgroundGame.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : BackgroundGame in Cocos2d x C++, Ansi-style
//============================================================================

#ifndef __BACKGROUND_GAME__
#define __BACKGROUND_GAME__

#include "cocos2d.h"
#include "MapLayer.h"

class MapLayer;
class BackgroundGame : public cocos2d::Sprite
{
public:
  BackgroundGame(void);
  ~BackgroundGame(void);

  static BackgroundGame* create(const char* pName,cocos2d::Layer* pLayer);
  bool init(const char* pName, cocos2d::Layer* pLayer);


};

#endif
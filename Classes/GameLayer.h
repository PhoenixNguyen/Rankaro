//============================================================================
// Name        : GameLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : GameLayer in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __GAME_LAYER__
#define __GAME_LAYER__

#include "cocos2d.h"
#include "BackgroundGame.h"

class GameLayer : public cocos2d::Layer
{
public:
  GameLayer(void);
  ~GameLayer(void);

  static cocos2d::Scene* scene();
  static GameLayer* create();
  virtual bool init();

};

#endif
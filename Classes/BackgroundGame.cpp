//============================================================================
// Name        : BackgroundGame.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : BackgroundGame in Cocos2d x C++, Ansi-style
//============================================================================

#include "BackgroundGame.h"

USING_NS_CC;

BackgroundGame::BackgroundGame(void)
{
}


BackgroundGame::~BackgroundGame(void)
{
}

BackgroundGame* BackgroundGame::create(Layer* pLayer)
{
  BackgroundGame* pBackgroundGame = new BackgroundGame();
  if(pBackgroundGame && pBackgroundGame->init(pLayer))
  {
    pBackgroundGame->autorelease();
    return pBackgroundGame;

  }
  else
  {
    CC_SAFE_DELETE(pBackgroundGame);
    return NULL;
  }
}
bool BackgroundGame::init(Layer* pLayer)
{
  if(!CCSprite::initWithFile("background.jpg"))
  {
    return false;
  }

  return true;

}


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

BackgroundGame* BackgroundGame::create(const char* pName, Layer* pLayer)
{
  BackgroundGame* pBackgroundGame = new BackgroundGame();
  if(pBackgroundGame && pBackgroundGame->init(pName, pLayer))
  {
    pBackgroundGame->setPosition(Point(WIDTH/2, HEIGHT/2));
    pBackgroundGame->autorelease();
    return pBackgroundGame;

  }
  else
  {
    CC_SAFE_DELETE(pBackgroundGame);
    return NULL;
  }
}
bool BackgroundGame::init(const char* pName, Layer* pLayer)
{
  if(!Sprite::initWithFile(pName))
  {

    return false;
  }
  
  return true;

}


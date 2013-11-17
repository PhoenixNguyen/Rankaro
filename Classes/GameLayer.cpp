//============================================================================
// Name        : GameLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : GameLayer in cocos2dx C++, Ansi-style
//============================================================================


#include "GameLayer.h"

USING_NS_CC;

 GameLayer* GameLayer::mLayer = NULL;
 TMXLayer* GameLayer::mTileLayer = NULL;
 TMXTiledMap* GameLayer::mTileMap = NULL;

GameLayer::GameLayer(void)
{
}


GameLayer::~GameLayer(void)
{
}

Scene* GameLayer::scene()
{
  Scene* scene = Scene::create();
  GameLayer* layer = GameLayer::create();

  scene->addChild(layer);
  return scene;

}

GameLayer* GameLayer::create()
{
  mLayer = new GameLayer();
  if(mLayer && mLayer->init())
  {
    mLayer->autorelease();
    return mLayer;
  }
  else
  {
    CC_SAFE_DELETE(mLayer);
    return NULL;
  }
}

bool GameLayer::init()
{
  if(!Layer::create())
    return false;

  addChild(BackgroundGame::create(this), 1);

  //mTileMap = new TMXTiledMap();
  mTileMap = TMXTiledMap::create("tilemap/map.tmx");
  mTileMap->setPosition(48, 24);

  mTileLayer = mTileMap->getLayer("Layer1");
  this->addChild(mTileMap, 2);


  setNumber(456);

  setTouchEnabled(true);
  return true;
}

void GameLayer::setNumber(int pNumber)
{
  //Tach number
  int number1 = pNumber/100;
  int number2 = (pNumber%100)/10;
  int number3 = (pNumber%100)%10;

  setPositionNumber(number1, 0, 0);
  setPositionNumber(number2, 0, 1);
  setPositionNumber(number3, 0, 2);

}

void GameLayer::setPositionNumber(int pNumber, int pRow, int pColumn)
{
  String* name = String::createWithFormat("number/node%d.png", pNumber);
  Sprite* sprite = Sprite::create(name->getCString());
  sprite->setPosition(mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)));
  CCLog("SPRITE: %f %f", mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).x, mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).y);

  mLayer->addChild(sprite, 3);
}

void GameLayer::ccTouchesBegan(cocos2d::Set* pTouches, cocos2d::Event* pEvent)
{
  
}
void GameLayer::ccTouchesMoved(cocos2d::Set* pTouches, cocos2d::Event* pEvent)
{
  
}

void GameLayer::ccTouchesEnded(cocos2d::Set* pTouches, cocos2d::Event* pEvent)
{
  Touch* touch = (Touch*)pTouches->anyObject();
  Point point = touch->getLocation();

  Rect rect = CCRectMake(mTileLayer->getPositionAt(Point(0 + 1.5, 0 - 1)).x - 24, 
    mTileLayer->getPositionAt(Point(0 + 1.5, 0 - 1)).y - 24, 48, 48);
  if(rect.containsPoint(point))
  {
    CCLog("Cham");
  }
}

void GameLayer::createRect()
{
  for(int i = 0; i< MAP_X; i++)
  {
    //Hang 1
    mListRect[i] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 0 - 1)).x - 24 + TILE_X*i, 
      mTileLayer->getPositionAt(Point(i + 1.5, 0 - 1)).y - 24 - TILE_Y*2, TILE_X, TILE_Y*3);
  
    //Hang 2
    mListRect[i+MAP_X] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 3 - 1)).x - 24 + TILE_X*i, 
      mTileLayer->getPositionAt(Point(i + 1.5, 3 - 1)).y - 24 - TILE_Y*2, TILE_X, TILE_Y*3);
 
    //Hang 3
    mListRect[i+2*MAP_X] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 6 - 1)).x - 24 + TILE_X*i, 
      mTileLayer->getPositionAt(Point(i + 1.5, 6 - 1)).y - 24 - TILE_Y*2, TILE_X, TILE_Y*3);
  }
}
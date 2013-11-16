//============================================================================
// Name        : GameLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : GameLayer in cocos2dx C++, Ansi-style
//============================================================================


#include "GameLayer.h"

USING_NS_CC;

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
  GameLayer* layer = new GameLayer();
  if(layer && layer->init())
  {
    layer->autorelease();
    return layer;
  }
  else
  {
    CC_SAFE_DELETE(layer);
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

  //mTileLayer = mTileMap->layerNamed("Layer1");
  this->addChild(mTileMap, 2);

  return true;
}
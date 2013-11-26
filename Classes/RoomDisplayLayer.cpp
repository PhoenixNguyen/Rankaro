#include "RoomDisplayLayer.h"

using namespace cocos2d;

RoomDisplayLayer::RoomDisplayLayer(void)
{
}


RoomDisplayLayer::~RoomDisplayLayer(void)
{
}

Scene* RoomDisplayLayer::scene()
{
  Scene* scene = Scene::create();
  RoomDisplayLayer*  layer = RoomDisplayLayer::create();
  
  scene->addChild(layer);
  return scene;

}

RoomDisplayLayer* RoomDisplayLayer::create()
{
  RoomDisplayLayer* layer = new RoomDisplayLayer();
  if( layer && layer->init())
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

bool RoomDisplayLayer::init()
{
  if(!Layer::create())
    return false;

  addChild(BackgroundGame::create(this), 0);

  //add room to choose
  addRoom();

  setTouchEnabled(true);

  return true;
}

void RoomDisplayLayer::addRoom()
{
  for(int i= 0; i< MAX_ROOM; i++){
    String* tmp = String::createWithFormat("roomdisplay/room%d.png", i+1);
    mSpriteList[i] = Sprite::create(tmp->getCString());
    int row = i/3+1 ;
    if(row == 1)
      row = 3;
    else
      if(row == 3)
        row =1;

    mSpriteList[i]->setPosition(Point((i%3+1) *WIDTH/4 , row*HEIGHT/4));
    addChild(mSpriteList[i], 1);

  }
}

void RoomDisplayLayer::ccTouchesEnded(cocos2d::Set* pTouched, cocos2d::Event* pEvent)
{
  Touch* touch = (Touch*)pTouched->anyObject();
  Point point = touch->getLocation();

  for(int i= 0; i < MAX_ROOM; i++)
  {
    if(mSpriteList[i]->getBoundingBox().containsPoint(point))
    {
      String* tmp = String::createWithFormat("room%d", i);
      CCLog("Room: %d", i);
      //Send room

      //Switch to RoomLayer

      break;
    }
  }
}
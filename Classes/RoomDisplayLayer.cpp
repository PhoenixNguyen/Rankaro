#include "RoomDisplayLayer.h"

using namespace cocos2d;

cocos2d::Sprite* RoomDisplayLayer::mSpriteList[9] = {NULL};
RoomDisplayLayer* RoomDisplayLayer::mLayer = NULL;
bool RoomDisplayLayer::mRoomStatus = false;

//RoomDisplayLayer::RoomDisplayLayer(void)
//{
//}
//
//
//RoomDisplayLayer::~RoomDisplayLayer(void)
//{
//  for(int i=0; i< 9; i++)
//    mSpriteList[i] = NULL;
//  mLayer = NULL;
//  mRoomStatus = false;
//}

Scene* RoomDisplayLayer::scene()
{
  Scene* scene = Scene::create();
  RoomDisplayLayer*  layer = RoomDisplayLayer::create();
  
  scene->addChild(layer);
  return scene;

}

RoomDisplayLayer* RoomDisplayLayer::create()
{
  mLayer = new RoomDisplayLayer();
  if( mLayer && mLayer->init())
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
      //Neu room dang hoat dong thi khong vao duoc
      if(CheckinLayer::mConnect->mListStatus[i])
        return;

      String* tmp = String::createWithFormat("%d", i);
      CCLog("Room: %d", i);
      //Send room
      CheckinLayer::mConnect->regRoom(tmp->getCString());

      //Running
      setRoomStatus(true);
      //Switch to RoomLayer
      //Replace Scene
      CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
          1.0, RoomLayer::scene()
        );
      CCDirector::sharedDirector()->replaceScene(transition);

      break;
    }
  }
}

void RoomDisplayLayer::roomStatus(bool* pList)
{
  

  for(int i= 0; i< MAX_ROOM; i++)
  {
    if(pList[i])
      addSprite(i, false);
    else
      addSprite(i, true);
  }
}

void RoomDisplayLayer::addSprite(int pNumber, bool pStatus)
{
  mLayer->removeChild(mSpriteList[pNumber], 1);

  int row = pNumber/3+1 ;
    if(row == 1)
      row = 3;
    else
      if(row == 3)
        row =1;
  int column = pNumber%3+1;

  if(pStatus)
  {
    String* tmp = String::createWithFormat("roomdisplay/room%d.png", pNumber+1);
    mSpriteList[pNumber] = Sprite::create(tmp->getCString());
    
    mSpriteList[pNumber]->setPosition(Point(column *WIDTH/4 , row*HEIGHT/4));
    mLayer->addChild(mSpriteList[pNumber], 1);
  }
  else
  {
    mSpriteList[pNumber] = Sprite::create("roomdisplay/running.png");

    mSpriteList[pNumber]->setPosition(Point(column *WIDTH/4 , row*HEIGHT/4));
    mLayer->addChild(mSpriteList[pNumber], 1);
  }
}

bool RoomDisplayLayer::getRoomStatus()
{
  return mRoomStatus;
}

void RoomDisplayLayer::setRoomStatus(bool pStatus)
{
  mRoomStatus = pStatus;
}
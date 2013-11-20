//============================================================================
// Name        : GameLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : GameLayer in cocos2dx C++, Ansi-style
//============================================================================


#include "GameLayer.h"

USING_NS_CC;

 TMXLayer* GameLayer::mTileLayer = NULL;
 TMXTiledMap* GameLayer::mTileMap = NULL;
 GameLayer* GameLayer::mLayer = NULL;

 CaculateScore* GameLayer::mCal = NULL;

 LabelBMFont* GameLayer::mLabel = NULL;

 int GameLayer::mTurn = 0;
 int GameLayer::mNumber = 0;

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

  mNumber = 0;
  //Khoi tao mang score
  mCal = new CaculateScore();

  addChild(BackgroundGame::create(this), 1);

  mTileMap = TMXTiledMap::create("tilemap/map.tmx");
  mTileMap->setPosition(48, 24);

  mTileLayer = mTileMap->getLayer("Layer1");
  this->addChild(mTileMap, 2);

  createRect();
  
  //Khoi tao number dau tien
  //setNumber(MapScene::mConnect->getNumber());

  setTouchEnabled(true);
  return true;
}

int GameLayer::getNumber()
{
  return mNumber;
}
void GameLayer::setNumber(int pNumber)
{
  mNumber = pNumber;
  

  //Tach number
  int number1 = pNumber/100;
  int number2 = (pNumber%100)/10;
  int number3 = (pNumber%100)%10;

  /*setPositionNumber(number1, 0, 0);
  setPositionNumber(number2, 0, 1);
  setPositionNumber(number3, 0, 2);*/

}

void GameLayer::setPositionNumber(int pNumber, int pRow, int pColumn)
{
  for(int i= 0; i< RoomLayer::mUser; i++)
  {
    //Get MySelf
    if(RoomLayer::mPlayerList[i]->getMySelf())
    {
      if(RoomLayer::mPlayerList[i]->getPlayerScoreArray(pRow, pColumn) != -1)
        return;
      RoomLayer::mPlayerList[i]->setPlayerScoreArray(pNumber, pRow, pColumn);

      String* name = String::createWithFormat("number/node%d.png", pNumber);
      Sprite* sprite = Sprite::create(name->getCString());
      sprite->setPosition(mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)));
      //CCLog("SPRITE: %f %f", mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).x, mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).y);
  

      mLayer->addChild(sprite, 3);
      //Tang so turn. turn hien tai = mTurn/3 -1
      mTurn++;

      int score = mCal->detection(RoomLayer::mPlayerList[i]->getPlayerScoreArray());
      RoomLayer::mPlayerList[i]->setScore(score);

      CCLog("SCORE: %d", RoomLayer::mPlayerList[i]->getScore());
      viewScore();

      //Send MyPosition
      MapScene::mConnect->sendPosition(RoomLayer::mPlayerList[i]->getID(), 
        std::to_string(pNumber), std::to_string(pRow), std::to_string(pColumn));

      //Thoat
      break;
    }
  }
}

void GameLayer::ccTouchesBegan(cocos2d::Set* pTouches, cocos2d::Event* pEvent)
{
  
}
void GameLayer::ccTouchesMoved(cocos2d::Set* pTouches, cocos2d::Event* pEvent)
{
  
}

void GameLayer::ccTouchesEnded(cocos2d::Set* pTouches, cocos2d::Event* pEvent)
{
  if(mTurn == (MapScene::mConnect->mTurn)*3)
    return;

  Touch* touch = (Touch*)pTouches->anyObject();
  Point point = touch->getLocation();

  //Tach number
  int number1 = getNumber()/100;
  int number2 = (getNumber()%100)/10;
  int number3 = (getNumber()%100)%10;

  for(int i= 0; i< MAP_X*3; i++)
  {
    if(mListRect[i].containsPoint(point))
    {
      if(i< MAP_X)
      {
        setPositionNumber(number1, i, 0);
        setPositionNumber(number2, i, 1);
        setPositionNumber(number3, i, 2);
      }
      
      if(i>= MAP_X && i< 2*MAP_X)
      {
        setPositionNumber(number1, i-9, 3);
        setPositionNumber(number2, i-9, 4);
        setPositionNumber(number3, i-9, 5);
      }
        
      if(i>= 2*MAP_X && i< 3*MAP_X)
      {
        setPositionNumber(number1, i-18, 6);
        setPositionNumber(number2, i-18, 7);
        setPositionNumber(number3, i-18, 8);
      }
      
    }
  }
  /*Rect rect = CCRectMake(mTileLayer->getPositionAt(Point(1 + 1.5, 0 - 1)).x - 24, 
    mTileLayer->getPositionAt(Point(1 + 1.5, 0 - 1)).y - 24 - 48*2, 48, 48*3);
  if(rect.containsPoint(point))
  {
    CCLog("Cham");
  }*/
}

void GameLayer::createRect()
{
  for(int i = 0; i< MAP_X; i++)
  {
    //Hang 1
    mListRect[i] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 0 - 1)).x - TILE_X/2, 
      mTileLayer->getPositionAt(Point(i + 1.5, 0 - 1)).y - TILE_Y/2 - TILE_Y*2, TILE_X, TILE_Y*3);
  
    //Hang 2
    mListRect[i+MAP_X] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 3 - 1)).x - TILE_X/2, 
      mTileLayer->getPositionAt(Point(i + 1.5, 3 - 1)).y - TILE_Y/2 - TILE_Y*2, TILE_X, TILE_Y*3);
 
    //Hang 3
    mListRect[i+2*MAP_X] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 6 - 1)).x - TILE_X/2, 
      mTileLayer->getPositionAt(Point(i + 1.5, 6 - 1)).y - TILE_Y/2 - TILE_Y*2, TILE_X, TILE_Y*3);
  }
}

void GameLayer::viewScore()
{
  //Sort with score
  setSTT();
  String* player0;
  String* player1;
  String* player2;
  String* player3;

  LabelBMFont* label0;
  LabelBMFont* label1;
  LabelBMFont* label2;
  LabelBMFont* label3;

  for(int i= 0; i< RoomLayer::mUser; i++)
  {
    //Get MySelf
    switch(RoomLayer::mPlayerList[i]->getSTT())
    {
 
    case 0:
      player0 = String::createWithFormat("%s :: %d", RoomLayer::mPlayerList[i]->getName().c_str(), 
                                                            RoomLayer::mPlayerList[i]->getScore());
      //CCLog("SCORE: %s", player->getCString());
      //LabelBMFont* label0;
      mLayer->removeChild(label0);
      label0 = LabelBMFont::create(player0->getCString(), "fonts/Arial.fnt");
	    label0->setScale(0.5);

      label0->setPosition(Point(3*WIDTH/4, 3*HEIGHT/4));

      mLayer->addChild(label0, 2);
      label0->runAction(ScaleTo::create(0.5, 1.0) );

      break;

    case 1:
      player1 = String::createWithFormat("%s :: %d", RoomLayer::mPlayerList[i]->getName().c_str(), 
                                                            RoomLayer::mPlayerList[i]->getScore());
      //CCLog("SCORE: %s", player->getCString());
      //LabelBMFont* label1;
      mLayer->removeChild(label1);
      label1 = LabelBMFont::create(player1->getCString(), "fonts/Arial.fnt");
	    label1->setScale(0.5);

      label1->setPosition(Point(3*WIDTH/4, 3*HEIGHT/4 -100));

      mLayer->addChild(label1, 2);
      label1->runAction(ScaleTo::create(0.5, 1.0) );

      break;
    case 2:
      player2 = String::createWithFormat("%s :: %d", RoomLayer::mPlayerList[i]->getName().c_str(), 
                                                            RoomLayer::mPlayerList[i]->getScore());
      //CCLog("SCORE: %s", player->getCString());
      //LabelBMFont* label2;
      mLayer->removeChild(label2);
      label2 = LabelBMFont::create(player2->getCString(), "fonts/Arial.fnt");
	    label2->setScale(0.5);

      label2->setPosition(Point(3*WIDTH/4, 3*HEIGHT/4 - 200));

      mLayer->addChild(label2, 2);
      label2->runAction(ScaleTo::create(0.5, 1.0) );

      break;
    case 3:
      player3 = String::createWithFormat("%s :: %d", RoomLayer::mPlayerList[i]->getName().c_str(), 
                                                            RoomLayer::mPlayerList[i]->getScore());
      //CCLog("SCORE: %s", player->getCString());
      //LabelBMFont* label3;
      mLayer->removeChild(label3);
      label3 = LabelBMFont::create(player3->getCString(), "fonts/Arial.fnt");
	    label3->setScale(0.5);

      label3->setPosition(Point(3*WIDTH/4, 3*HEIGHT/4 - 300));

      mLayer->addChild(label3, 2);
      label3->runAction(ScaleTo::create(0.5, 1.0) );

      break;
    }
  }
}

void GameLayer::setPositionPlayer(std::string pID, std::string pNumber, std::string pRow, std::string pColumn)
{
  for(int i= 0; i< RoomLayer::mUser; i++)
  {
    if(RoomLayer::mPlayerList[i]->getID() == pID)
    {
      
      RoomLayer::mPlayerList[i]->setPlayerScoreArray(std::stoi(pNumber), std::stoi(pRow), std::stoi(pColumn));
      RoomLayer::mPlayerList[i]->setScore(mCal->detection(RoomLayer::mPlayerList[i]->getPlayerScoreArray()));

      viewScore();
      //thoat
      break;
    }

  }
}

void GameLayer::setSTT()
{

  for(int i= 0; i < RoomLayer::mUser-2 ; i++)
  {
    int max = i;
    for(int j = i+1; j < RoomLayer::mUser-1; j++)
      if(RoomLayer::mPlayerList[j]->getScore() > RoomLayer::mPlayerList[max]->getScore())
      {
        max = j;
      }
      
      
     RoomLayer::mPlayerList[max]->setSTT(i);
     RoomLayer::mPlayerList[i]->setSTT(max);
     if(i == max)
       RoomLayer::mPlayerList[i+1]->setSTT(i+1);
  }

}
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
 CaculateScore* GameLayer::mCal = NULL;
 int GameLayer::mMyScore[MAP_X][MAP_Y] = {NULL};

 LabelBMFont* GameLayer::mLabel = NULL;
 Player* GameLayer::mPlayer = NULL;

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
  
  //Khoi tao mang score
  int* p;
  p = (int*)mMyScore;
  for(int i= 0; i< MAP_X*MAP_Y; i++)
    *(p+i) = -1;
  mPlayer = new Player();
  mPlayer->setName("HP");
  mPlayer->setID("123");
  
  CCLog("ID %s", mPlayer->getID());

  mCal = new CaculateScore();
  /*int score = mCal->detection(mMyScore);
  CCLog("SCORE: %d", score);*/

  addChild(BackgroundGame::create(this), 1);

  //mTileMap = new TMXTiledMap();
  mTileMap = TMXTiledMap::create("tilemap/map.tmx");
  mTileMap->setPosition(48, 24);

  mTileLayer = mTileMap->getLayer("Layer1");
  this->addChild(mTileMap, 2);

  createRect();
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

  /*setPositionNumber(number1, 0, 0);
  setPositionNumber(number2, 0, 1);
  setPositionNumber(number3, 0, 2);*/

}

void GameLayer::setPositionNumber(int pNumber, int pRow, int pColumn)
{
  if(mPlayer->getPlayerScoreArray(pRow, pColumn) != -1/*mMyScore[pRow][pColumn] != -1*/)
    return;
  //mMyScore[pRow][pColumn] = pNumber;
  mPlayer->setPlayerScoreArray(pNumber, pRow, pColumn);

  String* name = String::createWithFormat("number/node%d.png", pNumber);
  Sprite* sprite = Sprite::create(name->getCString());
  sprite->setPosition(mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)));
  //CCLog("SPRITE: %f %f", mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).x, mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).y);
  

  mLayer->addChild(sprite, 3);

  int score = mCal->detection(mPlayer->getPlayerScoreArray());
  mPlayer->setScore(score);

  CCLog("SCORE: %d", mPlayer->getScore());
  viewScore(mPlayer/*"HP", score*/);
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

  for(int i= 0; i< MAP_X*3; i++)
  {
    if(mListRect[i].containsPoint(point))
    {
      if(i< MAP_X)
      {
        setPositionNumber(6, i, 0);
        setPositionNumber(7, i, 1);
        setPositionNumber(9, i, 2);
      }
      
      if(i>= MAP_X && i< 2*MAP_X)
      {
        setPositionNumber(6, i-9, 3);
        setPositionNumber(7, i-9, 4);
        setPositionNumber(9, i-9, 5);
      }
        
      if(i>= 2*MAP_X && i< 3*MAP_X)
      {
        setPositionNumber(6, i-18, 6);
        setPositionNumber(7, i-18, 7);
        setPositionNumber(9, i-18, 8);
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

void GameLayer::viewScore(Player* pPlayer)
{
  
  mLayer->removeChild(mLabel);
  String* player = String::createWithFormat("%s :: %d", mPlayer->getName(), mPlayer->getScore());
  //CCLog("SCORE: %s", player->getCString());

  mLabel = LabelBMFont::create(player->getCString(), "fonts/Arial.fnt");
	mLabel->setScale(0.5);

  mLabel->setPosition(Point(3*WIDTH/4, 3*HEIGHT/4));

  mLayer->addChild(mLabel, 2);
  mLabel->runAction(ScaleTo::create(0.5, 1.0) );
}
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

 LabelBMFont* GameLayer::mLabel[4] = {NULL};

 CaculateScore* GameLayer::mCal = NULL;

 int GameLayer::mTurn = 0;
 int GameLayer::mNumber = 0;

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

  SoundLoader::playMusic("music/background_game.wav", true);

  mNumber = 0;
  //Khoi tao mang score
  mCal = new CaculateScore();

  addChild(BackgroundGame::create("fight.jpg", this), 1);

  mTileMap = TMXTiledMap::create("tilemap/map.tmx");
  mTileMap->setPosition(48, 24);

  mTileLayer = mTileMap->getLayer("Layer1");
  this->addChild(mTileMap, 2);

  createRect();
  
  //Khoi tao number dau tien
  //setNumber(MapScene::mConnect->getNumber());
  setName();
  exitGame();
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

  String* name1 = String::createWithFormat("number/node%d.png", number1);
  Sprite* sprite1 = Sprite::create(name1->getCString());
  sprite1->setPosition(Point(TILE_X*(MAP_X+2.5), TILE_Y + TILE_Y*2));

  String* name2 = String::createWithFormat("number/node%d.png", number2);
  Sprite* sprite2 = Sprite::create(name2->getCString());
  sprite2->setPosition(Point(TILE_X*(MAP_X+2.5), TILE_Y + TILE_Y*1));
  
  String* name3 = String::createWithFormat("number/node%d.png", number3);
  Sprite* sprite3 = Sprite::create(name3->getCString());
  sprite3->setPosition(Point(TILE_X*(MAP_X+2.5), TILE_Y + TILE_Y*0));

  mLayer->addChild(sprite1, 3);
  mLayer->addChild(sprite2, 3);
  mLayer->addChild(sprite3, 3);

}

void GameLayer::setPositionNumber(int pNumber, int pRow, int pColumn)
{
  for(int i= 0; i< 4; i++)
  {
    //Get MySelf
    if(RoomLayer::mPlayerList[i] != NULL && RoomLayer::mPlayerList[i]->getMySelf())
    {
      if(RoomLayer::mPlayerList[i]->getPlayerScoreArray(pRow, pColumn) != -1)
        return;

      SoundLoader::playEffect("music/put_down.wav");

      RoomLayer::mPlayerList[i]->setPlayerScoreArray(pNumber, pRow, pColumn);

      String* name = String::createWithFormat("number/node%d.png", pNumber);
      Sprite* sprite = Sprite::create(name->getCString());
      sprite->setPosition(mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)));
      //CCLog("SPRITE: %f %f", mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).x, mTileLayer->getPositionAt(Point(pRow + 1.5, pColumn - 1)).y);
  

      mLayer->addChild(sprite, 3);
      //Tang so turn. turn hien tai = mTurn/3 -1
      mTurn++;

      int score = mCal->detection(RoomLayer::mPlayerList[i]->getPlayerScoreArray());
      if(score > RoomLayer::mPlayerList[i]->getScore())
        SoundLoader::playEffect("music/increase.wav");

      RoomLayer::mPlayerList[i]->setScore(score);

      CCLog("SCORE: %d", RoomLayer::mPlayerList[i]->getScore());
      viewScore();

      //Send MyPosition
      CheckinLayer::mConnect->sendPosition(RoomLayer::mPlayerList[i]->getID(), 
        std::to_string(pNumber), std::to_string(pRow), std::to_string(pColumn));

      //Send End game
      CCLog("mTurn: %d", mTurn);
      if(mTurn == 27*3)
        CheckinLayer::mConnect->sendEndGame();

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
  //Kiem tra da gui position chua
  if(mTurn == (CheckinLayer::mConnect->getTurn())*3)
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
      mTileLayer->getPositionAt(Point(i + 1.5, 0 - 1)).y - TILE_Y/2 - TILE_Y*2, TILE_X-1, TILE_Y*3-1);
  
    //Hang 2
    mListRect[i+MAP_X] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 3 - 1)).x - TILE_X/2, 
      mTileLayer->getPositionAt(Point(i + 1.5, 3 - 1)).y - TILE_Y/2 - TILE_Y*2, TILE_X-1, TILE_Y*3-1);
 
    //Hang 3
    mListRect[i+2*MAP_X] = CCRectMake(mTileLayer->getPositionAt(Point(i + 1.5, 6 - 1)).x - TILE_X/2, 
      mTileLayer->getPositionAt(Point(i + 1.5, 6 - 1)).y - TILE_Y/2 - TILE_Y*2, TILE_X-1, TILE_Y*3-1);
  }
}

void GameLayer::viewScore()
{
  String* player0 = NULL;

  for(int i= 0; i< 4; i++)
  {
    if(RoomLayer::mPlayerList[i] == NULL)
      continue;

      player0 = String::createWithFormat("%s :: %d", RoomLayer::mPlayerList[i]->getName().c_str(), 
                                                            RoomLayer::mPlayerList[i]->getScore());
      //CCLog("SCORE: %s", player->getCString());
      //LabelBMFont* label0;
      mLayer->removeChild(mLabel[i]);
      mLabel[i] = LabelBMFont::create(player0->getCString(), "fonts/Arial.fnt");
      if(RoomLayer::mPlayerList[i]->getDisconnect())
        mLabel[i]->setOpacity(50);

	    mLabel[i]->setScale(0.5);

      mLabel[i]->setPosition(Point(3*WIDTH/4, 3*HEIGHT/4 +50 - 50*i));

      mLayer->addChild(mLabel[i], 2);
      mLabel[i]->runAction(ScaleTo::create(0.5, 1.0) );

  }
}

void GameLayer::setPositionPlayer(std::string pID, std::string pNumber, std::string pRow, std::string pColumn)
{
  for(int i= 0; i< 4; i++)
  {
    if(RoomLayer::mPlayerList[i] != NULL && RoomLayer::mPlayerList[i]->getID() == pID)
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
  int tmp1 = 0;
  for(int i= 0; i < 3 ; i++)
  {
   
    if(RoomLayer::mPlayerList[i] == NULL)
      continue;
    tmp1++;
//
    int max = i;
    for(int j = i+1; j < 4; j++)
    {
      if(RoomLayer::mPlayerList[j] != NULL && RoomLayer::mPlayerList[j]->getScore() > RoomLayer::mPlayerList[max]->getScore())
      {
        //Diem lon nhat thi set = i
        RoomLayer::mPlayerList[j]->setSTT(i);
        RoomLayer::mPlayerList[i]->setSTT(j);
        max = j;
      }
      else
        if(RoomLayer::mPlayerList[j] != NULL && RoomLayer::mPlayerList[j]->getScore() <= RoomLayer::mPlayerList[max]->getScore())
          RoomLayer::mPlayerList[j]->setSTT(j);
    }
      
  }

}

void GameLayer::setEndGame()
{
  SoundLoader::playEffect("music/end_game.wav");

  //Sort with score
  setSTT();

  for(int i= 0; i < 4 ; i++)
  {
    if(RoomLayer::mPlayerList[i] != NULL && RoomLayer::mPlayerList[i]->getMySelf()){
      String* status;
      if(RoomLayer::mPlayerList[i]->getSTT() == 0)
        status = String::createWithFormat("YOU WIN ^^");
      else
        status = String::createWithFormat("YOU LOSE :(");

      //CCLog("SCORE: %s", player->getCString());
      LabelBMFont* label = NULL;
      //mLayer->removeChild(label);
      label = LabelBMFont::create(status->getCString(), "fonts/Arial.fnt");
	    label->setScale(0.5);

      label->setPosition(Point(TILE_X*(MAP_X+ 5.5), TILE_Y + TILE_Y*1));

      mLayer->addChild(label, 2);
      label->runAction(ScaleTo::create(0.5, 1.0) );
    }
  }

  
}

void GameLayer::exitGame()
{

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage *closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(GameLayer::switchLayer, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    Menu* menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
}

void GameLayer::switchLayer(Object* pSender)
{
  SoundLoader::playEffect("music/click.wav");
  SoundLoader::playMusic("music/background_start.wav", true);

  //Disconnect server
  for(int i = 0; i< 4; i++)
    if(RoomLayer::mPlayerList[i] != NULL && RoomLayer::mPlayerList[i]->getMySelf())
    {
      CheckinLayer::mConnect->disconnectPlayer(RoomLayer::mPlayerList[i]->getName(), 
      RoomLayer::mPlayerList[i]->getID());
      
      //Thoat
      break;
    }

  for(int i= 0; i< 4; i++)
  {
    //delete RoomLayer::mPlayerList[i];
    RoomLayer::mPlayerList[i] = NULL;
  }
  //Delete connection
  GameLayer::mTurn = 0;
  CheckinLayer::mConnect->setTurn(0);
  CCLog("Turn Xoa%d: ", CheckinLayer::mConnect->getTurn());
  //CheckinLayer::mConnect->mTurn = 0;
  CheckinLayer::mConnect->mUsername.clear();
  CheckinLayer::mConnect->mState.clear();
  
  //delete - khong co y nghia
  CheckinLayer::mConnect->setRoomStatus(false);
  
  //Set room myself
  RoomDisplayLayer::setRoomStatus(false);

  RoomLayer::mUser = 0;
  
  //Switch to RoomLayer
  //Replace Scene
  CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
      1.0, RoomDisplayLayer::scene()
    );
  CCDirector::sharedDirector()->replaceScene(transition);
}

void GameLayer::setName()
{
  for(int i= 0; i < 4 ; i++)
  {
    if(RoomLayer::mPlayerList[i] != NULL && RoomLayer::mPlayerList[i]->getMySelf()){
      String* status;
      status = String::createWithFormat(RoomLayer::mPlayerList[i]->getName().c_str());

      //CCLog("SCORE: %s", player->getCString());
      LabelBMFont* label = NULL;
      //mLayer->removeChild(label);
      label = LabelBMFont::create(status->getCString(), "fonts/Arial.fnt");
	    label->setScale(0.5);

      label->setPosition(Point(TILE_X*(MAP_X+ 5.5), TILE_Y + TILE_Y*2));

      mLayer->addChild(label, 2);
      label->runAction(ScaleTo::create(0.5, 1.0) );

      //Thoat
      break;
    }
  }
}

void GameLayer::setPlayerDisconnect(std::string pID)
{
  for(int i= 0; i < 4 ; i++)
  {
    if(RoomLayer::mPlayerList[i] != NULL && RoomLayer::mPlayerList[i]->getID() == pID)
    {
      RoomLayer::mPlayerList[i]->setDisconnect(true);
      viewScore();
      //
      break;
    }
  }
}
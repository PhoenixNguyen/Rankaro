//============================================================================
// Name        : RoomLayer.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : RoomLayer in cocos2dx C++, Ansi-style
//============================================================================

#include "RoomLayer.h"

USING_NS_CC;

Menu* RoomLayer::mMenu = NULL;
MenuItem* RoomLayer::mMenuPlayer[4] = {NULL};

RoomLayer* RoomLayer::mLayer = NULL;
Player* RoomLayer::mPlayerList[4] = {NULL};
int RoomLayer::mUser = 0;
LabelBMFont* RoomLayer::mLabelList[4] = {NULL};

//RoomLayer::RoomLayer(void)
//{
//  
//}
//
//
RoomLayer::~RoomLayer(void)
{
  delete mMenuPlayer;
  
}

Scene* RoomLayer::scene()
{
  Scene* scene = Scene::create();
  RoomLayer* layer = RoomLayer::create();

  scene->addChild(layer);
  return scene;
}

RoomLayer* RoomLayer::create()
{
  /*RoomLayer* */ mLayer = new RoomLayer();
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

bool RoomLayer::init()
{
  if(!Layer::create())
    return false;
  
  mUser = 0;
  setMyself(true);
  addChild(BackgroundGame::create("room.png", this), 1);

  /////////////////// Greetings /////////////////////////////////////////////////////////////////////////
  String* room = String::createWithFormat("Waiting for more players - Room 0%d", CheckinLayer::mConnect->getRoom()+1);
  LabelBMFont* label;
  label = LabelBMFont::create(room->getCString(), "fonts/Arial.fnt");
	label->setScale(0.5);

  label->setPosition(Point(WIDTH/2, 3*HEIGHT/4 +80));

  addChild(label, 2);
  label->runAction(ScaleTo::create(0.5, 1.0) );

 // ////////////////////////////////////////////////////////////////////
  ////// Return to display room //////////////////////////////////////////////////////////////////////////////////
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Point origin = Director::getInstance()->getVisibleOrigin();

  MenuItemImage *closeItem = MenuItemImage::create(
                                      "CloseNormal.png",
                                      "CloseSelected.png",
                                      CC_CALLBACK_1(RoomLayer::switchLayer, this));
    
  closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                              origin.y + closeItem->getContentSize().height/2));

  //// create menu, it's an autorelease object
  Menu* menu = Menu::create(closeItem, NULL);
  menu->setPosition(Point::ZERO);
  this->addChild(menu, 2);

  ///////////////////////////////////////////////////////////////////////////////////////////////////

  mMenu = Menu::create(NULL);
  mMenu->setPosition(CCPointZero);
  mLayer->addChild(mMenu, 2);
 
  //setFirstUsername();
  //setFirstState();
  return true;
}

void RoomLayer::setLastUsername(std::string pName, std::string pID)
{
  //log("GET LAST USERNAME CONNECTED: %s", pName.c_str());
  /*if(mLayer->getMyself())
    mLayer->setMyID(pID);*/

  mLayer->addToMenu(pName, pID, mLayer->getMyself());
  mLayer->setMyself(false);
  
}

void RoomLayer::setFirstUsername()
{
  //log("GET LAST USERNAME CONNECTED: %s", pName.c_str());
  for( std::map<std::string, std::string>::iterator ii=CheckinLayer::mConnect->mUsername.begin(); 
    ii != CheckinLayer::mConnect->mUsername.end(); ++ii)
	   {
		   //log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
       CCLog("%s", (*ii).second.c_str());
       mLayer->addToMenu((*ii).second.c_str(), (*ii).first.c_str(), false);
	   }
  

  
}

void RoomLayer::addToMenu(std::string pName, std::string pID, bool pMySelf = false)
{
  
  //////////////////////////////////////////////////////////////////
  //Player mUser + 1
  //Init Player
  for(int dem=0; dem< 4; dem++)
  {
    if(mPlayerList[dem] != NULL)
      continue;

    mPlayerList[dem] = new Player();
    mPlayerList[dem]->setID(pID);
    mPlayerList[dem]->setName(pName);
    mPlayerList[dem]->setMySelf(pMySelf);
    mPlayerList[dem]->setNumber(dem);
    mPlayerList[dem]->setSTT(dem);
    mPlayerList[dem]->setScore(0);
    mPlayerList[dem]->setDisconnect(false);
    mPlayerList[dem]->createScoreArray();

    const char* player1 = pName.c_str();
  
    //LabelBMFont* label;
	  mLabelList[dem] = LabelBMFont::create(player1, "fonts/Arial.fnt");
	  mLabelList[dem]->setScale(0.5);

    mLabelList[dem]->setPosition(Point(WIDTH/4, 3*HEIGHT/4 - dem*100));
    this->addChild(mLabelList[dem], 2);
    mLabelList[dem]->runAction(ScaleTo::create(0.5, 1.0) );

    //String * player = String::createWithFormat("mMenuPlayer%d", mUser);
    //Map Player with ID
    //mPlayer.insert(std::pair<std::string, int>(pID, mUser));

    //CCLog("1. IDDDDDD %s", pID.c_str());
    RoomLayer::mMenuPlayer[dem] = MenuItemImage::create("room/Ready.png",
                                           "room/Readyed.png",
                                           "room/Readyed.png",
                                           this,
                                           menu_selector(RoomLayer::sendState));
    RoomLayer::mMenuPlayer[dem]->setPosition(3* WIDTH/4, 3*HEIGHT/4 - dem*100);

    if(!pMySelf)
      mMenuPlayer[dem]->setVisible(false);
    ////////////////////////////////////////////////////////////////////
    mMenu->addChild(RoomLayer::mMenuPlayer[dem]);

    //
    mUser ++;
    break;
  }
}
void RoomLayer::sendState(cocos2d::Object* pSender)
{
  SoundLoader::playEffect("music/click.wav");

  //CCLog("2. IDDDDDD %s", mLayer->getMyID().c_str());
  for(int i= 0; i< 4; i++){
    if(mPlayerList[i] != NULL && mPlayerList[i]->getMySelf()){
      //CCLog("%d :: %s", i, mPlayerList[i]->getID().c_str());
      CheckinLayer::mConnect->sendState(mPlayerList[i]->getID());
      
      break;
    }
  }

  
}


void RoomLayer::setLastState(std::string pID)
{
  for(int i= 0; i< 4; i++)
	   {
	      
       if(mPlayerList[i] != NULL && mPlayerList[i]->getID() == pID)
       {
         mMenuPlayer[mPlayerList[i]->getNumber()]->setVisible(true);
         mMenuPlayer[mPlayerList[i]->getNumber()]->setEnabled(false);

         break;
       }
	   }
}

void RoomLayer::setFirstState()
{
  for( std::map<std::string, std::string>::iterator i=CheckinLayer::mConnect->mState.begin(); 
    i != CheckinLayer::mConnect->mState.end(); ++i)
	{  
      for(int ii= 0; ii< 4; ii++)
	    {
	           //cout << (*ii).first << ": " << (*ii).second << endl;
		       //log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
           //CCLog("%s", (*ii).second.c_str());
           //mLayer->addToMenu((*ii).second.c_str(), (*ii).first.c_str(), false);
        if(mPlayerList[ii] != NULL && mPlayerList[ii]->getID() == (*i).first)
           {
             mMenuPlayer[mPlayerList[ii]->getNumber()]->setVisible(true);
             mMenuPlayer[mPlayerList[ii]->getNumber()]->setEnabled(false);
             break;
           }
	    }
  }
}

void RoomLayer::roomFull()
{
  Sprite* sprite = Sprite::create("room/full.png");
  sprite->setPosition(Point(WIDTH/2, HEIGHT/2));
  mLayer->addChild(sprite);
}

void RoomLayer::startGame()
{
  CCTransitionCrossFade* transition = CCTransitionCrossFade::create(1,
                      GameLayer::scene());

  CCDirector::sharedDirector()->replaceScene(transition);

}

void RoomLayer::switchLayer(cocos2d::Object* pSender)
{
  SoundLoader::playEffect("music/click.wav");

  //Delete all players
  for(int i= 0; i< 4; i++){
    if(mPlayerList[i] != NULL){
      
      delete mPlayerList[i];
      mPlayerList[i] = NULL;
      
    }
  }
  
  //Switch to Reg name
  //Replace Scene
  CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
    0.0, RoomDisplayLayer::scene()
    );
  CCDirector::sharedDirector()->replaceScene(transition);

  CheckinLayer::mConnect->sendOutRoom(std::string("11"));

  ////Reset value
  

  CheckinLayer::mConnect->mUsername.clear();
  CheckinLayer::mConnect->mState.clear();

  //CheckinLayer::mConnect->setRoomStatus(false);
  ////this player Ra khoi room
  RoomDisplayLayer::setRoomStatus(false);

  RoomLayer::mUser =0;

}

void RoomLayer::removePlayer(std::string pID)
{
  for(int i= 0; i< 4; i++){
    if(mPlayerList[i] != NULL && mPlayerList[i]->getID() == pID){
      mLayer->mMenu->removeChild(mMenuPlayer[mPlayerList[i]->getNumber()], true);
      mLayer->removeChild(mLabelList[i]);
      //CCLog("%d :: %s", i, mPlayerList[i]->getID().c_str());
      delete mPlayerList[i];
      mPlayerList[i] = NULL;
      
      RoomLayer::mUser --;
      break;
    }
  }
}
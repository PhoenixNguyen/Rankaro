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

RoomLayer::RoomLayer(void)
{
  
}


RoomLayer::~RoomLayer(void)
{
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
  addChild(BackgroundGame::create(this), 1);

 // ////////////////////////////////////////////////////////////////////

  mMenu = Menu::create(NULL);
  mMenu->setPosition(CCPointZero);
  mLayer->addChild(mMenu, 2);
 
  setFirstUsername();
  setFirstState();
  return true;
}

void RoomLayer::setLastUsername(std::string pName, std::string pID)
{
  //log("GET LAST USERNAME CONNECTED: %s", pName.c_str());
  if(mLayer->getMyself())
    mLayer->setMyID(pID);

  mLayer->addToMenu(pName, pID, mLayer->getMyself());
  mLayer->setMyself(false);
  
}

void RoomLayer::setFirstUsername()
{
  //log("GET LAST USERNAME CONNECTED: %s", pName.c_str());
  for( std::map<std::string, std::string>::iterator ii=MapScene::mConnect->mUsername.begin(); 
    ii != MapScene::mConnect->mUsername.end(); ++ii)
	   {
		   //log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
       //CCLog("%s", (*ii).second.c_str());
       mLayer->addToMenu((*ii).second.c_str(), (*ii).first.c_str(), false);
	   }
  

  
}

void RoomLayer::addToMenu(std::string pName, std::string pID, bool pMySelf = false)
{
  
  //////////////////////////////////////////////////////////////////
  //Player mUser + 1
  //mMyself = false;
  const char* player1 = pName.c_str();
  
  LabelBMFont* label;
	label = LabelBMFont::create(player1, "fonts/Arial.fnt");
	label->setScale(0.5);

  label->setPosition(Point(WIDTH/4, 3*HEIGHT/4 - mUser*100));
  this->addChild(label, 2);
  label->runAction(ScaleTo::create(0.5, 1.0) );

  //String * player = String::createWithFormat("mMenuPlayer%d", mUser);
  //Map Player with ID
  mPlayer.insert(std::pair<std::string, int>(pID, mUser));
  //CCLog("1. IDDDDDD %s", pID.c_str());
  RoomLayer::mMenuPlayer[mUser] = MenuItemImage::create("room/Ready.png",
                                         "room/Readyed.png",
                                         "room/Readyed.png",
                                         this,
                                         menu_selector(RoomLayer::sendState));
  RoomLayer::mMenuPlayer[mUser]->setPosition(3* WIDTH/4, 3*HEIGHT/4 - mUser*100);

  if(!pMySelf)
    mMenuPlayer[mUser]->setVisible(false);
  ////////////////////////////////////////////////////////////////////
  mMenu->addChild(RoomLayer::mMenuPlayer[mUser]);

  //
  mUser ++;
}
void RoomLayer::sendState(cocos2d::Object* pSender)
{
  
  //CCLog("2. IDDDDDD %s", mLayer->getMyID().c_str());
  MapScene::mConnect->sendState(mLayer->getMyID().c_str());

  /*CCTransitionCrossFade* transition = CCTransitionCrossFade::create(1,
                      GameLayer::scene());

  CCDirector::sharedDirector()->replaceScene(transition);*/

}


void RoomLayer::setLastState(std::string pID)
{
  for( std::map<std::string, int>::iterator ii=mLayer->mPlayer.begin(); 
    ii != mLayer->mPlayer.end(); ++ii)
	   {
	      
       if((*ii).first == pID)
       {
         mMenuPlayer[(*ii).second]->setVisible(true);
         mMenuPlayer[(*ii).second]->setEnabled(false);
       }
	   }
}

void RoomLayer::setFirstState()
{
  for( std::map<std::string, std::string>::iterator i=MapScene::mConnect->mState.begin(); 
    i != MapScene::mConnect->mState.end(); ++i)
	{  
      for( std::map<std::string, int>::iterator ii=mLayer->mPlayer.begin(); 
        ii != mLayer->mPlayer.end(); ++ii)
	    {
	           //cout << (*ii).first << ": " << (*ii).second << endl;
		       //log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
           //CCLog("%s", (*ii).second.c_str());
           //mLayer->addToMenu((*ii).second.c_str(), (*ii).first.c_str(), false);
           if((*ii).first == (*i).first)
           {
             mMenuPlayer[(*ii).second]->setVisible(true);
             mMenuPlayer[(*ii).second]->setEnabled(false);
             continue;
           }
	    }
  }
}
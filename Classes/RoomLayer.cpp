//============================================================================
// Name        : RoomLayer.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : RoomLayer in cocos2dx C++, Ansi-style
//============================================================================

#include "RoomLayer.h"

USING_NS_CC;

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
  RoomLayer* layer = new RoomLayer();
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

bool RoomLayer::init()
{
  if(!Layer::create())
    return false;

  addChild(BackgroundGame::create(this), 1);

  ////////////////////////////////////////////////////////////////////
  //Player 1
  const char* player1 = "HP001";
  LabelBMFont* label;
	label = LabelBMFont::create(player1, "fonts/Arial.fnt");
	label->setScale(0.1);

  label->setPosition(Point(WIDTH/2, HEIGHT/4));
	this->addChild(label, 2);
  label->runAction(ScaleTo::create(0.5, 1.0) );

  mMenuPlayer1 = MenuItemImage::create("room/Ready.png",
                                         "room/Readyed.png",
                                         "room/Readyed.png",
                                         this,
                                         menu_selector(RoomLayer::sendState));
  mMenuPlayer1->setPosition(WIDTH/2, HEIGHT/4 - 50);

  ////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////
  //Player 2
  const char* player2 = "HP002";
  LabelBMFont* label2;
	label2 = LabelBMFont::create(player2, "fonts/Arial.fnt");
	label2->setScale(0.1);

  label2->setPosition(Point(WIDTH/2, 3*HEIGHT/4 +50 ));
	this->addChild(label2, 2);
  label2->runAction(ScaleTo::create(0.5, 1.0) );

  mMenuPlayer2 = MenuItemImage::create("room/Ready.png",
                                         "room/Readyed.png",
                                         "room/Readyed.png",
                                         this,
                                         menu_selector(RoomLayer::sendState));
  mMenuPlayer2->setPosition(WIDTH/2, 3*HEIGHT/4);

  ////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////
  //Player 3
  const char* player3 = "HP003";
  LabelBMFont* label3;
	label3 = LabelBMFont::create(player3, "fonts/Arial.fnt");
	label3->setScale(0.1);

  label3->setPosition(Point(WIDTH/4, HEIGHT/2 ));
	this->addChild(label3, 2);
  label3->runAction(ScaleTo::create(0.5, 1.0) );

  mMenuPlayer3 = MenuItemImage::create("room/Ready.png",
                                         "room/Readyed.png",
                                         "room/Readyed.png",
                                         this,
                                         menu_selector(RoomLayer::sendState));
  mMenuPlayer3->setPosition(WIDTH/4, HEIGHT/2 - 50);

  ////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////
  //Player 3
  const char* player4 = "HP004";
  LabelBMFont* label4;
	label4 = LabelBMFont::create(player4, "fonts/Arial.fnt");
	label4->setScale(0.1);

  label4->setPosition(Point(3*WIDTH/4, HEIGHT/2 ));
	this->addChild(label4, 2);
  label4->runAction(ScaleTo::create(0.5, 1.0) );

  mMenuPlayer4 = MenuItemImage::create("room/Ready.png",
                                         "room/Readyed.png",
                                         "room/Readyed.png",
                                         this,
                                         menu_selector(RoomLayer::sendState));
  mMenuPlayer4->setPosition(3*WIDTH/4, HEIGHT/2 - 50);

  ////////////////////////////////////////////////////////////////////

  Menu* menu = Menu::create(mMenuPlayer1, mMenuPlayer2, mMenuPlayer3, mMenuPlayer4, NULL);
  menu->setPosition(CCPointZero);
  addChild(menu, 2);
}

void RoomLayer::sendState(Object* pSender)
{
  CCTransitionCrossFade* transition = CCTransitionCrossFade::create(1,
                      GameLayer::scene());

  CCDirector::sharedDirector()->replaceScene(transition);



}
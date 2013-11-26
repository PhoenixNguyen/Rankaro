//============================================================================
// Name        : CheckinLayer.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : CheckinLayer in cocos2dx C++, Ansi-style
//============================================================================


#include "CheckinLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

ConnectionLayer* CheckinLayer::mConnect = NULL;


CheckinLayer::~CheckinLayer(void)
{
  if(mConnect != NULL)
    CheckinLayer::mConnect->release();

}

Scene* CheckinLayer::scene()
{
  Scene* scene = Scene::create();
  CheckinLayer* layer = CheckinLayer::create();

  scene->addChild(layer);
  return scene;
}

CheckinLayer* CheckinLayer::create()
{
  CheckinLayer* layer = new CheckinLayer();
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

bool CheckinLayer::init()
{
  if(!Layer::create())
    return false;

  //Connect server
  mConnect = new ConnectionLayer();

  addChild(BackgroundGame::create(this), 1);

  mEditBox = EditBox::create(Size(300, 50), Scale9Sprite::create("input/Input.png"));
  mEditBox->setPosition(Point(WIDTH/2, HEIGHT/3));
  mEditBox->setFontColor(ccRED);

  mEditBox->setPlaceHolder("Your name ...");
  mEditBox->setMaxLength(20);
  //mEditBox->setReturnType(1);
  //mEditBox->setDelegate(this);
  addChild(mEditBox, 2);

  mSend = MenuItemImage::create("input/send.png",
                                         "input/sent.png",
                                         "input/sent.png",
                                         this,
                                         menu_selector(CheckinLayer::sendName));
  mSend->setPosition(WIDTH/2, HEIGHT/4 - 30);

  Menu* menu = Menu::create(mSend, NULL);
  menu->setPosition(CCPointZero);
  addChild(menu, 2);
  
  return true;

}

void CheckinLayer::sendName(Object* pSender)
{
  mSend->setEnabled(false);
  const char* name = mEditBox->getText();
  CCLog("%s", name);

  //Send to server
  mConnect->regUsername(name);
  //
  /*std::string data;
  MapScene::mConnect->lastUsername(MapScene::mConnect->mClient, data);*/
  //Replace Scene
  CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
      1.0, RoomDisplayLayer::scene()
    );
    
    CCDirector::sharedDirector()->replaceScene(transition);
}

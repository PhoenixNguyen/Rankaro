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

CheckinLayer::CheckinLayer(){}
CheckinLayer::~CheckinLayer(void)
{
  /*if(mConnect != NULL)
    CheckinLayer::mConnect->release();*/

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

  addChild(BackgroundGame::create("background.jpg", this), 1);

  mTextField = TextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
        "Thonburi",
        36);
	
  mTextField->setPosition(Point(WIDTH/2, HEIGHT/2));
	addChild(mTextField, 2);
	CCLog("TEXT FIELD: %s", mTextField->getString());

	mEditBox = EditBox::create(Size(300, 50), Scale9Sprite::create("input/Input.png"));
  mEditBox->setPosition(Point(WIDTH/2, HEIGHT/3));
  mEditBox->setFontColor(ccRED);
  mEditBox->setPlaceHolder("(1-6 character)");
  mEditBox->setPlaceholderFontSize(5);
  mEditBox->setMaxLength(7);
  //mEditBox->setReturnType(kKeyboardReturnTypeDone);
  //mEditBox->setDelegate(this);
	mEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
	mEditBox->setDelegate(this);
  addChild(mEditBox, 2);
  
	this->runAction(CCSequence::create(
		CCDelayTime::create(2.5f),
		CCCallFunc::create(this,
		callfunc_selector(CheckinLayer::addSendMenu)),
		NULL));
  
  return true;

}

void CheckinLayer::addSendMenu()
{
	
	//////////////////////
	mSend = MenuItemImage::create("input/send.png",
                                         "input/sent.png",
                                         "input/sent.png",
                                         this,
                                         menu_selector(CheckinLayer::sendName));
  mSend->setPosition(WIDTH/2, HEIGHT/4 - 30);

   ////// Return to main Menu //////////////////////////////////////////////////////////////////////////////////
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Point origin = Director::getInstance()->getVisibleOrigin();

  MenuItemImage *closeItem = MenuItemImage::create(
                                      "CloseNormal.png",
                                      "CloseSelected.png",
                                      CC_CALLBACK_1(CheckinLayer::switchLayer, this));
    
  closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                              origin.y + closeItem->getContentSize().height/2));

  ///////////////////////////////////////////////////////////////////////////////////////////////////
	Menu* menu = Menu::create(mSend, closeItem, NULL);
  menu->setPosition(CCPointZero);
  addChild(menu, 2);

}
void CheckinLayer::sendName(Object* pSender)
{
  SoundLoader::playEffect("music/click.wav");

  const char* name = mEditBox->getText();
  CCLog("%s", name);
  if(strcmp(name, "") == 0 ){
    name = strdup("Demo!");
	}
	if(strlen(name) > 7)
		return;

  mSend->setEnabled(false);
  

  //Send to server
  mConnect->regUsername(name);
  //
  /*std::string data;
  MapScene::mConnect->lastUsername(MapScene::mConnect->mClient, data);*/
  //Replace Scene
  CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
      1.5, RoomDisplayLayer::scene()
    );
  CCDirector::sharedDirector()->replaceScene(transition);
}


void CheckinLayer::switchLayer(cocos2d::Object* psender)
{
  SoundLoader::playEffect("music/click.wav");

  CheckinLayer::mConnect->sendDisconnect(std::string("11"));
  //Replace Scene
  CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
    1.0, MapScene::create()
    );
    
    CCDirector::sharedDirector()->replaceScene(transition);
}


void CheckinLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void CheckinLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void CheckinLayer::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void CheckinLayer::editBoxReturn(EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
    
}
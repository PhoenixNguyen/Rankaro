//============================================================================
// Name        : MenuStart.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : MenuStart in cocos2dx C++, Ansi-style
//============================================================================


#include "MenuStart.h"

USING_NS_CC;

MenuStart::MenuStart(void)
{
}


MenuStart::~MenuStart(void)
{
}

MenuStart* MenuStart::create(Object* pTarget)
{
  MenuStart* pMenuStart = new MenuStart();
  if(pMenuStart && pMenuStart->init(pTarget))
  {
    pMenuStart->autorelease();
    return pMenuStart;
  }
  else
  {
    CC_SAFE_DELETE(pMenuStart);
    return NULL;

  }
}

bool MenuStart::init(Object* pTarget)
{
  if(!MenuItem::create())
    return false;

  //Start
  MenuItemImage *startGame = MenuItemImage::create(
                                        "menu/StartGame.png",
                                        "menu/StartGame.png",
                                        this,
                                        menu_selector(MenuStart::startGame));
    
	startGame->setPosition(Point(WIDTH/2, HEIGHT-100));

  //Help
  MenuItemImage *help = MenuItemImage::create(
                                        "menu/Help.png",
                                        "menu/Help.png",
                                        this,
                                        menu_selector(MenuStart::startGame));
    
	help->setPosition(Point(WIDTH/2, HEIGHT-200));

  //Contact
  MenuItemImage *contact = MenuItemImage::create(
                                        "menu/Contact.png",
                                        "menu/Contact.png",
                                        this,
                                        menu_selector(MenuStart::startGame));
    
	contact->setPosition(Point(WIDTH/2, HEIGHT-300));

  //Quit
  MenuItemImage *quit = MenuItemImage::create(
                                        "menu/Quit.png",
                                        "menu/Quit.png",
                                        this,
                                        menu_selector(MenuStart::startGame));
    
	quit->setPosition(Point(WIDTH/2, HEIGHT-400));

    // create menu, it's an autorelease object
    Menu* menu = Menu::create(startGame, help, contact, quit, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu, 1);

    return true;
}

void MenuStart::startGame(Object* pSender)
{
  //Replace Scene to input name layer
  
    CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
      0.5, CheckinLayer::scene()
    );
    
    CCDirector::sharedDirector()->replaceScene(transition);
  
}

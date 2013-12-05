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
    
  startGame->setPosition(Point(WIDTH/2, HEIGHT - HEIGHT/5));

  //Help
  MenuItemImage *help = MenuItemImage::create(
                                        "menu/Help.png",
                                        "menu/Help.png",
                                        this,
                                        menu_selector(MenuStart::help));
    
	help->setPosition(Point(WIDTH/2, HEIGHT - HEIGHT/5 - 100));

  //Contact
  MenuItemImage *contact = MenuItemImage::create(
                                        "menu/Contact.png",
                                        "menu/Contact.png",
                                        this,
                                        menu_selector(MenuStart::contact));
    
	contact->setPosition(Point(WIDTH/2, HEIGHT - HEIGHT/5 - 200));

  //Quit
  MenuItemImage *quit = MenuItemImage::create(
                                        "menu/Quit.png",
                                        "menu/Quit.png",
                                        this,
                                        menu_selector(MenuStart::exitGame));
    
	quit->setPosition(Point(WIDTH/2, HEIGHT - HEIGHT/5 -300));

    // create menu, it's an autorelease object
    Menu* menu = Menu::create(startGame, help, contact, quit, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu, 1);

    return true;
}

void MenuStart::startGame(Object* pSender)
{
  //Replace Scene to input name layer
  SoundLoader::playEffect("music/click.wav");

    CCTransitionCrossFade* transition = CCTransitionCrossFade::create(
      2.0, CheckinLayer::scene()
    );
    
    CCDirector::sharedDirector()->replaceScene(transition);
  
}

void MenuStart::help(Object* pSender)
{
  SoundLoader::playEffect("music/click.wav");
}
void MenuStart::contact(Object* pSender)
{
  SoundLoader::playEffect("music/click.wav");
}
void MenuStart::exitGame(Object* pSender)
{
  SoundLoader::playEffect("music/click.wav");
  CCDirector::sharedDirector()->end();
}

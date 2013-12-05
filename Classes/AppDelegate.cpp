#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MapScene.h"
#include "GameLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
  CCDirector* pDirector = CCDirector::sharedDirector();
  CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
  pDirector->setOpenGLView(pEGLView);


  CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
  std::vector<std::string> searchPaths;
  
  if(IS_MOBILES)
  {
    if (pDirector->getWinSize().width == 800)
    {
      // 
      //pDirector->setContentScaleFactor(2);
      searchPaths.push_back("800x480");
      searchPaths.push_back("1280x768");
	  designResolutionSize = cocos2d::CCSizeMake(800, 480);
    }
    else if (pDirector->getWinSize().width == 1280)
    {
      // 
      //pDirector->setContentScaleFactor(2);
      searchPaths.push_back("1280x768");
      searchPaths.push_back("800x480");
      designResolutionSize = cocos2d::CCSizeMake(1280, 768);
    }
  }
  else
  {
	searchPaths.push_back("800x480");
	searchPaths.push_back("1280x768");
	designResolutionSize = cocos2d::CCSizeMake(800, 480);
  }
  

  //searchPaths.push_back("iphone");

  pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

  CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
  
  srand(time(0));
  
  CCLog("getWinSizeInPixels() w: %f, h: %f", CCDirector::sharedDirector()->getWinSizeInPixels().width,
        CCDirector::sharedDirector()->getWinSizeInPixels().height);

  // turn on display FPS
//  pDirector->setDisplayStats(true);
  
  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);
  
  //Config::loadConfiguration();
  // create a scene. it's an autorelease object

  // CCScene *pScene = HelloWorld::scene();

  CCScene* pScene = MapScene::create();
  //CCScene* pScene = GameLayer::scene("Images/Game/Backgrounds/bg_stage00.pvr.ccz");

  // run
  pDirector->runWithScene(pScene);
  
    //Scene *scene = MapScene::create();
    ////Scene *scene = GameLayer::scene();
    //
    //// run
    //director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

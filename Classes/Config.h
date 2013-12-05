//============================================================================
// Name        : Config.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : Config in cocos2dx C++, Ansi-style
//============================================================================



#ifndef __CONFIG__
#define __CONFIG__
//----------- RESOLUTION ------------------////////////////

#define IS_MOBILES (CCDirector::sharedDirector()->getWinSizeInPixels().width==1280)

#define WIDTH (IS_MOBILES ? CCDirector::sharedDirector()->getWinSizeInPixels().width : 800)
#define HEIGHT (IS_MOBILES ? CCDirector::sharedDirector()->getWinSizeInPixels().height : 480)



#define RESOLUTION 800x480


//-------------------------------------------------------

#define MAP_X 9
#define MAP_Y 9

#define TILE_X (IS_MOBILES ? 80 : 48)
#define TILE_Y (IS_MOBILES ? 80 : 48)

#define MAX_ROOM 9

class Config
{
public:
  Config(void);
  ~Config(void);
};

#endif
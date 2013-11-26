//============================================================================
// Name        : Config.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : Config in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __CONFIG__
#define __CONFIG__

#define WIDTH 800
#define HEIGHT 480

#define MAP_X 9
#define MAP_Y 9

#define TILE_X 48
#define TILE_Y 48

#define MAX_ROOM 9

class Config
{
public:
  Config(void);
  ~Config(void);
};

#endif
//============================================================================
// Name        : Player.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : Player in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __PLAYER__
#define __PLAYER__

#include "cocos2d.h"
#include "Config.h"

class Player
{
  CC_SYNTHESIZE(std::string, mName, Name);
  CC_SYNTHESIZE(std::string, mID, ID);
  CC_SYNTHESIZE(int, mScore, Score);
  CC_SYNTHESIZE(bool, mMySelf, MySelf);
  CC_SYNTHESIZE(int, mNumber, Number);

  static int mPlayerScoreArray[MAP_X][MAP_Y];

public:
  Player(void);
  ~Player(void);

  static int** getPlayerScoreArray();
  static int getPlayerScoreArray(int pRow, int pColumn);
  static void setPlayerScoreArray(int pScore, int pRow, int pColumn);
};

#endif
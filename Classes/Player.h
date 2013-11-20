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
  CC_SYNTHESIZE(int, mSTT, STT);

  int mPlayerScoreArray[MAP_X][MAP_Y];

public:
  Player(void);
  ~Player(void);

  int** getPlayerScoreArray();
  int getPlayerScoreArray(int pRow, int pColumn);
  void setPlayerScoreArray(int pNumber, int pRow, int pColumn);
  void createScoreArray();
};

#endif
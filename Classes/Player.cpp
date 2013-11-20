//============================================================================
// Name        : Player.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : Player in cocos2dx C++, Ansi-style
//============================================================================

#include "Player.h"

USING_NS_CC;

Player::Player(void)
{
}


Player::~Player(void)
{
}


int** Player::getPlayerScoreArray()
{
  int** tmp = new int*[MAP_X];
  for(int i= 0; i< MAP_X; i++)
  {
    tmp[i] = new int[MAP_Y];
    for(int j= 0; j< MAP_Y; j++)
    {
      tmp[i][j] = mPlayerScoreArray[i][j];
    }
  }

  return tmp;
}

int Player::getPlayerScoreArray(int pRow, int pColumn)
{
  return mPlayerScoreArray[pRow][pColumn];
}
void Player::setPlayerScoreArray(int pScore, int pRow, int pColumn)
{
  mPlayerScoreArray[pRow][pColumn] = pScore;
}

void Player::createScoreArray()
{
  for(int i = 0; i< MAP_X; i++)
    for(int j= 0; j< MAP_Y; j++)
    {
      mPlayerScoreArray[i][j] = -1;
    }
}
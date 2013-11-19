//============================================================================
// Name        : Player.cpp
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : Player in cocos2dx C++, Ansi-style
//============================================================================

#include "Player.h"

USING_NS_CC;

int Player::mPlayerScoreArray[MAP_X][MAP_Y] = {NULL};

Player::Player(void)
{
  int* p;
  p = (int*)mPlayerScoreArray;
  for(int i= 0; i< MAP_X*MAP_Y; i++)
    *(p+i) = -1;
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
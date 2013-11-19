//============================================================================
// Name        : GameLayer.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : GameLayer in cocos2dx C++, Ansi-style
//============================================================================

#ifndef __GAME_LAYER__
#define __GAME_LAYER__

#include "cocos2d.h"
#include "BackgroundGame.h"
#include "Config.h"
#include "CaculateScore.h"
#include "Player.h"

class GameLayer : public cocos2d::Layer
{
  static cocos2d::TMXTiledMap* mTileMap;
  static cocos2d::TMXLayer* mTileLayer;
  static GameLayer* mLayer;
  cocos2d::Rect mListRect[27];
  static int mMyScore[MAP_X][MAP_Y];
  static CaculateScore* mCal;

  static cocos2d::LabelBMFont* mLabel;

  static Player* mPlayer;
public:
  GameLayer(void);
  ~GameLayer(void);

  static cocos2d::Scene* scene();
  static GameLayer* create();
  virtual bool init();

  static void setNumber(int pNumber);
  static void setPositionNumber(int pNumber, int pRow, int pColumn);

  //Touch begin
	void ccTouchesBegan(cocos2d::Set* pTouches, cocos2d::Event* pEvent);
		
	//Touch move
	void ccTouchesMoved(cocos2d::Set* pTouches, cocos2d::Event* pEvent);
  void ccTouchesEnded(cocos2d::Set* pTouches, cocos2d::Event* pEvent);

  //Set List Rect
  void createRect();

  //View Score and sort
  static void viewScore(Player* pPlayer/*const char* pName, int pScore*/);
};

#endif
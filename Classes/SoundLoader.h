//============================================================================
// Name        : SoundLoader.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : SoundLoader in Cocos2d x C++, Ansi-style
//============================================================================

#ifndef __SOUND_LOADER__
#define __SOUND_LOADER__

#include "cocos2d.h"
#include "MapLayer.h"
#include "SimpleAudioEngine.h"


class SoundLoader : public cocos2d::Object
{
public:
  static void preloadMusic();

  static void playMusic(const char* pMusic, bool pLoop);
  static void pauseMusic();
  static void resumeMusic();
  static void stopMusic();

  static void playEffect(const char* pEffect);

};

#endif
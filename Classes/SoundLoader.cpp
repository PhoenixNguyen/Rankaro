//============================================================================
// Name        : SoundLoader.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : SoundLoader in Cocos2d x C++, Ansi-style
//============================================================================

#include "SoundLoader.h"

void SoundLoader::preloadMusic()
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/background_game.wav");
  CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/background_start.wav");
  CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/click.wav");
  CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/end_game.wav");
  CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/increase.wav");
  CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/put_down.wav");
}

void SoundLoader::playMusic(const char* pMusic, bool pLoop)
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pMusic,  pLoop);
}
void SoundLoader::pauseMusic()
{
  if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
      CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
}
void SoundLoader::resumeMusic()
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
void SoundLoader::stopMusic()
{
  if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
      CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}

void SoundLoader::playEffect(const char* pEffect)
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pEffect);
}
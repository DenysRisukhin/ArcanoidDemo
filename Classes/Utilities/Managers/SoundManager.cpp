//
//  SoundManager.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "SoundManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

SoundManager* SoundManager::m_instance = NULL;

SoundManager* SoundManager::instance()
{
    if (!m_instance)
    {
        m_instance = new SoundManager;
    }
    
    return m_instance;
}

void SoundManager::init() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("barrierCrash.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("barrierTouch.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("buttonTap.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("lose.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("win.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("platform.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("wall.mp3");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("inAction.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mainMenu.mp3");
    
    m_musicVol = 5;
    m_effectsVol = 5;
}

void SoundManager::stopAllFx() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

int SoundManager::getVol(const int volType) {
    //    if (volType == kVolTypeMusic){
    //        return _musicVol;
    //    }
    //    else if (volType == kVolTypeEffect) {
    //        return    _effectsVol;
    //    }
    return 0;
}

void SoundManager::setVol(const int volType, const int val) {
    //    if (volType == kVolTypeMusic){
    //        _musicVol = val;
    //        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)_musicVol / 10);
    //        // UserDefault::getInstance()->setIntegerForKey(US_VOL_MUSIC, _musicVol);
    //    }
    //    else if (volType == kVolTypeEffect) {
    //        _effectsVol = val;
    //        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
    //        //UserDefault::getInstance()->setIntegerForKey(US_VOL_EFFECT, _effectsVol);
    //    }
}

void SoundManager::playFx(SoundManager::FX fx) {
    
    string fxName;
    
    switch(fx)
    {
        case SoundManager::FX::BarrierCrash:
            fxName = "barrierCrash.mp3";
            break;
        case SoundManager::FX::BarrierTouch:
            fxName = "barrierTouch.wav";
            break;
        case SoundManager::FX::ButtonTap:
            fxName = "buttonTap.wav";
            break;
        case SoundManager::FX::Wall:
            fxName = "wall.mp3";
            break;
        case SoundManager::FX::Platform:
            fxName = "platform.wav";
            break;
        case SoundManager::FX::Lose:
            fxName = "lose.wav";
            break;
        case SoundManager::FX::Win:
            fxName = "win.wav";
            break;
        default:
            break;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)m_effectsVol / 10);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fxName.c_str());
}

void SoundManager::startBGMusic(SoundManager::BGSound bgSound)
{
    string soundName;
    
    switch(bgSound)
    {
        case SoundManager::BGSound::MainMenu:
            soundName = "mainMenu.mp3";
            break;
        case SoundManager::BGSound::InAction:
            soundName = "inAction.mp3";
            break;
        
        default:
            break;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)m_musicVol / 10);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName.c_str(), true);
}

void SoundManager::stopBGMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}



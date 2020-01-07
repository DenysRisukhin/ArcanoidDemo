//
//  SoundManager.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef SoundManager_h
#define SoundManager_h

#include <stdio.h>
#include "cocos2d.h"

class SoundManager
{
public:
    
    enum class BGSound
    {
        MainMenu = 0,
        InAction
    };
    
    enum class FX
    {
        BarrierCrash = 0,
        BarrierTouch,
        ButtonTap,
        Wall,
        Platform,
        Lose,
        Win
    };
    
    static SoundManager* instance();
    
    void init();

    void setVol(const int volType, const int val);
    int getVol(const int volType);
    
    void startBGMusic(SoundManager::BGSound bgSound);
    void stopBGMusic();
    void playFx(SoundManager::FX fx);
    void stopAllFx();
    
private:
    SoundManager() {}
    
    static SoundManager* m_instance;
        
    int m_musicVol;
    int m_effectsVol;
};

#endif /* SoundManager_h */

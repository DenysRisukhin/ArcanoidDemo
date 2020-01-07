//
//  SceneManager.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef SceneManager_h
#define SceneManager_h

#include <stdio.h>
#include "cocos2d.h"

class SceneManager
{
public:
    
    enum class SceneID
    {
        Splash = 0,
        MainMenu,
        Map,
        InAction,
        Result
    };
    
    static SceneManager* instance();
    
    // Represents transition to desired scene.
    void runScene(SceneID sceneID, bool isWin = false, int score = 0);
       
    const cocos2d::Size getWinSize() const { return cocos2d::Director::getInstance()->getWinSize(); }
    const cocos2d::Size getVisibleSize() const { return cocos2d::Director::getInstance()->getVisibleSize(); }
    const cocos2d::Vec2 getVisibleOrigin() const { return cocos2d::Director::getInstance()->getVisibleOrigin(); }
        
private:
    SceneManager() {}

    static SceneManager* m_instance;
};

#endif /* SceneManager_h */

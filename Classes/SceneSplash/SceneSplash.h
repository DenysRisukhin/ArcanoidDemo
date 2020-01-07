//
//  SceneSplash.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#ifndef SceneSplash_h
#define SceneSplash_h

#include <stdio.h>

class TitleSplashNode;
class LoadingSplashNode;

class SceneSplash: public cocos2d::Scene
{
public:
    CREATE_FUNC(SceneSplash);
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void renderComponents();
    
private:
    TitleSplashNode* m_titleImgNode = nullptr;
    LoadingSplashNode* m_labelLoadingNode = nullptr;
    
    cocos2d::Size m_screenWinSize;
    void runMainMenuScene(float);
};

#endif /* SceneSplash_h */

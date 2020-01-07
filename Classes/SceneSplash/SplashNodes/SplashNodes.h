//
//  SplashNodes.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/16/19.
//

#ifndef SplashNodes_h
#define SplashNodes_h

#include <stdio.h>

#include "cocos2d.h"

class LabelFontAnimated;

class TitleSplashNode: public cocos2d::Node
{
public:
    bool init() override;
    void renderUI();
    
private:
    cocos2d::Sprite* m_arcanoidSplashTitleImg = nullptr;
    
    cocos2d::Size m_screenWinSize;
};

#pragma mark - Loading Splash Node

class LoadingSplashNode: public cocos2d::Node
{
public:
    bool init() override;
    void renderUI();
    
private:
    LabelFontAnimated* m_labelLoading = nullptr;
};

#endif /* SplashNodes_h */

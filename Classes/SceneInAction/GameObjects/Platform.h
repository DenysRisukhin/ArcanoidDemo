//
//  Platform.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef Platform_h
#define Platform_h

#include <stdio.h>

class Platform : public cocos2d::Sprite
{
public:
    
    enum class PlatformState
    {
        GRABBED = 0,
        UNGRABBED
    };
        
    static Platform* createWithTexture(cocos2d::Texture2D* aTexture);
    bool initWithTexture(cocos2d::Texture2D* aTexture) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    void setMoveLimitPosX(float gameFrameWidthStart, float gameFrameWidthEnd);
    
    cocos2d::Rect getRect();
    
    bool containsTouchLocation(cocos2d::Touch* touch);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
private:
    PlatformState m_state;
    cocos2d::Vec2 m_prevPosition;
    
    float m_gameFrameWidthStart = 0.f;
    float m_gameFrameWidthEnd = 0.f;
};

#endif /* Platform_h */

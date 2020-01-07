//
//  Ball.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef Ball_h
#define Ball_h

#include <stdio.h>
#include "GameFieldRect.h"

class Platform;
class BarrierNode;

class Ball: public cocos2d::Sprite
{
public:
    enum class FXsound
    {
        Platform = 0,
        Wall
    };
    
    using FxCallback = std::function<void()>;

    void setTapCallback(FxCallback callback) { m_fxCallback = std::move(callback); }
    
    static Ball* ballWithTexture(cocos2d::Texture2D* aTexture);
    
    void setVelocity(cocos2d::Vec2 velocity);
    cocos2d::Vec2 getVelocity() const;
    
    cocos2d::Rect getRect() const;
    
    float getRadius() const;
    
    FXsound getFXsound() const;
    
    void update(float delta);
    
    void collideWithWalls(GameFieldRect gameFieldRect);
    void collideWithPlatform(Platform* platform);
    bool collideWithBarrier(BarrierNode* barrier, float indent);
    
protected:
    FxCallback m_fxCallback;
    
private:
    FXsound m_fxSound;
    
    cocos2d::Vec2 m_velocity = cocos2d::Vec2(0.f, 0.f);
    float m_scalarVelocity = 0.f;
    float m_velocityAngle = 0.f;
    
    void updateVelocityAngel(bool hitLeftRight, bool hitTop, float hitAngle);
};

#endif /* Ball_h */

//
//  Ball.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "Ball.h"
#include "Platform.h"
#include "Barrier.h"
#include "GameFieldRect.h"

USING_NS_CC;

//#define ButtomWallOn

Ball* Ball::ballWithTexture(Texture2D* texture)
{
    Ball* ball = new (std::nothrow) Ball();
    ball->initWithTexture(texture);
    ball->autorelease();
    return ball;
}

void Ball::setVelocity(cocos2d::Vec2 velocity)
{
    m_velocity = velocity;
}

cocos2d::Vec2 Ball::getVelocity() const
{
    return m_velocity;
}

cocos2d::Rect Ball::getRect() const
{
    auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

float Ball::getRadius() const
{
    return getTexture()->getContentSize().width / 2.f;
}

#pragma mark - handling collisions with walls

void Ball::update(float delta)
{
    this->setPosition(getPosition() + m_velocity * delta);
}

void Ball::collideWithWalls(GameFieldRect gameFieldRect)
{
    bool hitSide = false;
    bool hitTopSide = false;
    
    float angleOffset = 0.f;
    float hitAngle = 0.f;
    
    Vec2 gameFieldRectPos;
    
    if ( getPosition().x < gameFieldRect.left().x + getRadius())
    {
        log("left wall: right side touched");
        hitSide = true;
        
        setPosition(gameFieldRect.left().x + getRadius(), getPosition().y);
        gameFieldRectPos = Vec2(gameFieldRect.leftBottom().x, gameFieldRect.leftTop().y);
        
        angleOffset = -(float)M_PI / 2;
        
        hitAngle = (gameFieldRectPos + getPosition()).getAngle() + angleOffset;
    }
    else if (getPosition().x > gameFieldRect.right().x - getRadius())
    {
        log("right wall: left side touched");
        hitSide = true;
        
        setPosition(gameFieldRect.right().x - getRadius(), getPosition().y);
        gameFieldRectPos = Vec2(gameFieldRect.rightBottom().x, gameFieldRect.rightTop().y);
        
        angleOffset = -(float)M_PI / 2;
        
        hitAngle = (gameFieldRectPos - getPosition()).getAngle() + angleOffset;
    }
    
    if (getPosition().y > gameFieldRect.top().y - getRadius())
    {
        log("top wall: botton side touched");
        hitTopSide = true;

        setPosition(getPosition().x, gameFieldRect.top().y - getRadius());
        m_velocity.y *= -1;
    }
    
    updateVelocityAngel(hitSide, hitTopSide, hitAngle);
    
#ifdef ButtomWallOn
    if (getPosition().y < gameFieldRect.bottom().y + getRadius())
    {
        log("bottm wall: top side touched");
        
        setPosition(getPosition().x, gameFieldRect.bottom().y + getRadius());
        m_velocity.y *= -1;
    }
#endif
}

void Ball::updateVelocityAngel(bool hitSide, bool hitTopSide, float hitAngle)
{
    if (hitSide)
    {
        auto velocityAngle = -m_velocity.getAngle() + 0.5 * hitAngle;
        m_velocity = Vec2::forAngle(velocityAngle) * m_velocity.getLength();
        
        m_velocity.x *= -1;
        m_velocity.y *= -1;
    }
    
    if (hitTopSide || hitSide)
    {
        if (m_fxCallback)
        {
            m_fxSound = Ball::FXsound::Wall;
            m_fxCallback();
        }
    }
}

Ball::FXsound Ball::getFXsound() const
{
    return m_fxSound;
}

#pragma mark - collide with platform

void Ball::collideWithPlatform(Platform* platform)
{
    auto platformRect = platform->getRect();
    platformRect.origin.x += platform->getPosition().x;
    platformRect.origin.y += platform->getPosition().y;
    
    float lowY  = platformRect.getMinY();
    float midY  = platformRect.getMidY();
    float highY = platformRect.getMaxY();
    
    float leftX  = platformRect.getMinX();
    float midX   = platformRect.getMidX();
    float rightX = platformRect.getMaxX();
    
    bool hit = false;
    
    // check collisions with top or botton platform side
    if ((getPosition().x > leftX && getPosition().x < rightX)) {
        
        hit = false;
        float angleOffset = 0.0f;
        
        if (getPosition().y > midY && getPosition().y <= highY + getRadius())
        {
            log("Platform: top side touched");
            setPosition(getPosition().x, highY + getRadius());
            hit = true;
            angleOffset = (float)M_PI / 2;
            
        }
        else if (getPosition().y < midY && getPosition().y >= lowY - getRadius())
        {
            log("Platform: bottom side touched");
            setPosition(getPosition().x, lowY - getRadius());
            hit = true;
            angleOffset = -(float)M_PI / 2;
        }
        
        if (hit)
        {
            float hitAngle = (platform->getPosition() - getPosition()).getAngle() + angleOffset;
            auto scalarVelocity = m_velocity.getLength();
            auto velocityAngle = -m_velocity.getAngle() + 0.5f * hitAngle;

            m_velocity = Vec2::forAngle(velocityAngle) * scalarVelocity;
        }
    }
    
    // check collisions with left or right platform side
    if (getPosition().y > lowY && getPosition().y < highY)
    {
        if (getPosition().x > midX && getPosition().x <= rightX + getRadius())
        {
            log("Platform: right side was touched");
            hit = true;

            setPosition(rightX + getRadius(), getPosition().y);
            m_velocity.x *= -1;
        }
        
        if (getPosition().x < midX && getPosition().x >= leftX - getRadius())
        {
            log("Platform: left side was touched");
            hit = true;
    
            setPosition(leftX - getRadius(), getPosition().y);
            m_velocity.x *= -1;
        }
    }
    
    if (hit)
    {
        if (m_fxCallback)
        {
            m_fxSound = Ball::FXsound::Platform;
            m_fxCallback();
        }
    }
}

#pragma mark - collide with barrier

bool Ball::collideWithBarrier(BarrierNode* barrier, float indent)
{
    auto barrierRect = barrier->getRect();
    
    barrierRect.origin.x += barrier->getPosition().x * barrier->getParent()->getScaleX();
    barrierRect.origin.x += indent;
    barrierRect.origin.y += barrier->getPosition().y * barrier->getParent()->getScaleY();
    
    float lowY  = barrierRect.getMinY();
    float midY  = barrierRect.getMidY();
    float highY = barrierRect.getMaxY();
    
    float leftX  = barrierRect.getMinX();
    float midX   = barrierRect.getMidX();
    float rightX = barrierRect.getMaxX();
    
    // check collisions with top or botton barrier side
    if (getPosition().x > leftX && getPosition().x < rightX)
    {
        if (getPosition().y > midY && getPosition().y <= highY + getRadius())
        {
            log("Barrier: right side was touched");
            
            setPosition(getPosition().x, highY + getRadius());
            m_velocity.y *= -1;
            return true;
        }
        else if (getPosition().y < midY && getPosition().y >= lowY - getRadius())
        {
            log("Barrier: right side was touched");
            
            setPosition(getPosition().x, lowY - getRadius());
            m_velocity.y *= -1;
            
            return true;
        }
    }
    
    // check collisions with left or right barrier side
    if (getPosition().y > lowY && getPosition().y < highY)
    {
        if (getPosition().x > midX && getPosition().x <= rightX + getRadius())
        {
            log("Barrier: right side was touched");
            
            setPosition(rightX + getRadius(), getPosition().y);
            m_velocity.x *= -1;
            
            return true;
        }
        
        if (getPosition().x < midX && getPosition().x >= leftX - getRadius())
        {
            log("Barrier: left side was touched");
            
            setPosition(leftX - getRadius(), getPosition().y);
            m_velocity.x *= -1;
            
            return true;
        }
    }
    return false;
}




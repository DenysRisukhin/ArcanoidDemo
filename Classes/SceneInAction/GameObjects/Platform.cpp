//
//  Platform.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "Platform.h"

USING_NS_CC;

Platform* Platform::createWithTexture(Texture2D* texture)
{
    Platform* platform = new (std::nothrow) Platform();
    platform->initWithTexture(texture);
    platform->autorelease();
    return platform;
}

bool Platform::initWithTexture(Texture2D* texture)
{
    if(Sprite::initWithTexture(texture))
    {
        m_state = PlatformState::UNGRABBED;
    }
    
    return true;
}

void Platform::onEnter()
{
    Sprite::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Platform::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Platform::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Platform::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Platform::onExit()
{
    Sprite::onExit();
}

void Platform::setMoveLimitPosX(float gameFrameWidthStart, float gameFrameWidthEnd)
{
    m_gameFrameWidthStart = gameFrameWidthStart;
    m_gameFrameWidthEnd = gameFrameWidthEnd;
}

Rect Platform::getRect()
{
    auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

#pragma mark - touch events

bool Platform::onTouchBegan(Touch* touch, Event* event)
{
    if (m_state != PlatformState::UNGRABBED || !containsTouchLocation(touch))
    {
        return false;
    }
    
    m_state = PlatformState::GRABBED;

    return true;
}

void Platform::onTouchMoved(Touch* touch, Event* event)
{
    CCASSERT(m_state == PlatformState::GRABBED, "Platform - Unexpected state!");
    
    auto touchPoint = touch->getLocation();
    
    // Handling collisions with walls
    m_prevPosition = this->getPosition();
    
    this->setPosition(Vec2(touchPoint.x, getPosition().y));
    
    if (getPosition().x > m_gameFrameWidthEnd - getTexture()->getContentSize().width / 2 ||
        getPosition().x < m_gameFrameWidthStart + getTexture()->getContentSize().width / 2)
    {
        this->setPosition(m_prevPosition);
    }
}

void Platform::onTouchEnded(Touch* touch, Event* event)
{
    CCASSERT(m_state == PlatformState::GRABBED, "Platform - Unexpected state!");
    
    m_state = PlatformState::UNGRABBED;
}

bool Platform::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}


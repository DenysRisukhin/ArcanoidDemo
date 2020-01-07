//
//  GameFieldRect.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/12/19.
//

#include "GameFieldRect.h"
USING_NS_CC;

GameFieldRect::GameFieldRect(Rect gameFieldRect)
{
    m_gameFieldRect = gameFieldRect;
}

GameFieldRect::GameFieldRect(const Rect& gameFieldRect)
{
    m_gameFieldRect = gameFieldRect;
}

void GameFieldRect::setRect(Rect gameFieldRect)
{
    m_gameFieldRect = gameFieldRect;
}

Rect GameFieldRect::getGameFieldRect()
{
    return m_gameFieldRect;
}

#pragma mark - basic stuff

Vec2 GameFieldRect::left()
{
    return Vec2(m_gameFieldRect.origin.x, m_gameFieldRect.origin.y+m_gameFieldRect.size.height/2);
}

Vec2 GameFieldRect::right()
{
    return Vec2(m_gameFieldRect.origin.x+m_gameFieldRect.size.width, m_gameFieldRect.origin.y+m_gameFieldRect.size.height/2);
}

Vec2 GameFieldRect::top()
{
    return Vec2(m_gameFieldRect.origin.x+m_gameFieldRect.size.width/2, m_gameFieldRect.origin.y+m_gameFieldRect.size.height);
}

Vec2 GameFieldRect::bottom()
{
    return Vec2(m_gameFieldRect.origin.x+m_gameFieldRect.size.width/2, m_gameFieldRect.origin.y);
}

Vec2 GameFieldRect::center()
{
    return Vec2(m_gameFieldRect.origin.x+m_gameFieldRect.size.width/2, m_gameFieldRect.origin.y+m_gameFieldRect.size.height/2);
}

Vec2 GameFieldRect::leftTop()
{
    return Vec2(m_gameFieldRect.origin.x, m_gameFieldRect.origin.y+m_gameFieldRect.size.height);
}

Vec2 GameFieldRect::rightTop()
{
    return Vec2(m_gameFieldRect.origin.x+m_gameFieldRect.size.width, m_gameFieldRect.origin.y+m_gameFieldRect.size.height);
}

Vec2 GameFieldRect::leftBottom()
{
    return m_gameFieldRect.origin;
}

Vec2 GameFieldRect::rightBottom()
{
    return Vec2(m_gameFieldRect.origin.x+m_gameFieldRect.size.width, m_gameFieldRect.origin.y);
}

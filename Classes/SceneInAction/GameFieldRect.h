//
//  GameFieldRect.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/12/19.
//

#ifndef GameFieldRect_h
#define GameFieldRect_h

#include <stdio.h>

class GameFieldRect
{
public:
    
    GameFieldRect() {}
    
    GameFieldRect(cocos2d::Rect gameFieldRect);
    GameFieldRect(const cocos2d::Rect& gameFieldRect);
    
    void setRect(cocos2d::Rect gameFieldRect);
    cocos2d::Rect getGameFieldRect();
    
    cocos2d::Vec2 left();
    cocos2d::Vec2 right();
    cocos2d::Vec2 top();
    cocos2d::Vec2 bottom();
    cocos2d::Vec2 center();
    cocos2d::Vec2 leftTop();
    cocos2d::Vec2 rightTop();
    cocos2d::Vec2 leftBottom();
    cocos2d::Vec2 rightBottom();
    
private:
    cocos2d::Rect m_gameFieldRect;
};

#endif /* GameFieldRect_h */

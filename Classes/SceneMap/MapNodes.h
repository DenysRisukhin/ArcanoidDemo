//
//  MapNodes.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/17/19.
//

#ifndef MapNodes_h
#define MapNodes_h

#include <stdio.h>
#include "cocos2d.h"

class LevelNode: public cocos2d::Node
{
public:
    bool init() override;
    void renderUI() noexcept;
    
    void setLevelNumber(int number);
private:
    cocos2d::Sprite* m_levelImg = nullptr;
    cocos2d::Sprite* m_levelTitle = nullptr;
    
    cocos2d::Label* m_labelLevel = nullptr;
};


#endif /* MapNodes_h */

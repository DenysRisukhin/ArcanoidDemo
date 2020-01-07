//
//  Barrier.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef Barrier_h
#define Barrier_h

#include <stdio.h>

class BarrierNode: public cocos2d::Node {
public:
    enum class BarrierState {
        ST_GREEN,
        ST_RED,
        ST_BLUE
    };
        
    bool init() override;
    
    void renderComponents();
    
    void setState(int state);
        
    BarrierState getState() const;
    std::string getTexture() const;
    cocos2d::Rect getRect() const;
   
    void changeState();
    
    bool isRemove() const;
    
private:
    cocos2d::Sprite* m_barrier = nullptr;
    cocos2d::Sprite* m_transparentHelperImg = nullptr;
    BarrierState m_state;
};

#endif /* Barrier_h */

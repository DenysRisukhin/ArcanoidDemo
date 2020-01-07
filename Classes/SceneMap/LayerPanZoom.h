//
//  LayerPanZoom.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#ifndef LayerPanZoom_h
#define LayerPanZoom_h

#include <stdio.h>

using namespace cocos2d;

class LevelNode;

class LayerPanZoom : public LayerColor
{
public:
    LayerPanZoom();
    virtual ~LayerPanZoom();
    
    static LayerPanZoom* create();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float dt);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    virtual void setPosition(Point position);
    void SetPanBoundsRect(Rect rect);
    
    virtual void setScale(float scale);
    void SetMaxScale(float maxScale);
    float GetMaxScale();
    void SetMinScale(float minScale);
    float GetMinScale();
    
    void Holding();
    void UnHolding();
    
    void SetProductFactor(float v);
    
private:
    EventListenerTouchOneByOne* m_touchListener = nullptr;
    LevelNode* m_levelNode = nullptr;
    
    Sprite* m_level = nullptr;
    Sprite* target = nullptr;
    
    Touch *touch1 = nullptr;
    Touch *touch2 = nullptr;
    
    Point m_beganTouchPoint;
    Point m_endedTouchPoint;
    Point m_deltaSum;
    Point m_prevDeltaPoint;
    
    Size m_screenSize;
    
    timeval m_timeStamp;
    Rect m_panBoundsRect;
    
    double m_accelerationFactor;
    
    float m_maxScale;
    float m_minScale;
    float m_productFactor;
    
    int m_touchCount;
    
    bool m_isHolding;
    bool m_touchMoveFlag;
    bool m_moveFlag;
    
    void moveToLevelNode();
};

#endif /* LayerPanZoom_h */

//
//  SceneMap.hpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#ifndef SceneMap_h
#define SceneMap_h

#include <stdio.h>

class LayerPanZoom;

class SceneMap: public cocos2d::Scene
{
public:
    CREATE_FUNC(SceneMap);
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void renderComponents();
    
private:
    cocos2d::Size m_screenWinSize;
    
    LayerPanZoom* ppLayer;
    //LayerPanZoom* holdLayer;
};

#endif /* SceneMap_h */

//
//  SceneMap.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#include "SceneMap.h"
#include "LayerPanZoom.h"
#include "BackgroundNode.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "UI.h"

USING_NS_CC;

Scene* SceneMap::createScene()
{
    auto scene = SceneMap::create();
    return scene;
}

bool SceneMap::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    m_screenWinSize = SceneManager::instance()->getWinSize();
    
    renderComponents();
    
    return true;
}

void SceneMap::renderComponents()
{
    Sprite* map = UI::sprite("map4");
    map->setOpacity( 150 );
    map->setAnchorPoint( Point( 0, 0 ) );
    map->setPosition( map->getContentSize() * -0.5 );
    
    ppLayer = LayerPanZoom::create();
    ppLayer->SetPanBoundsRect(Rect(map->getContentSize().width * -0.5, map->getContentSize().height * -0.5f, map->getContentSize().width * 1.0f, map->getContentSize().height * 1.0f));
    
    ppLayer->SetMaxScale(5.f);
    ppLayer->SetMinScale(0.65f);
    
    // important: set scale after min & max scale alredy fixed
    ppLayer->setScale(0.65f);
    ppLayer->setPosition(Vec2(m_screenWinSize.width/2, m_screenWinSize.height/2));
    ppLayer->addChild(map, -1);
    this->addChild(ppLayer);
}

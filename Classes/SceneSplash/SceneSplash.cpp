//
//  SceneSplash.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#include "SceneSplash.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "BackgroundNode.h"
#include "UI.h"
#include "SplashNodes.h"

USING_NS_CC;

namespace SplashZOrder {
    enum ZOrder {
        Title = 0,
        Label
    };
}

Scene* SceneSplash::createScene()
{
    auto scene = SceneSplash::create();
    return scene;
}

bool SceneSplash::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    SoundManager::instance()->init();
    m_screenWinSize = Director::getInstance()->getWinSize();
    
    renderComponents();
    
    this->scheduleOnce(schedule_selector(SceneSplash::runMainMenuScene), 5.f); // 1.f
    
    return true;
}

void SceneSplash::runMainMenuScene(float){
    SceneManager::instance()->runScene(SceneManager::SceneID::MainMenu);
}

void SceneSplash::renderComponents()
{
    m_titleImgNode = UI::create<TitleSplashNode>();
    m_titleImgNode->setScale(1.2f);
    m_titleImgNode->setPosition(Vec2(m_screenWinSize.width / 2.f, m_screenWinSize.height / 2.f));
    this->addChild(m_titleImgNode, SplashZOrder::Title);
    
    m_labelLoadingNode = UI::create<LoadingSplashNode>();
    m_labelLoadingNode->setPosition(Vec2(m_screenWinSize.width / 2.f, m_labelLoadingNode->getContentSize().height / 2.f));
    this->addChild(m_labelLoadingNode, SplashZOrder::Label);
}

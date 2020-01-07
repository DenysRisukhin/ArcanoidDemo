//
//  SceneResult.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "SceneResult.h"
#include "SceneManager.h"
#include "BackgroundNode.h"
#include "UI.h"
#include "ui/CocosGUI.h"
#include "ResultNodes.h"
#include "SoundManager.h"

USING_NS_CC;

namespace ResultZOrder {
    enum ZOrder {
        Background = 0,
        Node
    };
}

Scene* SceneResult::createScene(bool state, int score)
{
    auto scene = SceneResult::create();
    scene->setScore(score);
    scene->setResultGameState(state);
    return scene;
}

void SceneResult::setScore(int score)
{
    m_resultNode->setScore(score);
}

void SceneResult::setResultGameState(bool state)
{
    m_resultNode->setState(state);
    
    state ? SoundManager::instance()->playFx(SoundManager::FX::Win) :
            SoundManager::instance()->playFx(SoundManager::FX::Lose);
}

bool SceneResult::init()
{
    if (!Node::init())
    {
        return false;
    }

    m_screenWinSize = SceneManager::instance()->getWinSize();
    renderComponents();
    
    return true;
}

void SceneResult::renderComponents()
{
    auto backgroundImg = UI::create<BackgroundNode>(UI::img("background"), m_screenWinSize, kContentAspectFill);
    
    backgroundImg->setPosition(Vec2(m_screenWinSize.width / 2.f, m_screenWinSize.height / 2.f));
    this->addChild(backgroundImg, ResultZOrder::Background);
    
    m_resultNode = UI::create<ResultNode>();
    m_resultNode->setPosition(Vec2(m_screenWinSize.width / 2.f, m_screenWinSize.height / 2.f));
    m_resultNode->setTapCallback([this]()
    {
        SoundManager::instance()->playFx(SoundManager::FX::ButtonTap);
        SceneManager::instance()->runScene(SceneManager::SceneID::MainMenu);
    });
    this->addChild(m_resultNode, ResultZOrder::Node);
}




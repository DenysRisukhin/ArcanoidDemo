//
//  MainMenuNodes.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "MainMenuNodes.h"
#include "LocaleProvider.h"
#include "UI.h"
#include "UIFont.h"

USING_NS_CC;

bool ArcanoidTitleNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    renderUI();
    
    return true;
}

void ArcanoidTitleNode::renderUI() noexcept
{
    m_arcanoidTitleImg = UI::sprite("arkanoid");
    m_arcanoidTitleImg->setScale(0.35);
    this->addChild(m_arcanoidTitleImg);
    
    setAranoidTitleImgAnimation();
}

void ArcanoidTitleNode::setAranoidTitleImgAnimation()
{
    auto scaleTo = ScaleTo::create(1.5f, 0.56f);
    auto scaleBy = ScaleTo::create(1.5f, 0.65f);
    
    m_arcanoidTitleImg->runAction(RepeatForever::create(Sequence::create(scaleTo, scaleBy, nullptr)));
    
    this->setContentSize(m_arcanoidTitleImg->getContentSize());
}

#pragma mark - Start Node

bool StartButtonNode::init()
{
    if (!Node::init())
    {
        return false;
    }
        
    renderUI();
    
    return true;
}

void StartButtonNode::renderUI() noexcept
{
    m_startButton = ui::Button::create(UI::img("button"), UI::img("button_active"));
    m_startButton->setTitleText(LocaleProvider::instance()->loadString("startID"));
    m_startButton->setTitleFontName(UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium));
    m_startButton->setTitleFontSize(18.f);
    m_startButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED)
        {
            if (m_tapCallback)
            {
                m_tapCallback();
            }
        }
    });
    this->addChild(m_startButton);
    
    this->setContentSize(m_startButton->getContentSize());
}

void StartButtonNode::update()
{
    m_startButton->setTitleText(LocaleProvider::instance()->loadString("startID"));
}

#pragma mark - Settings Node

bool SettingsNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    renderUI();
    
    return true;
}

void SettingsNode::renderUI() noexcept
{
    m_settingsButton = ui::Button::create(UI::img("settings"), UI::img("settings_active"));
    m_settingsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED)
        {
            if (m_tapCallback)
            {
                m_tapCallback();
            }
        }
    });
    this->addChild(m_settingsButton);
    
    this->setContentSize(m_settingsButton->getContentSize());
}




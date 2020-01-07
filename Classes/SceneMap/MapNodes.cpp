//
//  MapNodes.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/17/19.
//

#include "MapNodes.h"

#include "LocaleProvider.h"
#include "UI.h"
#include "UIFont.h"

USING_NS_CC;

namespace LevelNodeZOrder {
    enum ZOrder {
        Button = 0,
        Label
    };
}

bool LevelNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    renderUI();
    
    return true;
}

void LevelNode::renderUI() noexcept
{
    m_levelImg = UI::sprite("level");
    m_levelImg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(m_levelImg, LevelNodeZOrder::Button);
    
    m_levelTitle = UI::sprite("buttonLevel");
    m_levelTitle->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    m_levelTitle->setPosition(Vec2(m_levelImg->getBoundingBox().size.width / 2.f - m_levelTitle->getBoundingBox().size.width / 2, m_levelImg->getBoundingBox().size.height));
    this->addChild(m_levelTitle, LevelNodeZOrder::Button);
    
    this->setContentSize(Size(m_levelImg->getBoundingBox().size.width, m_levelImg->getBoundingBox().size.height + m_levelTitle->getBoundingBox().size.height / 2.f));
    
    m_labelLevel = Label::createWithSystemFont(LocaleProvider::instance()->loadString("levelID"), UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium), 8);
    m_labelLevel->setColor(Color3B::BLACK);
    m_labelLevel->setAlignment(cocos2d::TextHAlignment::CENTER);
    m_labelLevel->setPosition(Vec2(m_levelTitle->getBoundingBox().size.width / 2.f, m_levelTitle->getBoundingBox().size.height / 2.f));
    m_levelTitle->addChild(m_labelLevel, LevelNodeZOrder::Label);
}

void LevelNode::setLevelNumber(int number)
{
    m_labelLevel->setString(LocaleProvider::instance()->loadString("levelID") + std::to_string(number));
}



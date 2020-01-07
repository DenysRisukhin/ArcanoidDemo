//
//  SplashNodes.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/16/19.
//

#include "SplashNodes.h"
#include "LocaleProvider.h"
#include "UI.h"
#include "UIFont.h"
#include "LabelFontAnimated.h"

USING_NS_CC;

bool TitleSplashNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    renderUI();
    
    this->setContentSize(Size(m_arcanoidSplashTitleImg->getBoundingBox().size.width, m_arcanoidSplashTitleImg->getBoundingBox().size.height));
    
    return true;
}

void TitleSplashNode::renderUI()
{
    m_arcanoidSplashTitleImg = UI::sprite("arcanoid2");
    this->addChild(m_arcanoidSplashTitleImg);
}

#pragma mark - Loading Splash Node

bool LoadingSplashNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    renderUI();
    
    this->setContentSize(Size(m_labelLoading->getContentSize().width, m_labelLoading->getContentSize().height));
    
    return true;
}

void LoadingSplashNode::renderUI()
{
    m_labelLoading = LabelFontAnimated::createWithTTF(
         LocaleProvider::instance()->loadString("loadingID"),
         UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium),
         35.f, Size(400, 55), TextHAlignment::CENTER, TextVAlignment::CENTER
    );
    m_labelLoading->setTextColor(Color4B::WHITE);
    this->addChild(m_labelLoading);
    
    auto tinToAction = TintTo::create(0, 0, 0, 0);
    m_labelLoading->runActionOnAllSprites(tinToAction);
    m_labelLoading->animateRainbow(0.5);
}

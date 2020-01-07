//
//  SettingsPageNode.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/16/19.
//

#include "SettingsPageNode.h"
#include "LocaleProvider.h"
#include "UI.h"
#include "UIFont.h"
#include "BackgroundNode.h"

USING_NS_CC;

namespace SettingsPageZOrder {
    enum ZOrder {
        Background = 8,
        Button,
    };
}

bool SettingsPageNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    m_screenWinSize = Director::getInstance()->getWinSize();
    renderUI();
    
    return true;
}

void SettingsPageNode::renderUI() noexcept
{
    this->setContentSize(Size(m_screenWinSize.width / 2.f, m_screenWinSize.height / 2.f));
    
    auto backgroundImg = UI::create<BackgroundNode>("settingsBg", this->getContentSize(), kContentAspectFill);
    this->addChild(backgroundImg, SettingsPageZOrder::Background);
    
    m_setRusLanguageButton = ui::Button::create(UI::img("button"), UI::img("button_active"));
    m_setRusLanguageButton->setPosition(Vec2(backgroundImg->getPositionX() / 2.f, backgroundImg->getPositionY() + m_setRusLanguageButton->getBoundingBox().size.height / 2.f));
    m_setRusLanguageButton->setTitleText(LocaleProvider::instance()->loadString("rusID"));
    m_setRusLanguageButton->setTitleFontName(UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium));
    m_setRusLanguageButton->setScale(0.7);
    m_setRusLanguageButton->setTitleFontSize(22.f);
    m_setRusLanguageButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED)
        {
            LocaleProvider::instance()->setCurrentLanguage("rus");
            updateLocale();
        }
    });
    this->addChild(m_setRusLanguageButton, SettingsPageZOrder::Button);
    
    m_setEngLanguageButton = ui::Button::create(UI::img("button"), UI::img("button_active"));
    m_setEngLanguageButton->setPosition(Vec2(backgroundImg->getPositionX() / 2.f, backgroundImg->getPositionY() - m_setRusLanguageButton->getBoundingBox().size.height) / 2.f);
    m_setEngLanguageButton->setTitleText(LocaleProvider::instance()->loadString("enID"));
    m_setEngLanguageButton->setTitleFontName(UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium));
    m_setEngLanguageButton->setScale(0.7);
    m_setEngLanguageButton->setTitleFontSize(22.f);
    m_setEngLanguageButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED)
        {
            LocaleProvider::instance()->setCurrentLanguage("en");
            updateLocale();
        }
    });
    this->addChild(m_setEngLanguageButton, SettingsPageZOrder::Button);
    
    m_closeButton = ui::Button::create(UI::img("close"), UI::img("close"));
    m_closeButton->setPosition(Vec2(this->getContentSize().width / 2.f - m_closeButton->getBoundingBox().size.width, this->getContentSize().height / 2.f - m_closeButton->getBoundingBox().size.height));
    m_closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED)
        {
            if (m_tapCallback)
            {
                m_tapCallback();
            }
        }
    });
    this->addChild(m_closeButton, SettingsPageZOrder::Button);
}

void SettingsPageNode::updateLocale()
{
     m_setEngLanguageButton->setTitleText(LocaleProvider::instance()->loadString("enID"));
    m_setRusLanguageButton->setTitleText(LocaleProvider::instance()->loadString("rusID"));
}

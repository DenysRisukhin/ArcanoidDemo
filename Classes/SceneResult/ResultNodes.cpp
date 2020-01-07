//
//  ResultNodes.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "ResultNodes.h"
#include "LocaleProvider.h"
#include "UI.h"
#include "UIFont.h"

#define shiftY 25.f

USING_NS_CC;
using namespace std;

namespace ResultNodeZOrder {
    enum ZOrder {
        Img = 1,
        Label,
        Button
    };
}

ResultNode::ResultNode()
{
    // do nothing
}

bool ResultNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    this->setContentSize(Size(1000, 1000));
    renderUI();
    
    return true;
}

void ResultNode::renderUI() 
{
    m_resultImg = UI::sprite("win");
    this->addChild(m_resultImg, ResultNodeZOrder::Img);

    m_resultLabel = Label::createWithSystemFont(LocaleProvider::instance()->loadString("winID"), UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium), 25);
    m_resultLabel->setAlignment(TextHAlignment::CENTER);
    m_resultLabel->setPositionY(this->getPosition().y + m_resultImg->getContentSize().height + m_resultImg->getContentSize().height / 3.f);
    this->addChild(m_resultLabel, ResultNodeZOrder::Label);
    
    m_scoreLabel = Label::createWithSystemFont(LocaleProvider::instance()->loadString("scoreID"), UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium), 18);
    m_scoreLabel->setAlignment(TextHAlignment::CENTER);
    m_scoreLabel->setPositionY(this->getPosition().y + m_resultImg->getContentSize().height / 1.3);
    this->addChild(m_scoreLabel, ResultNodeZOrder::Label);

    replayButton = ui::Button::create(UI::img("button"), UI::img("button_active"));
    replayButton->setPositionY(this->getPosition().y - m_resultImg->getContentSize().height);
    replayButton->setTitleText(LocaleProvider::instance()->loadString("replayID"));
    replayButton->setTitleFontName(UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium));
    replayButton->setTitleFontSize(24);
    replayButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        if (type == ui::Widget::TouchEventType::ENDED)
        {
            if (m_tapCallback)
            {
                m_tapCallback();
            }
        }
    });
    this->addChild(replayButton, ResultNodeZOrder::Button);
}

void ResultNode::setScore(int score)
{
    m_scoreLabel->setString(LocaleProvider::instance()->loadString("scoreID") + std::to_string(score));
}

void ResultNode::setState(bool state)
{
    m_resultImg->setTexture(state ? UI::img("win") : UI::img("lose"));
    m_resultLabel->setString(state ? LocaleProvider::instance()->loadString("winID")
                                   : LocaleProvider::instance()->loadString("loseID"));
}


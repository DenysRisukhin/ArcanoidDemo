//
//  SceneMainMenu.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "SceneMainMenu.h"
#include "BackgroundNode.h"
#include "UI.h"
#include "MainMenuNodes.h"
#include "LocaleProvider.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SettingsPageNode.h"

USING_NS_CC;

namespace MinMenuZOrder {
    enum ZOrder {
        Background = 0,
        Button,
        Title,
        SettingsNode
    };
}

Scene* SceneMainMenu::createScene()
{
    return SceneMainMenu::create();
}

bool SceneMainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    m_screenWinSize = SceneManager::instance()->getWinSize();
    SoundManager::instance()->startBGMusic(SoundManager::BGSound::MainMenu);

    renderComponents();
    
    return true;
}

void SceneMainMenu::renderComponents()
{
    auto backgroundImg = UI::create<BackgroundNode>("background", m_screenWinSize, kContentAspectFill);
    backgroundImg->setPosition(Vec2(m_screenWinSize.width / 2.f, m_screenWinSize.height / 2.f));
    this->addChild(backgroundImg, MinMenuZOrder::Background);
    
    m_arcanoidTitleNode = UI::create<ArcanoidTitleNode>();
    m_arcanoidTitleNode->setPosition(Vec2(m_screenWinSize.width/ 2.f, m_screenWinSize.height / 1.7));
    this->addChild(m_arcanoidTitleNode, MinMenuZOrder::Title);
    
    m_startButtonNode = UI::create<StartButtonNode>();
    m_startButtonNode->setPosition(Vec2(m_screenWinSize.width / 2.f, m_arcanoidTitleNode->getPosition().y - m_startButtonNode->getContentSize().height * 1.5));
    m_startButtonNode->setTapCallback([this]()
    {
        SoundManager::instance()->playFx(SoundManager::FX::ButtonTap);
        SoundManager::instance()->stopBGMusic();
        SceneManager::instance()->runScene(SceneManager::SceneID::Map);
    });
    this->addChild(m_startButtonNode, MinMenuZOrder::Button);
    
    m_settingsNode = UI::create<SettingsNode>();
    m_settingsNode->setPosition(Vec2(m_screenWinSize.width - m_settingsNode->getBoundingBox().size.width, m_screenWinSize.height - m_settingsNode->getBoundingBox().size.height));
    
     //m_settingsNode->setPosition(Vec2(m_screenWinSize.width / 3.f, m_screenWinSize.height / 3.f));
    
    m_settingsNode->setTapCallback([this]()
                                      {
                                          SoundManager::instance()->playFx(SoundManager::FX::ButtonTap);
                                          
                                          if (!m_settingsPageNode)
                                          {
                                              createSettingPage();
                                          }
                                         
                                      });
    this->addChild(m_settingsNode, MinMenuZOrder::Button);
}

void SceneMainMenu::createSettingPage()
{
    setVisible(false);
    
    m_settingsPageNode = UI::create<SettingsPageNode>();
    m_settingsPageNode->setPosition(Vec2(m_screenWinSize.width / 2.f, m_screenWinSize.height / 2.f));
    this->addChild(m_settingsPageNode, MinMenuZOrder::SettingsNode);
    m_settingsPageNode->setTapCallback([this]()
                                      {
                                          if (m_settingsPageNode)
                                          {
                                              m_settingsPageNode->removeFromParent();
                                              m_settingsPageNode = nullptr;
                                              
                                              setVisible(true);
                                              updateLocale();
                                          }
                                      });
}

void SceneMainMenu::setVisible(bool visible)
{
    m_startButtonNode->setVisible(visible);
    m_arcanoidTitleNode->setVisible(visible);
    m_settingsNode->setVisible(visible);
}

void SceneMainMenu::updateLocale()
{
    m_startButtonNode->update();
}

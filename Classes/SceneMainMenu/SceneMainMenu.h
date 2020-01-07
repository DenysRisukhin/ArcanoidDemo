//
//  SceneMainMenu.hpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef SceneMainMenu_h
#define SceneMainMenu_h

#include <stdio.h>
#include "cocos2d.h"

class ArcanoidTitleNode;
class StartButtonNode;
class SettingsNode;
class SettingsPageNode;

class SceneMainMenu: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void renderComponents();
    
    CREATE_FUNC(SceneMainMenu);
        
private:
    ArcanoidTitleNode* m_arcanoidTitleNode = nullptr;
    StartButtonNode* m_startButtonNode = nullptr;
    SettingsNode* m_settingsNode = nullptr;
    
    SettingsPageNode* m_settingsPageNode = nullptr;
    
    cocos2d::Size m_screenWinSize;
    
    void createSettingPage();
    void setVisible(bool visible);
    void updateLocale();
};

#endif /* SceneMainMenu_h */

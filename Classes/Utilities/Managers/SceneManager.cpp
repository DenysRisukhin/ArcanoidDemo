//
//  SceneManager.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "SceneSplash.h"
#include "SceneManager.h"
#include "SceneMainMenu.h"
#include "SceneInAction.h"
#include "SceneResult.h"
#include "SceneMap.h"

USING_NS_CC;
using namespace std;

SceneManager* SceneManager::m_instance = NULL;

SceneManager* SceneManager::instance()
{
    if (!m_instance)
    {
        m_instance = new SceneManager;
    }
    
    return m_instance;
}

void SceneManager::runScene(SceneID sceneID, bool isWin, int score)
{
    Scene *pScene = nullptr;
    
    switch(sceneID)
    {
        case SceneID::Splash:
            pScene = SceneSplash::create();
            break;
        case SceneID::Map:
            pScene = SceneMap::create();
            break;
        case SceneID::MainMenu:
            pScene = SceneMainMenu::create();
            break;
        case SceneID::InAction:
            pScene = SceneInAction::create();
            break;
        case SceneID::Result:
            pScene = SceneResult::createScene(isWin, score);
            break;
    }
    
    if(pScene)
    {
        Director::getInstance()->getRunningScene() ? Director::getInstance()->replaceScene(TransitionFade::create(0.5, pScene, Color3B(0, 0, 0))) :
                                                     Director::getInstance()->runWithScene(pScene);
    }
}

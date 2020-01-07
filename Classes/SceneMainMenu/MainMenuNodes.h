//
//  MainMenuNodes.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef MainMenuNodes_h
#define MainMenuNodes_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ArcanoidTitleNode: public cocos2d::Node
{
public:
    bool init() override;
    void renderUI() noexcept;
    
private:
    cocos2d::Sprite* m_arcanoidTitleImg = nullptr;
    
    void setAranoidTitleImgAnimation();
};

#pragma mark - Start Node

class StartButtonNode: public cocos2d::Node
{
public:
    using TapCallback = std::function<void()>;
    
    void setTapCallback(TapCallback callback) { m_tapCallback = std::move(callback); }
    
    bool init() override;
    void renderUI() noexcept;
    
    void update();
    
protected:
    TapCallback m_tapCallback;
    
private:
    cocos2d::ui::Button* m_startButton = nullptr;
};

#pragma mark - Settings Node

class SettingsNode: public cocos2d::Node
{
public:
    using TapCallback = std::function<void()>;
    
    void setTapCallback(TapCallback callback) { m_tapCallback = std::move(callback); }
    
    bool init() override;
    void renderUI() noexcept;
    
protected:
    TapCallback m_tapCallback;
    
private:
    cocos2d::ui::Button* m_settingsButton = nullptr;
};

#endif /* MainMenuNodes_h */

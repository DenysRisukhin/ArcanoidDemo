//
//  SettingsPageNode.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/16/19.
//

#ifndef SettingsPageNode_h
#define SettingsPageNode_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#pragma mark - Settings Page Node

class SettingsPageNode: public cocos2d::Node
{
public:
    using TapCallback = std::function<void()>;
    
    void setTapCallback(TapCallback callback) { m_tapCallback = std::move(callback); }
    
    bool init() override;
    void renderUI() noexcept;
    
protected:
    TapCallback m_tapCallback;
    
private:
    cocos2d::ui::Button* m_setEngLanguageButton = nullptr;
    cocos2d::ui::Button* m_setRusLanguageButton = nullptr;
    cocos2d::ui::Button* m_closeButton = nullptr;
    
    cocos2d::Size m_screenWinSize;
    
    void updateLocale();
};


#endif /* SettingsPageNode_h */

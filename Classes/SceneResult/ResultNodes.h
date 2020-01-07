//
//  ResultNodes.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef ResultNodes_h
#define ResultNodes_h

#include <stdio.h>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ResultNode: public cocos2d::Node
{
public:
    using TapCallback = std::function<void()>;
    
    void setTapCallback(TapCallback callback) { m_tapCallback = std::move(callback); }
    
    ResultNode();
    
    bool init() override;
    void renderUI();
    
    void setScore(int score);
    void setState(bool state);
    
protected:
    TapCallback m_tapCallback;
    
private:
    cocos2d::Sprite* m_resultImg = nullptr;
    
    cocos2d::Label* m_scoreLabel = nullptr;
    cocos2d::Label* m_resultLabel = nullptr;
    
    cocos2d::ui::Button* replayButton = nullptr;
    
    cocos2d::Size m_screenWinSize;
};

#endif /* ResultNodes_h */

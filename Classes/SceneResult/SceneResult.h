//
//  SceneResult.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef SceneResult_h
#define SceneResult_h

#include <stdio.h>

class ResultNode;

class SceneResult: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(bool isWin, int score);
    
    virtual bool init();
    
    void renderComponents();
    
    void setScore(int score);
    void setResultGameState(bool state);
    
    CREATE_FUNC(SceneResult);
    
private:
    ResultNode* m_resultNode = nullptr;

    int m_state;
//    cocos2d::Label* m_score = nullptr;
//    cocos2d::Label* m_resultLabel = nullptr;
//
    cocos2d::Size m_screenWinSize;
};

#endif /* SceneResult_h */

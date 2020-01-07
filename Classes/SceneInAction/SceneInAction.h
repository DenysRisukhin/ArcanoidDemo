//
//  SceneInAction.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef SceneInAction_h
#define SceneInAction_h

#include <stdio.h>
#include "cocos2d.h"

#include "GameFieldRect.h"
#include "Barrier.h"

class Ball;
class Platform;
class BarrierScaleNode;
class ScoreNode;

#pragma mark - Scene InAction

class SceneInAction: public cocos2d::Scene
{
public:
    CREATE_FUNC(SceneInAction);
    static cocos2d::Scene* createScene();
    virtual bool init();
    
private:
    cocos2d::Size m_screenWinSize;
};

#pragma mark - InAction Layer

class LayerInAction : public cocos2d::Layer
{
public:
    CREATE_FUNC(LayerInAction);
    LayerInAction();
  
    void update(float delta);
    
private:
    void gameOver(bool isWin);
    
    void initGameFieldRect();
    void initBarriers();
    void initGameFrame();
    void initWall(cocos2d::Vec2 position, cocos2d::Point anchor, bool isTopWall = false);
    void initBall();
    void initPlatform();
    
private:
    Ball* m_ball = nullptr;
    Platform* m_platform = nullptr;
    BarrierScaleNode* m_scaleBarriersNode = nullptr;
    
    ScoreNode* m_scoreNode = nullptr;
    
    GameFieldRect m_gameFieldRect;
    cocos2d::Size m_screenWinSize;
    cocos2d::Vec2 m_visibleOrigin;
    
    int m_barrierEraseCounter = 0;
    int m_score = 0;
    
    float m_gameframeWidth = 0.f;
    float m_gameFrameHeight = 0.f;
    
    bool enableTransition = true;
    
    void updateBallVelocity(float scalar);
    void updateScore();
    cocos2d::Point getBarrierPosition(int col, int row, BarrierNode* barrier);
};

#endif /* SceneInAction_h */

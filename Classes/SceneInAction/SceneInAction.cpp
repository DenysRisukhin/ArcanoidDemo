//
//  SceneInAction.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "SceneInAction.h"
#include "BackgroundNode.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameFieldRect.h"
#include "Ball.h"
#include "Barrier.h"
#include "Platform.h"
#include "InActionNodes.h"
#include "UI.h"

USING_NS_CC;
using namespace std;

#define scorePlatform 10
#define ballVelocityScalar 0.1f

#define startBallVelocityX (18.f * 1)
#define startBallVelocityY (80.f * 1)

#define columnBarrierAmount 5
#define rowBarrierAmount 15

#define updateBallVelocityMaxDestrVal 5

#define widthScreenIndent 16.f
#define heightScreenIndent 15.f

namespace InActionZOrder {
    enum ZOrder {
        Background = 0,
        Layer,
        Wall,
        Label,
        Ball,
        Barrier,
        Platform
    };
}

Scene* SceneInAction::createScene()
{
    return SceneInAction::create();
}

bool SceneInAction::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    SoundManager::instance()->startBGMusic(SoundManager::BGSound::InAction);
    
    m_screenWinSize = Director::getInstance()->getWinSize();
    
    auto backgroundImg = UI::create<BackgroundNode>(UI::img("background"), m_screenWinSize, kContentAspectFill);
    backgroundImg->setPosition(Vec2(m_screenWinSize.width / 2.f, m_screenWinSize.height / 2.f));
    this->addChild(backgroundImg, InActionZOrder::Background);

    auto layerInAction = LayerInAction::create();
    this->addChild(layerInAction, InActionZOrder::Layer);
    
    return true;
}

#pragma mark - InAction Layer

LayerInAction::LayerInAction()
{
    m_screenWinSize = SceneManager::instance()->getWinSize();
    m_visibleOrigin = SceneManager::instance()->getVisibleOrigin();
    
    initGameFieldRect();
    initBarriers();
    initGameFrame();
    initPlatform();
    initBall();
    
    m_scoreNode = UI::create<ScoreNode>();
    m_scoreNode->setPosition(Vec2(m_gameFieldRect.center().x, m_gameFieldRect.top().y + heightScreenIndent));
    this->addChild(m_scoreNode, InActionZOrder::Label);
    
    schedule(CC_SCHEDULE_SELECTOR(LayerInAction::update));
}

#pragma mark - init components

void LayerInAction::initGameFieldRect()
{
    auto widthLeftIndent = widthScreenIndent;
    auto widthRightIndent = widthLeftIndent * 2;
    m_gameFrameHeight = m_screenWinSize.height - widthRightIndent;
    
    m_gameFieldRect.setRect(Rect(m_visibleOrigin.x + widthLeftIndent, m_visibleOrigin.y, m_screenWinSize.width - widthRightIndent, m_gameFrameHeight));
    m_gameframeWidth = m_gameFieldRect.getGameFieldRect().getMaxX() - m_gameFieldRect.getGameFieldRect().getMinX();
}

void LayerInAction::initBarriers()
{
    m_scaleBarriersNode = UI::create<BarrierScaleNode>(m_gameframeWidth, columnBarrierAmount, rowBarrierAmount);
    this->addChild(m_scaleBarriersNode, InActionZOrder::Barrier);
   
    for (int col = 0; col < columnBarrierAmount; col++) {
        for (int row = 0; row < rowBarrierAmount; row++) {
            auto barrier = UI::create<BarrierNode>();
            auto barrierPosition = getBarrierPosition(row, col, barrier);
            barrier->setPosition(barrierPosition);
           
            m_scaleBarriersNode->push(barrier);
            m_scaleBarriersNode->addChild(barrier, InActionZOrder::Barrier);
        }
    }
    
    m_scaleBarriersNode->scale();
    
    m_scaleBarriersNode->setPosition(Vec2(m_gameFieldRect.left().x, m_scaleBarriersNode->getPositionY()));
}

Point LayerInAction::getBarrierPosition(int col, int row, BarrierNode* barrier)
{
    float barrierWidth = barrier->getContentSize().width / 2.f; 
    float barrierHeight = 0.f;
    
    int heightRowShiftDown = 3;
    
    if (col > 0) 
    {
        barrierWidth += col * barrier->getContentSize().width;
    }
    
    auto heightShift = barrier->getContentSize().height * (row + heightRowShiftDown);
    barrierHeight = m_gameFieldRect.top().y - heightShift - barrier->getContentSize().height / 2.f;
    
    return Point(barrierWidth, barrierHeight);
}

void LayerInAction::initGameFrame()
{
    // left
    Vec2 pos = Vec2(m_gameFieldRect.getGameFieldRect().getMinX(), m_gameFieldRect.getGameFieldRect().getMinY());
    initWall(pos, Point(1.f, 0.f));
    
    // right
    pos = Vec2(m_gameFieldRect.getGameFieldRect().getMaxX(), m_gameFieldRect.getGameFieldRect().getMinY());
    initWall(pos, Point(0.f, 0.f));
    
    // top
    pos = Vec2(m_gameFieldRect.getGameFieldRect().getMidX(), m_gameFieldRect.getGameFieldRect().getMaxY());
    initWall(pos, Point(0.5f, 0.f), true);
}

void LayerInAction::initWall(Vec2 position, Point anchor, bool isTopWall)
{
    Texture2D::TexParams texParams = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    
    auto wall = UI::sprite("tex");
    wall->setPosition(position);
    wall->setAnchorPoint(anchor);
    
    isTopWall ? wall->setTextureRect(cocos2d::Rect(0, 0, m_gameframeWidth + wall->getTexture()->getPixelsWide() * 2.f, wall->getTexture()->getPixelsHigh())) :
                wall->setTextureRect(cocos2d::Rect(0, 0, wall->getTexture()->getPixelsWide(), m_gameFrameHeight));
    
    wall->getTexture()->setTexParameters(texParams);
    this->addChild(wall, InActionZOrder::Wall);
}

void LayerInAction::initPlatform()
{
    auto platformTexture = Director::getInstance()->getTextureCache()->addImage(UI::img("platform"));
    
    m_platform = Platform::createWithTexture(platformTexture);
    m_platform->setPosition(Vec2(m_gameFieldRect.center().x, m_gameFieldRect.bottom().y + 15));
    m_platform->setMoveLimitPosX(m_gameFieldRect.left().x, m_gameFieldRect.right().x);
    this->addChild(m_platform, InActionZOrder::Platform);
}

void LayerInAction::initBall()
{
    auto ballTexture = Director::getInstance()->getTextureCache()->addImage(UI::img("ball"));
    
    m_ball = Ball::ballWithTexture(ballTexture);
    m_ball->setPosition(Vec2(m_gameFieldRect.center().x, m_platform->getPosition().y + m_platform->getContentSize().height + 5 ));
    m_ball->setVelocity(Vec2(startBallVelocityX, startBallVelocityY));
    m_ball->setTapCallback([this]()
    {
        m_ball->getFXsound() == Ball::FXsound::Wall ? SoundManager::instance()->playFx(SoundManager::FX::Wall)
                                                    : SoundManager::instance()->playFx(SoundManager::FX::Platform);
    });
    this->addChild(m_ball, InActionZOrder::Ball);
}

#pragma mark - handling objects movements & collisions

void LayerInAction::update(float delta)
{
    if (m_ball->getPosition().y < m_gameFieldRect.bottom().y - m_ball->getRadius())
    {
        gameOver(false);
        return;
    }
    
    m_ball->update(delta);
    m_ball->collideWithWalls(m_gameFieldRect);
    m_ball->collideWithPlatform(m_platform);
    
    for (auto iter = m_scaleBarriersNode->getBeginIter(); iter != m_scaleBarriersNode->getEndIter(); )
    {
        if (!m_ball->collideWithBarrier(iter->get(), m_gameFieldRect.left().x))
        {
            iter++;
            continue;
        }

        auto barrier = iter->get();

        if (barrier->isRemove())
        {
            iter = m_scaleBarriersNode->erase(iter);
            
            barrier->removeFromParent();
            barrier = nullptr;

            SoundManager::instance()->playFx(SoundManager::FX::BarrierCrash);

            updateScore();
            updateBallVelocity(ballVelocityScalar);

            auto isUserWin = m_scaleBarriersNode->isEmpty();
            if (isUserWin)
            {
                gameOver(true);
            }
        }
        else
        {
            SoundManager::instance()->playFx(SoundManager::FX::BarrierTouch);

            barrier->changeState();
            iter++;
        }
    }
}

void LayerInAction::updateScore()
{
    m_score += scorePlatform;
    m_scoreNode->updateScore(m_score);
}

void LayerInAction::updateBallVelocity(float scalar)
{
    ++m_barrierEraseCounter;
    
    if (m_barrierEraseCounter < updateBallVelocityMaxDestrVal)
    {
        log("ball velocity has just updated");
        
        auto curVelocity = m_ball->getVelocity() + m_ball->getVelocity() * scalar;
        m_ball->setVelocity(curVelocity);
        
        m_barrierEraseCounter = 0;
    }
}

void LayerInAction::gameOver(bool resultState)
{
    unscheduleUpdate();
    
    if (enableTransition)
    {
        enableTransition = false;
        SoundManager::instance()->stopBGMusic();
        SceneManager::instance()->runScene(SceneManager::SceneID::Result, resultState, m_score);
    }
}



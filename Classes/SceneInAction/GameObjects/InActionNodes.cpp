//
//  InActionNodes.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/14/19.
//

#include "InActionNodes.h"
#include "Barrier.h"
#include "UIFont.h"
#include "LocaleProvider.h"

USING_NS_CC;
using namespace std;

BarrierScaleNode::BarrierScaleNode(float gameframeWidth, int column, int row)
    : m_gameframeWidth(gameframeWidth), m_column(column), m_row(row)
{
    // do nothing
}

bool BarrierScaleNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
}

void BarrierScaleNode::push(BarrierNode* barrier)
{
    m_barriers.push_back(barrier);
}

void BarrierScaleNode::scale()
{
    bool isEmpty = m_barriers.empty();
    
    if (isEmpty)
    {
        return;
    }
    
    float curNodeWidth = m_barriers.begin()->get()->getContentSize().width * m_row;
    float curNodeHeight = m_barriers.begin()->get()->getContentSize().height * m_column;
    
    this->setContentSize(Size(curNodeWidth, curNodeHeight));

    log("curNodeWidth = %f", curNodeWidth);
    log("curNodeHeight = %f", curNodeHeight);
    log("m_gameframeWidth = %f", m_gameframeWidth);
    
    auto curNodeRect = this->getBoundingBox();
    auto targetNodeSize = Size(m_gameframeWidth, curNodeHeight);
    
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    
    Vec2 scaleVec = getScaleToFitScale(curNodeRect.size, targetNodeSize);
    scaleX = scaleVec.x;
    scaleY = scaleVec.y;
    
    this->setScale(scaleX, scaleY);
}

Vec2 BarrierScaleNode::getScaleToFitScale(cocos2d::Size &originSize, cocos2d::Size &fitSize)
{
    float ratioW = fitSize.width / originSize.width;
    float ratioH = fitSize.height / originSize.height;
    
    return Vec2(ratioW,ratioH);
}

BarrierScaleNode::barrierIter BarrierScaleNode::getBeginIter()
{
    return m_barriers.begin();
}

BarrierScaleNode::barrierIter BarrierScaleNode::getEndIter()
{
    return m_barriers.end();
}

bool BarrierScaleNode::isEmpty() const
{
    return m_barriers.empty();
}

int BarrierScaleNode::getBarrierSize() const
{
    return m_barriers.size();
}

BarrierScaleNode::barrierIter BarrierScaleNode::erase(barrierIter iter)
{
    return m_barriers.erase(iter);
}

#pragma mark - Score Node

bool ScoreNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    renderUI();
    
    this->setContentSize(Size(m_labelScore->getContentSize().width, m_labelScore->getContentSize().height));
    
    return true;
}

void ScoreNode::renderUI() 
{
    m_labelScore = Label::createWithSystemFont(LocaleProvider::instance()->loadString("scoreID") + std::to_string(0), UIFont::getFont(UIFont::Font::SFUIDisplay, UIFont::FontWeight::Medium), 18);
    m_labelScore->setAlignment(cocos2d::TextHAlignment::CENTER);
    this->addChild(m_labelScore);
}

void ScoreNode::updateScore(int value)
{
    m_labelScore->setString(LocaleProvider::instance()->loadString("scoreID") + std::to_string(value));
}

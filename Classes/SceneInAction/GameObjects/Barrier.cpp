//
//  Barrier.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include <ctime>
#include "SceneManager.h"
#include "Barrier.h"

USING_NS_CC;

bool BarrierNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    srand(time(NULL));
    setState(RandomHelper::random_int(1, 3));
    
    renderComponents();
    
    this->setContentSize(m_barrier->getContentSize());
    return true;
}

void BarrierNode::renderComponents()
{
    m_barrier = Sprite::create(getTexture());
    this->addChild(m_barrier);
    
    m_transparentHelperImg = Sprite::create(getTexture());
    this->addChild(m_transparentHelperImg);
    m_transparentHelperImg->setScale(2.f);
    m_transparentHelperImg->setOpacity(256);
}

void BarrierNode::setState(int state) {
    switch(state) {
        case 1:
            m_state = BarrierState::ST_GREEN;
            break;
        case 2:
            m_state = BarrierState::ST_RED;
            break;
        case 3:
            m_state = BarrierState::ST_BLUE;
            break;
    }
}

std::string BarrierNode::getTexture() const
{
    switch(m_state) {
        case BarrierState::ST_GREEN:
            return "barrier_green.png";
            break;
        case BarrierState::ST_RED:
            return "barrier_red.png";
            break;
        case BarrierState::ST_BLUE:
            return "barrier_blue.png";
            break;
        default:
            return "barrier_blue.png";
            break;
    }
}

Rect BarrierNode::getRect() const
{
    auto width = this->getContentSize().width * getParent()->getScaleX();
    auto height = this->getContentSize().height * getParent()->getScaleY();
    
    return Rect(-width / 2.f, -height / 2.f, width, height);
}

BarrierNode::BarrierState BarrierNode::getState() const
{
    return m_state;
}

void BarrierNode::changeState()
{
    if (getState() == BarrierState::ST_BLUE)
    {
        m_barrier->setTexture("barrier_red.png");
        m_state = BarrierState::ST_RED;
    }
    else if (getState() == BarrierState::ST_RED)
    {
        m_barrier->setTexture("barrier_green.png");
        m_state = BarrierState::ST_GREEN;
    }
}

bool BarrierNode::isRemove() const
{
    return m_state == BarrierState::ST_GREEN ? true : false;
}


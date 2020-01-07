//
//  LayerPanZoom.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#include "LayerPanZoom.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "ui/CocosGUI.h"
#include "LocaleProvider.h"
#include "UI.h"
#include "MapNodes.h"

#define kMaxScale -5

LayerPanZoom::LayerPanZoom() {}

LayerPanZoom::~LayerPanZoom() {}

LayerPanZoom* LayerPanZoom::create()
{
    auto pRet = new LayerPanZoom;
    
    if(pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool LayerPanZoom::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 0, 0, 0)))
        return false;
    
    this->setAnchorPoint(Vec2(0,0));
    m_screenSize = Director::getInstance()->getWinSize();
    
    m_accelerationFactor = 0.f;
    m_productFactor = 55.f;
    
   // m_maxScale = 4.5f;
   // m_minScale = 0.f;
   // this->setScale(0.65f);
    
    m_isHolding = false;
    
    return true;
}

void LayerPanZoom::onEnter()
{
    Layer::onEnter();
    
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
    
    m_touchListener = EventListenerTouchOneByOne::create();
    m_touchListener->setSwallowTouches(true);
    m_touchListener->onTouchBegan = CC_CALLBACK_2(LayerPanZoom::onTouchBegan, this);
    m_touchListener->onTouchMoved = CC_CALLBACK_2(LayerPanZoom::onTouchMoved, this);
    m_touchListener->onTouchEnded = CC_CALLBACK_2(LayerPanZoom::onTouchEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
    
    m_levelNode = UI::create<LevelNode>();
    m_levelNode->setPosition(Vec2(0.f, 0.f));
    m_levelNode->setLevelNumber(1);
    this->addChild(m_levelNode);
    m_levelNode->setLocalZOrder(200);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener->clone(), m_levelNode);
    
    moveToLevelNode();
}

void LayerPanZoom::moveToLevelNode()
{
    this->runAction(ScaleTo::create(1, 5.f));
    
    Point p = m_levelNode->getPosition() + m_levelNode->getContentSize() / 2.f;
    p.y += 15.f;
    
    this->runAction(MoveTo::create(1,  Vec2( (p.x - m_screenSize.width * 0.1f) * kMaxScale, (p.y - m_screenSize.height * 0.1f) * kMaxScale)));
}


void LayerPanZoom::onExit()
{
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    Layer::onExit();
}

bool LayerPanZoom::onTouchBegan(Touch* touch, Event* event)
{
    if(m_isHolding)
    {
        return false;
    }
    
    m_touchCount = 0;
    m_deltaSum = Vec2( 0, 0 );
    m_accelerationFactor = 0;
    
    if (touch->getID() <= 1)
    {
        log("_touchCount = %i",m_touchCount++);
        m_moveFlag = false;
        
        target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode) || rect.containsPoint(this->getContentSize()))
        {
            touch1 = touch;
            
            log("touch1 = touch");
            
            return true;
        }
        
    }
    
    return false;
}

void LayerPanZoom::onTouchMoved(Touch* touch, Event* event)
{
    if (m_isHolding)
    {
        return;
    }
    
    m_moveFlag = true;
    
    if (touch->getID() == 0)
    {
        log("1 touch");
        
        Vec2 curTouchPosition = Director::getInstance()->convertToGL(touch->getLocationInView());
        Vec2 prevTouchPosition = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
        Vec2 deltaPosition = curTouchPosition - prevTouchPosition;
        
        m_touchMoveFlag = false;
        
        this->setPosition(this->getPosition() + deltaPosition);
        
        float prevAngle = CC_RADIANS_TO_DEGREES( m_prevDeltaPoint.getAngle() );
        float angle = CC_RADIANS_TO_DEGREES( deltaPosition.getAngle() );
        if( fabs( prevAngle - angle ) <= 30 )
        {
            m_deltaSum = Vec2( 0, 0 );
        }

        m_prevDeltaPoint = deltaPosition;

        m_deltaSum.x = m_deltaSum.x + deltaPosition.x / this->getContentSize().width;
        m_deltaSum.y = m_deltaSum.y + deltaPosition.y / this->getContentSize().height;

        m_accelerationFactor += m_deltaSum.getLength() * 4.0;
        
        touch1 = touch;
    }
    else if (m_touchCount == 1)
    {
        log("2 touch");

        touch2 = touch;
        
        if (touch2 == touch1)
        {
            log("touches error");
        }
        else
        {
            // Get current and previous positions of the touches
            Vec2 curPosTouch1 = Director::getInstance()->convertToGL(touch1->getLocationInView());
            Vec2 curPosTouch2 = Director::getInstance()->convertToGL(touch2->getLocationInView());
            
            Vec2 prevPosTouch1 = Director::getInstance()->convertToGL(touch1->getPreviousLocationInView());
            Vec2 prevPosTouch2 = Director::getInstance()->convertToGL(touch2->getPreviousLocationInView());
            
            // Calculate current and previous positions of the layer relative the anchor point
            Vec2 curPosLayer = curPosTouch1.getMidpoint(curPosTouch2);
            Vec2 prevPosLayer = prevPosTouch1.getMidpoint(prevPosTouch2);
            log("curPosLayer %f %f", curPosLayer.x, curPosLayer.y);
            log("prevPosLayer %f %f", prevPosLayer.x, prevPosLayer.y);
            
            // Calculate new scale
            float prevScale = this->getScale();
            float curScale = this->getScale() * curPosTouch1.distance(curPosTouch2) / prevPosTouch1.distance(prevPosTouch2);
            
            this->setScale( curScale );
            
            if( this->getScale() != prevScale )
            {
                Point realCurPosLayer = this->convertToNodeSpaceAR(curPosLayer);
                float deltaX = (realCurPosLayer.x) * (this->getScale() - prevScale);
                float deltaY = (realCurPosLayer.y) * (this->getScale() - prevScale);
                
                this->setPosition(Vec2(this->getPosition().x - deltaX, this->getPosition().y - deltaY));
            }
            
            // If current and previous position of the multitouch's center aren't equal -> change position of the layer
            if (!prevPosLayer.equals(curPosLayer))
            {
                this->setPosition(Vec2(this->getPosition().x + curPosLayer.x - prevPosLayer.x,
                                      this->getPosition().y + curPosLayer.y - prevPosLayer.y));
            }
        }
    }
}

void LayerPanZoom::onTouchEnded(Touch* touch, Event* event)
{
    if(m_isHolding)
    {
        return;
    }
    
    auto target = static_cast<LevelNode*>(event->getCurrentTarget());
    auto locationInNode = target->convertToNodeSpace(touch->getLocation());
    auto s = target->getContentSize();
    auto rect = Rect(0, 0, s.width, s.height);
    
    if (m_moveFlag == false)
    {
        if (m_levelNode == target)
        {
            SoundManager::instance()->playFx(SoundManager::FX::ButtonTap);
            SoundManager::instance()->stopBGMusic();
            SceneManager::instance()->runScene(SceneManager::SceneID::InAction);
            
            return;
        }
    }
    
    m_touchCount--;
}

void LayerPanZoom::update(float dt)
{
    // Skip smoothe panning when dt is high value
    if (dt > 1.f / 55)
    {
        return;
    }
    
    LayerColor::update(dt);
    
    if (m_touchCount == 1) {
        m_accelerationFactor *= 40 * dt * 0.95f;
    }
    else if (m_touchCount == 0)
    {
        m_accelerationFactor = fabs(m_accelerationFactor - 0);
        
        if (m_accelerationFactor < FLT_EPSILON)
        {
            return;
        }
        
        if (m_accelerationFactor < 0.004f)
        {
            m_accelerationFactor = 0;
        }
        else
        {
            double d = dt * 60;
            if (d > 0.99) d = 0.99;
            double i = (0 - m_accelerationFactor) * 0.025 * d;
            
            m_accelerationFactor = (m_accelerationFactor + i) * d;
            
            Vec2 adder = m_deltaSum;
            adder.x *= this->getContentSize().width;
            adder.y *= this->getContentSize().height;
            
            this->setPosition(this->getPosition() + adder * 2.5 * m_accelerationFactor);
        }
    }
}

void LayerPanZoom::setPosition(Point position)
{
    Node::setPosition(position);
    
    if( m_panBoundsRect.equals(Rect::ZERO) == false )
    {
        Rect boundBox;
        boundBox.origin = this->getPosition() / this->getScale();
        boundBox.size = this->getContentSize() / this->getScale();
        //log("boundBox : origin(%.1f, %.1f), size(%.1f, %.1f)", boundBox.origin.x, boundBox.origin.y, boundBox.size.width, boundBox.size.height);
        
        // OpenGL coordinate system
        float left = boundBox.getMinX();
        float right = boundBox.getMaxX();
        float top = boundBox.getMaxY();
        float bottom = boundBox.getMinY();
        //log("left,right(%.1f, %.1f), top,bottom(%.1f, %.1f)", left, right, top, bottom);
        
        float min_x = m_panBoundsRect.getMinX() + boundBox.size.width;
        float max_x = m_panBoundsRect.getMaxX() + boundBox.size.width;
        float min_y = m_panBoundsRect.getMinY() + boundBox.size.height;
        float max_y = m_panBoundsRect.getMaxY() + boundBox.size.height;
        //log("min(%.1f, %.1f), max(%.1f, %.1f)", min_x, min_y, max_x, max_y);
        
        float scale = this->getScale();
        float arLeft = min_x * scale;
        float arRight = max_x * scale - this->getContentSize().width;
        float arTop = max_y * scale - this->getContentSize().height;
        float arBottom = min_y * scale;
        
        if (left < min_x)
        {
            Node::setPosition(arLeft, this->getPosition().y);
        }
        
        if (right > max_x)
        {
            Node::setPosition(arRight, this->getPosition().y);
        }
        
        if (top > max_y)
        {
            Node::setPosition(this->getPosition().x, arTop);
        }
        
        if (bottom < min_y)
        {
            Node::setPosition(this->getPosition().x, arBottom);
        }
    }
}


void LayerPanZoom::setScale(float scale)
{
    LayerColor::setScale(MIN( MAX( scale, m_minScale), m_maxScale));
    this->setPosition(this->getPosition());
}

void LayerPanZoom::SetPanBoundsRect(Rect rect)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    m_panBoundsRect = rect;
    
    auto wFactor = m_panBoundsRect.size.width / visibleSize.width;
    auto hFactor = m_panBoundsRect.size.height / visibleSize.height;
    float minScale;
    
    if (wFactor > hFactor)
    {
        minScale = wFactor;
    }
    else
    {
        minScale = hFactor;
    }
    
    SetMinScale(minScale);
}

void LayerPanZoom::SetMaxScale(float maxScale)
{
    m_maxScale = maxScale;
}

float LayerPanZoom::GetMaxScale()
{
    return m_maxScale;
}

void LayerPanZoom::SetMinScale(float minScale)
{
    m_minScale = minScale;
}

float LayerPanZoom::GetMinScale()
{
    return m_minScale;
}

void LayerPanZoom::Holding()
{
    m_isHolding = true;
}

void LayerPanZoom::UnHolding()
{
    m_isHolding = false;
}

void LayerPanZoom::SetProductFactor(float v)
{
    m_productFactor = v;
}

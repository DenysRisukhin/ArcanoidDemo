//
//  BackgroundNode.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "BackgroundNode.h"
#include <stdio.h>
#include "UI.h"

USING_NS_CC;

BackgroundNode::BackgroundNode(const std::string name, Size size, ImageNodeContentMode contentMode)
{
    m_image = UI::sprite(name);
    m_image->setAnchorPoint(Vec2(0.5, 0.5));
    m_mode = contentMode;
    m_size = size;
}

bool BackgroundNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    Rect rect = m_image->getTextureRect();
    
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    
    switch (m_mode) {
        case kContentAspectFill:
            scaleX = scaleY = BackgroundNode::getAspectFillScale(rect.size, m_size);
            break;
            
        case kContentAspectFit:
            scaleX = scaleY = BackgroundNode::getAspectFitScale(rect.size, m_size);
            break;
            
        case kContentScaleToFit:
            Vec2 scaleVec = BackgroundNode::getScaleToFitScale(rect.size, m_size);
            scaleX = scaleVec.x;
            scaleY = scaleVec.y;
            break;
    }
    
    m_image->setScale(scaleX, scaleY);
    this->addChild(m_image);
    
    m_image->setGlobalZOrder(-10);
    
    return true;
}

#pragma mark - static

Vec2 BackgroundNode::getScaleToFitScale(Size &originSize, Size &fitSize)
{
    // Calculate resize ratios for resizing
    float ratioW = fitSize.width / originSize.width;
    float ratioH = fitSize.height / originSize.height;
    
    return Vec2(ratioW,ratioH);
}

float BackgroundNode::getAspectFitScale(Size &originSize, Size &fitSize)
{
    // Calculate resize ratios for resizing
    float ratioW = fitSize.width / originSize.width;
    float ratioH = fitSize.height / originSize.height;
    
    // smaller ratio will ensure that the image fits in the view
    return (ratioW < ratioH ? ratioW : ratioH);
}

float BackgroundNode::getAspectFillScale(Size &originSize, Size &fillSize)
{
    // Calculate resize ratios for resizing
    float ratioW = fillSize.width / originSize.width;
    float ratioH = fillSize.height / originSize.height;
    
    // bigger ratio will ensure that the image fill in the view
    return (ratioW > ratioH ? ratioW : ratioH);
}


//
//  InActionNodes.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/14/19.
//

#ifndef InActionNodes_h
#define InActionNodes_h

#include <stdio.h>
#include <cocos2d.h>
#include <list>
#include "SharedRef.h"

class BarrierNode;

class BarrierScaleNode: public cocos2d::Node
{
public:
    
    using barrierIter = std::list<SharedRef<BarrierNode>>::iterator;
    
    BarrierScaleNode(float gameframeWidth, int column, int row);
    
    bool init() override;
    
    void push(BarrierNode* barrier);
    
    barrierIter getBeginIter();
    barrierIter getEndIter();
    int getBarrierSize() const;
    
    bool isEmpty() const;
    barrierIter erase(barrierIter iter);
    
    void scale();
    
private:
    std::list<SharedRef<BarrierNode>> m_barriers;
    
    float m_gameframeWidth;
    int m_column;
    int m_row;
    
    cocos2d::Vec2 getScaleToFitScale(cocos2d::Size &originSize, cocos2d::Size &fitSize);
};

#pragma mark - Score Node

class ScoreNode: public cocos2d::Node
{
public:
    bool init() override;
    void renderUI();
    
    void updateScore(int value);
    
private:
    cocos2d::Label* m_labelScore = nullptr;
};


#endif /* InActionNodes_h */

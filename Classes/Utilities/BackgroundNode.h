//
//  BackgroundNode.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef BackgroundNode_h
#define BackgroundNode_h

#include <stdio.h>

enum ImageNodeContentMode {
    kContentScaleToFit, // scale to image initial size
    kContentAspectFit, // all image on screen with borders
    kContentAspectFill // all initial size fill with image (without borders)
};


// Makes sprite with concrete size and scale modes.
class BackgroundNode: public cocos2d::Node
{
public:
    BackgroundNode(const std::string imageName, cocos2d::Size size, ImageNodeContentMode contentMode = kContentScaleToFit);
    
    bool init() override;
        
    // scale methods
    static cocos2d::Vec2 getScaleToFitScale(cocos2d::Size &originSize, cocos2d::Size &fitSize);
    static float getAspectFitScale(cocos2d::Size &originSize, cocos2d::Size &fitSize);
    static float getAspectFillScale(cocos2d::Size &originSize, cocos2d::Size &fillSize);
    
private:
    cocos2d::Sprite* m_image = nullptr;
    ImageNodeContentMode m_mode;
    cocos2d::Size m_size;
    
    // Scale imageSprite with choosen content mode 
    void adjustSize();
};

#endif /* BackgroundNode_h */

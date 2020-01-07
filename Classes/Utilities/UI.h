//
//  UI.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#ifndef UI_h
#define UI_h

#include <stdio.h>

// We need namespace for UI due to conflict with UI typedef structure from OpenSSL
class UI
{
public:
    enum ExtensionType {
        Default = 0,
        WEBP,
        PNG,
        JPG
    };
    
    static cocos2d::Sprite* sprite();
    static cocos2d::Sprite* sprite(const std::string& srcImageName);
    static cocos2d::Sprite* sprite(const std::string& srcImageName, ExtensionType type, const cocos2d::Rect& rect = cocos2d::Rect());
   
    static std::string img(const std::string& srcImageName);
    static std::string img(const std::string& srcImageName, ExtensionType type);
    static std::string getExtension(ExtensionType type);
    
    template<typename T, typename... Args>
    static T* create(Args&&... args)
    {
        T* node = new T(std::forward<Args>(args)...);
        if (node->init())
        {
            node->autorelease();
        }
        else
        {
            delete node;
            node = nullptr;
        }
        return node;
    }
    
private:
    static cocos2d::Sprite* createSpriteFromFile(const std::string& srcImageName, const cocos2d::Rect& rect);
};

#endif /* UI_h */

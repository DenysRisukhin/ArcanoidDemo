//
//  UI.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/11/19.
//

#include "UI.h"

USING_NS_CC;
using namespace std;

const UI::ExtensionType DefaultExtensionType = UI::ExtensionType::PNG; // PNG or WEBP

Sprite* UI::sprite()
{
    return Sprite::create();
}

Sprite* UI::sprite(const string& srcImageName)
{
    return UI::sprite(srcImageName, ExtensionType::PNG);
}

Sprite* UI::createSpriteFromFile(const string& srcImageName, const Rect& rect)
{
    if (rect.size.width > 0 && rect.size.height > 0)
    {
        return Sprite::create(srcImageName, rect);
    }
    else
    {
        return Sprite::create(srcImageName);
    }
}

Sprite* UI::sprite(const string& srcImageName, ExtensionType type, const Rect& rect)
{
    if (srcImageName.empty())
    {
        return nullptr;
    }
    
    string str = srcImageName;
    string strTexture = srcImageName;
    
    if (srcImageName.find(".png") == string::npos)
    {
        str = UI::img(srcImageName, type);
        strTexture = UI::img(srcImageName);
    }
    
    return  createSpriteFromFile(str, rect);
}

string UI::img(const string& srcImageName)
{
    return UI::img(srcImageName, ExtensionType::Default);
}

string UI::img(const string& srcImageName, ExtensionType type)
{
    if (srcImageName.find(".") != string::npos)
    {
        return srcImageName;
    }
    
    return srcImageName + UI::getExtension(type);
}

string UI::getExtension(ExtensionType type)
{
    switch (type) {
        case ExtensionType::WEBP:
            return ".webp";
        case ExtensionType::PNG:
            return ".png";
        case ExtensionType::JPG:
            return ".jpg";
        case ExtensionType::Default:
        default:
        {
            if (DefaultExtensionType == ExtensionType::PNG)
            {
                return ".png";
            }
        }
    }
}

//
//  UIFont.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/17/19.
//

#ifndef UIFont_h
#define UIFont_h

#include <stdio.h>

class UIFont
{
public:
    
    enum class Font
    {
        SFUIDisplay = 0
    };
    
    enum class FontWeight
    {
        Regular = 0,
        Medium,
        Bold
    };
    
    static std::string getFont(Font font, FontWeight weight);    
};

#endif /* UIFont_h */

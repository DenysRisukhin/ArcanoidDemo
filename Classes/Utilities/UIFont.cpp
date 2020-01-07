//
//  UIFont.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/17/19.
//

#include "UIFont.h"
using namespace std;

string UIFont::getFont(Font font, FontWeight weight)
{
    switch (font) {
        case Font::SFUIDisplay:
            
            switch (weight) {
                case FontWeight::Regular:
                    return "";
                case FontWeight::Medium:
                    return "fonts/SFUIDisplayMedium.otf";
                case FontWeight::Bold:
                    return "";
            }
    }
    return "";
}

//
//  LocaleProvider.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#ifndef LocaleProvider_h
#define LocaleProvider_h

#include <stdio.h>
#include "XmlParser.h"
#include "cocos2d.h"
#include <map>

class LocaleProvider {
public:
    typedef std::map<std::string, std::string> resourcesCache;
    typedef resourcesCache::iterator resourcesCachIt;
    
    static LocaleProvider* instance();
    
    void setCurrentLanguage(cocos2d::__String language);
    
    const char* loadString(cocos2d::__String resourceId);
    const char* loadString(cocos2d::__String resourceId, cocos2d::__String language);
    
protected:
    LocaleProvider();
    ~LocaleProvider(){}
    
private:
    XmlParser* m_parser = nullptr;
    
    cocos2d::__String m_curLanguage;
    
    resourcesCache m_resourcesCache;
    
    std::string addNewLineCharacters(std::string str);
};

#endif /* LocaleProvider_h */

//
//  LocaleProvider.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#include "LocaleProvider.h"

LocaleProvider* LocaleProvider::instance() {
    static LocaleProvider provider;
    return &provider;
}

LocaleProvider::LocaleProvider() {
    m_parser = XmlParser::instance();
    m_parser->load("localization.xml");
}

void LocaleProvider::setCurrentLanguage(cocos2d::__String language) {
    m_curLanguage = language;
}

const char* LocaleProvider::loadString(cocos2d::__String resourceId) {
    return LocaleProvider::loadString(resourceId, m_curLanguage);
}

const char* LocaleProvider::loadString(cocos2d::__String resourceId, cocos2d::__String language) {
    char buffer[1500];
    sprintf(buffer, "%s%s", resourceId._string.c_str(), language._string.c_str());
    
    resourcesCachIt findResult = m_resourcesCache.find(buffer);
    if (findResult == m_resourcesCache.end()) {
        m_resourcesCache[buffer] = addNewLineCharacters(m_parser->getString(resourceId._string, language._string));
        return m_resourcesCache[buffer].c_str();
    } else {
        return findResult->second.c_str();
    }
}

std::string LocaleProvider::addNewLineCharacters(std::string string)
{
    const char* pattern = "\\n";
    if (string.find(pattern) != -1)
        return string.replace(string.find(pattern), 2, "\n");
    else
        return string;
}

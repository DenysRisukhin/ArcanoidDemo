//
//  XmlParser.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#ifndef XmlParser_h
#define XmlParser_h

#include "pugixml.hpp"
#include <string>

class XmlParser
{
    pugi::xml_document m_Doc;
    
public:
    static XmlParser* instance();
    
    void load(std::string fileName);
    std::string getString(std::string id, std::string language);
    
protected:
    XmlParser() {}
    ~XmlParser() {}
};

#endif /* XmlParser_h */

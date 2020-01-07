//
//  XmlParser.cpp
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/13/19.
//

#include "XmlParser.h"
#include "Utilities.h"

XmlParser* XmlParser::instance()
{
    static XmlParser parser;
    return &parser;
}

void XmlParser::load(std::string fileName)
{
    std::string resultPath;
    
    std::string resourseFolder = resoursesFolder();
    
#ifdef _WIN32
    resultPath = fileName;
#else
    resultPath = resourseFolder + "/" + fileName;
#endif
    
    pugi::xml_parse_result result = m_Doc.load_file(resultPath.c_str());
    //log(result.description());
}

std::string XmlParser::getString(std::string id, std::string language)
{
    pugi::xml_node strings = m_Doc.first_child();
    pugi::xml_node string = strings.find_child_by_attribute("string", "id", id.c_str());
    return string.find_child_by_attribute("localization", "lang", language.c_str()).text().get();
}

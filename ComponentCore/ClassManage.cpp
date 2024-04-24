#include "ClassManage.h"
#include "ObjectFactory.h"
#include "StringUtils.h"
//inline static bool OnStartsWith(const std::string& value, const std::string& start, bool case_sensitive = true) 
//{
//    if (start.length() > value.length()) 
//        return false;
//
//    if (case_sensitive) 
//        return std::equal(start.begin(), start.end(), value.begin());
//
//    return std::equal(start.begin(), start.end(), value.begin(), [](unsigned char lc, unsigned char rc) {return tolower(lc) == tolower(rc); });
// }
//
//inline static bool OnEndsWith(const std::string& value, const std::string& end, bool case_sensitive = true)
//{
//    if (end.length() > value.length())
//        return false;
//
//    if (case_sensitive)
//        return std::equal(end.rbegin(), end.rend(), value.rbegin());
//
//    return std::equal(end.rbegin(), end.rend(), value.rbegin(), [](unsigned char lc, unsigned char rc) {return tolower(lc) == tolower(rc); });
//}
//
//static inline std::string OnGetClassName(const std::string strName)
//{
//    const std::string strClassPrefix = "class ";
//    const std::string strStructPrefix = "struct ";
//    const std::string strEnumPrefix = "enum ";
//
//    if (StringUtils::startsWith(strName, strClassPrefix))
//        return StringUtils::trimLeft(strName, strClassPrefix);
//
//    else if (StringUtils::startsWith(strName, strStructPrefix))
//        return StringUtils::trimLeft(strName.substr(strStructPrefix.length()));
//
//    else if (StringUtils::startsWith(strName, strEnumPrefix))
//        return StringUtils::trimLeft(strName.substr(strEnumPrefix.length()));
//
//    return strName;
//
//}



ClassManage::ClassManage()
{

}

ClassManage& ClassManage::getDefaultClassManage() {
	static ClassManage ret;
	// populate ret
	return ret;
}


void ClassManage::registerClass(const std::string strClassName, std::unique_ptr<ObjectFactory> objFactory)
{
    std::lock_guard<std::mutex> lock(internal_mutex_);
    if (strClassName.empty())
        return;
    std::string strClass = StringUtils::getTypeName2WithDot(strClassName);
    if (m_mapClassManage.find(strClass) != m_mapClassManage.end()) {
        return;
    }
    m_mapClassManage.insert(std::make_pair(strClass, std::move(objFactory)));
}

std::unique_ptr<ObjectClass> ClassManage::CreateObject(std::string strClassName)
{
    std::lock_guard<std::mutex> lock(internal_mutex_);
    if (strClassName.empty())
        return nullptr;
    std::string strClass = StringUtils::getTypeName2WithDot(strClassName);
    if(m_mapClassManage.find(strClass) != m_mapClassManage.end())
        return std::move(m_mapClassManage[strClass]->createObject());
    return nullptr;
}

std::unique_ptr<ObjectClass> ClassManage::createObjectClass(std::string strClassName)
{
    if (strClassName.empty())
        return nullptr;
    return std::move(ClassManage::getDefaultClassManage().CreateObject(strClassName));
}

void ClassManage::unregisterClass(const std::string strClassName)
{
    std::lock_guard<std::mutex> lock(internal_mutex_);
    if (strClassName.empty())
        return;
    std::string strClass = StringUtils::getTypeName2WithDot(strClassName);
    m_mapClassManage.erase(strClass);
}

void ClassManage::unregisterClass()
{
    std::lock_guard<std::mutex> lock(internal_mutex_);
    m_mapClassManage.clear();
}
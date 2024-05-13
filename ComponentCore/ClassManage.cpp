#include "ClassManage.h"
#include "ObjectFactory.h"
#include "StringUtils.h"
#include "ObjectClass.h"
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

//ClassManage::ClassManage()
//{
//
//}
/************************************************************************************************************************/
template <typename T_To, typename T_From>
static inline std::unique_ptr<T_To> DynamicUniqueCast(std::unique_ptr<T_From> obj) 
{
    return std::unique_ptr<T_To>{dynamic_cast<T_To*>(obj.get()) ? dynamic_cast<T_To*>(obj.release()) : nullptr};
}
/************************************************************************************************************************/
ClassManage& ClassManage::getDefaultClassManage() {
	static ClassManage ret;
	return ret;
}

void ClassManage::registerClass(const std::string strClassName, std::unique_ptr<ObjectFactory> objFactory)
{
    std::lock_guard<std::mutex> lock(internal_mutex_);
    if (strClassName.empty())
        return;
    std::string strClass = StringUtils::getTypeName2WithDot(strClassName);
    if (m_mapClassManage.find(strClass) != m_mapClassManage.end()) 
        return;

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
    if(m_mapClassManage.find(strClass) != m_mapClassManage.end())
        m_mapClassManage.erase(strClass);
}

void ClassManage::unregisterClass()
{
    std::lock_guard<std::mutex> lock(internal_mutex_);
    m_mapClassManage.clear();
}

bool ClassManage::initLoadClass(const std::string& strClassName, const std::string strLable, std::string strObjectName)
{
    bool fRet = false;
    if (strClassName.empty() || strLable.empty())
        return fRet;
    std::unique_ptr<ObjectClass> obj = ClassManage::createObjectClass(strClassName);
    if (obj && (m_mapClassLoad.empty() || m_mapClassLoad.find(strLable) == m_mapClassLoad.end()))
    {
        if(!strObjectName.empty())
            obj->setObjectName(strObjectName);
        m_mapClassLoad.insert(std::make_pair(strLable, DynamicUniqueCast<ObjectClass>(std::move(obj))));
        fRet = true;
    }
    return fRet;
}

std::unique_ptr<ObjectClass> ClassManage::GetObjectPrtFromLoadClass(const std::string strLable)
{
    if (strLable.empty() || m_mapClassLoad.empty())
        return nullptr;
    auto prtClass = m_mapClassLoad.find(strLable);
    if(prtClass == m_mapClassLoad.end())
        return nullptr;
    return std::move(prtClass->second);
}
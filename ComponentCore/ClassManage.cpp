/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ClassManage.h"
#include "ObjectFactory.h"
#include "StringUtils.h"
#include "ObjectClass.h"

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
    std::lock_guard<std::mutex> lock(m_mutexUnternal);
    if (strClassName.empty())
        return;
    std::string strClass = StringUtils::getTypeName2WithDot(strClassName);
    if (m_mapClassManage.find(strClass) != m_mapClassManage.end()) 
        return;

    m_mapClassManage.insert(std::make_pair(strClass, std::move(objFactory)));
}

std::shared_ptr<ObjectClass> ClassManage::CreateObject(std::string strClassName)
{
    std::lock_guard<std::mutex> lock(m_mutexUnternal);
    if (strClassName.empty())
        return nullptr;
    std::string strClass = StringUtils::getTypeName2WithDot(strClassName);
    if(m_mapClassManage.find(strClass) != m_mapClassManage.end())
        return m_mapClassManage[strClass]->createObject();
    return nullptr;
}

std::shared_ptr<ObjectClass> ClassManage::createObjectClass(std::string strClassName)
{
    if (strClassName.empty())
        return nullptr;
    return ClassManage::getDefaultClassManage().CreateObject(strClassName);
}

void ClassManage::unregisterClass(const std::string strClassName)
{
    std::lock_guard<std::mutex> lock(m_mutexUnternal);
    if (strClassName.empty())
        return;
    std::string strClass = StringUtils::getTypeName2WithDot(strClassName);
    if(m_mapClassManage.find(strClass) != m_mapClassManage.end())
        m_mapClassManage.erase(strClass);
}

void ClassManage::unregisterClass()
{
    std::lock_guard<std::mutex> lock(m_mutexUnternal);
    m_mapClassManage.clear();
}

bool ClassManage::insertClass(const std::string& strLable, const std::string &strClassName,
    const std::string& strObjName, std::shared_ptr<Properties> pProp)
{
    bool fRet = false;
    if (strLable.empty())
        return fRet;
    std::shared_ptr<ObjectClass> objClass = ClassManage::getDefaultClassManage().createObjectClass(strClassName);
    if (objClass && (m_mapClassLoad.empty() || m_mapClassLoad.find(strLable) == m_mapClassLoad.end()))
    {
        objClass->addPropertiesPtr(pProp);
        objClass->setObjectName(strObjName);
        m_mapClassLoad.insert(std::make_pair(strLable, objClass));
        fRet = true;
    }
    return fRet;
}

std::shared_ptr<ObjectClass> ClassManage::GetObjectPrtFromLoadClass(const std::string strLable)
{
    if (strLable.empty() || m_mapClassLoad.empty())
        return nullptr;
    auto prtClass = m_mapClassLoad.find(strLable);
    if(prtClass == m_mapClassLoad.end())
        return nullptr;
    return prtClass->second;
}

bool ClassManage::initClassInfo()
{
    if (m_mapClassLoad.empty())
        return false;
    for (auto it = m_mapClassLoad.begin(); it != m_mapClassLoad.end(); ++it)
        it->second->initObject();
    return true;
}
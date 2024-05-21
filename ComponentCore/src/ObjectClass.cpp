/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ObjectClass.h"
#include <typeinfo>
#include "StringUtils.h"
#include "Properties.h"
#ifndef WIN32
#include <cxxabi.h>
#endif
/**
 * @brief 
*/
ObjectClass::ObjectClass() :m_strObjectName()
{

}
/**
 * @brief 
*/
ObjectClass::~ObjectClass() 
{
}
/**
 * @brief 
 * @return 
*/
std::string ObjectClass::getClassType()
{
#ifndef WIN32
    char* szDemangleName = abi::__cxa_demangle(typeid(*this).name(), NULL, NULL, NULL);
    if (szDemangleName == nullptr)
        return {};
    std::string strTypeame = std::string(szDemangleName);
    std::free(szDemangleName);
    szDemangleName= nullptr;
	return StringUtils::getTypeName2WithDot(strTypeame);
#else
    return StringUtils::getTypeName2WithDot(typeid(*this).name());
#endif
}
/**
 * @brief 
 * @param strObjectName 
 * @return 
*/
bool ObjectClass::setObjectName(const std::string strObjectName)
{
    m_strObjectName = strObjectName;
    return true;
}
/**
 * @brief 
 * @return 
*/
std::string ObjectClass::getObjectName()
{
    return m_strObjectName;
}
/**
 * @brief 
 * @param strObjectId 
 * @return 
*/
bool ObjectClass::setObjectId(const std::string strObjectId)
{
    m_strObjectId = strObjectId;
    return true;
}
/**
 * @brief 
 * @return 
*/
std::string ObjectClass::getObjectId()
{
    return m_strObjectId;
}
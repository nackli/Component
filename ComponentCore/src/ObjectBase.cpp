/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ObjectBase.h"
#include <typeinfo>
#include "StringUtils.h"
#include "Properties.h"
#ifndef WIN32
#include <cxxabi.h>
#endif
/**
 * @brief 
*/
ObjectBase::ObjectBase() :m_strObjectName(), m_strObjectId(), m_emTypeClass(TYPE_UNINIT)
{

}
/**
 * @brief 
*/
ObjectBase::~ObjectBase()
{
}
/**
 * @brief 
 * @return 
*/
std::string ObjectBase::getClassType()
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
bool ObjectBase::setObjectName(const std::string strObjectName)
{
    m_strObjectName = strObjectName;
    return true;
}
/**
 * @brief 
 * @return 
*/
std::string ObjectBase::getObjectName()
{
    return m_strObjectName;
}
/**
 * @brief 
 * @param strObjectId 
 * @return 
*/
bool ObjectBase::setObjectId(const std::string strObjectId)
{
    m_strObjectId = strObjectId;
    return true;
}
/**
 * @brief 
 * @return 
*/
std::string ObjectBase::getObjectId()
{
    return m_strObjectId;
}
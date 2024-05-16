/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ObjectClass.h"
#include <typeinfo>
#include "StringUtils.h"
ObjectClass::ObjectClass() :m_strObjectName()
{

}

ObjectClass::~ObjectClass() 
{
}

std::string ObjectClass::getClassType()
{
#ifndef WIN32
    char* szDemangleName = abi::__cxa_demangle(typeid(Class).name(), NULL, NULL, NULL);
    if (szDemangleName == nullptr)
        return {};
    std::string strTypeame = szDemangleName;
    std::free(szDemangleName);
    return StringUtils::getTypeName2WithDot(szDemangleName);
#else
    return StringUtils::getTypeName2WithDot(typeid(*this).name());
#endif
}

bool ObjectClass::setObjectName(const std::string strObjectName)
{
    m_strObjectName = strObjectName;
    return true;
}

std::string ObjectClass::getObjectName()
{
    return m_strObjectName;
}
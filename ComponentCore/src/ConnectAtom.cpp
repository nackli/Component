/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ConnectAtom.h"
#include <typeinfo>
#include "StringUtils.h"
#ifndef WIN32
#include <cxxabi.h>
#endif
/**
 * @brief 
*/
ConnectAtom::ConnectAtom(std::string strConnsId, std::string strConnName)
	:ObjectBase(), m_pSrcPtr(nullptr), m_pDestPtr(nullptr), m_sData()
{
	this->setObjectId(strConnsId);
	this->setObjectName(strConnName);
}
/**
 * @brief 
*/
ConnectAtom::~ConnectAtom()
{
}
/**
 * @brief 
 * @param strSrcId 
*/
void ConnectAtom::setSrcObject(std::shared_ptr<ObjectBase> pSrcPtr)
{
	m_pSrcPtr = pSrcPtr;
}
/**
 * @brief 
 * @param strDestId 
*/
void ConnectAtom::setDestObject(std::shared_ptr<ObjectBase> pDestPtr)
{
	m_pDestPtr = pDestPtr;
}
/**
 * @brief 
 * @return 
*/
std::shared_ptr<ObjectBase> ConnectAtom::getSrcObject() const
{
	return m_pSrcPtr;
}
/**
 * @brief 
 * @return 
*/
std::shared_ptr<ObjectBase>  ConnectAtom::getDestObject() const
{
	return m_pDestPtr;
}

bool ConnectAtom::addData(Value& vData)
{
	std::lock_guard<std::mutex> lock(m_mutexUnternal);
	m_sData.emplace(vData);
	return true;
}

Value ConnectAtom::getData()
{
	std::lock_guard<std::mutex> lock(m_mutexUnternal);
	if (m_sData.empty())
		return Value();
	Value vTemp = m_sData.top();
	m_sData.pop();
	return vTemp;
}
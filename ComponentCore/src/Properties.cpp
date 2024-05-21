/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/
#include "Properties.h"
Properties::Properties() :m_mapCfgValue()
{
}

Properties::~Properties()
{
}
/**
 * @brief 
 * @param mapValue 
 * @return 
*/
bool Properties::addValue(const MapStr2Value& mapValue)
{
	if(!m_mapCfgValue.empty())
		m_mapCfgValue.clear();
	m_mapCfgValue = mapValue;
	return true;
}
/**
 * @brief 
 * @param strKey 
 * @return 
*/
Value Properties::getValue(const std::string &strKey)
{
	if (m_mapCfgValue.empty())
		return Value();
	return m_mapCfgValue.at(strKey);
}
/**
 * @brief 
 * @param strKey 
 * @param vData 
 * @return 
*/
bool Properties::addValue(std::string& strKey, Value vData)
{
	if (strKey.empty())
		return false;
	m_mapCfgValue.insert(std::make_pair(strKey, vData));
	return true;
}
/**
 * @brief 
 * @param strKey 
 * @return 
*/
Value Properties::operator[](std::string strKey)
{
	return getValue(strKey);
}
/**
 * @brief 
 * @return 
*/
Properties::itNumber Properties::beginNumber()
{
	return m_mapCfgValue.begin();
}
/**
 * @brief 
 * @return 
*/
Properties::itNumber Properties::endNumber()
{
	return m_mapCfgValue.end();
}
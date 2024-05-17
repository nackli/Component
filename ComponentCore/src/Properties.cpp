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

bool Properties::addValue(const MapStr2Value& mapValue)
{
	m_mapCfgValue.clear();
	m_mapCfgValue = mapValue;
	return true;
}

Value Properties::getValue(const std::string &strKey)
{
	if (m_mapCfgValue.empty())
		return Value();
	return m_mapCfgValue.at(strKey);
}

bool Properties::addValue(std::string& strKey, Value vData)
{
	if (strKey.empty())
		return false;
	m_mapCfgValue.insert(std::make_pair(strKey, vData));
	return true;
}

Value Properties::operator[](std::string strKey)
{
	return getValue(strKey);
}

Properties::itNumber Properties::beginNumber()
{
	return m_mapCfgValue.begin();
}

Properties::itNumber Properties::endNumber()
{
	return m_mapCfgValue.end();
}
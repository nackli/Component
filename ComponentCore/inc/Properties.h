/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/
#pragma once
#include <map>
#include <string>
#include "Value.h"
class Properties
{
public:
	using MapStr2Value = std::map<std::string, Value>;
	using itNumber = typename MapStr2Value::iterator;
public:
	Properties();
	~Properties();
	bool addValue(const MapStr2Value&);
	Value getValue(const std::string&);
	bool addValue(std::string&, Value);
	Value operator[](std::string strKey);
	itNumber beginNumber();
	itNumber endNumber();
private:
	MapStr2Value m_mapCfgValue;
};


/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "Value.h"
#include <utility>
#include<map>
#include <algorithm>
#include <functional>
#define FREE_MEM(x) if((x)){free((x));(x) =nullptr;}

static const std::type_index UINT64_TYPE = std::type_index(typeid(uint64_t));
static const std::type_index INT64_TYPE = std::type_index(typeid(int64_t));
static const std::type_index UINT32_TYPE = std::type_index(typeid(uint32_t));
static const std::type_index INT32_TYPE = std::type_index(typeid(int));
static const std::type_index STRING_TYPE = std::type_index(typeid(char *));
static const std::type_index BOOL_TYPE = std::type_index(typeid(bool));
static const std::type_index REAL_TYPE = std::type_index(typeid(double));
static const std::type_index NULL_UNKOWN = STRING_TYPE;
/**********************************************************************************************/
template <typename R,typename T>
static const std::map<std::string, std::function<R(T, T)>>  g_mapOperateFun = {
	{"==",          [](T leftNum, T rightNum)->R { return leftNum == rightNum; } },
	{"!=",          [](T leftNum, T rightNum)->R { return leftNum == rightNum; } },
	{"<",			[](T leftNum, T rightNum)->R { return leftNum < rightNum; } },
	{">",           [](T leftNum, T rightNum)->R { return leftNum > rightNum; } },
	{"<=",          [](T leftNum, T rightNum)->R { return leftNum <= rightNum; } },
	{">=",          [](T leftNum, T rightNum)->R { return leftNum >= rightNum; } },
	{"+",			[](T leftNum, T rightNum)->R { return (R)(leftNum + rightNum); } },
	{"-",			[](T leftNum, T rightNum)->R { return (R)(leftNum - rightNum); } },
	{"*",			[](T leftNum, T rightNum)->R { return (R)(leftNum * rightNum); } },
	{"/",           [](T leftNum, T rightNum)->R { return (R)(leftNum / rightNum); } }
};

static bool OnIsSameType(std::type_index type1, std::type_index type2,bool bDouble = false)
{
	if (type1 == type2)
		return true;
	else
	{
		bool bType1 = (type1 == UINT64_TYPE || type1 == INT64_TYPE || type1 == UINT32_TYPE || type1 == INT32_TYPE);
		bool bType2 = (type2 == UINT64_TYPE || type2 == INT64_TYPE || type2 == UINT32_TYPE || type2 == INT32_TYPE);
		if (bDouble)
		{
			bType1 = (bType1 || type1 == REAL_TYPE);
			bType2 = (bType2 || type2 == REAL_TYPE);
		}

		if (bType1 && bType2)
			return true;
		return false;
	}
	return false;
}

static inline bool str2Number(std::string strData, uint64_t& uData)
{
	bool fRet = false;
	if (strData.empty())
		return fRet;
	char* pEnd = NULL;
	uData = strtoul(strData.c_str(), &pEnd, 10);
	if (*pEnd != 0)
		return false;
	return true;
}

static inline uint64_t OnGetValue(std::type_index typeIndex, uint64_t uValue,
	std::string strValue, uint64_t uDefalt)
{
	if (OnIsSameType(typeIndex, UINT64_TYPE))
		return uValue;
	else if (typeIndex == STRING_TYPE)
	{
		uint64_t uRet = 0;
		if (str2Number(strValue, uRet))
			return uRet;
	}
	return uDefalt;
}


static inline bool str2Real(std::string strData, double& dData)
{
	bool fRet = false;
	if (strData.empty())
		return fRet;
	char* pEnd = NULL;
	dData = strtod(strData.c_str(), &pEnd);
	if (*pEnd != 0)
		return false;
	return true;
}
/**********************************************************************************************/
Value::Value() :m_objValue(), m_typeId(NULL_UNKOWN), m_strValue()
{
}

Value::Value(std::string strValue) : m_objValue(), m_typeId(STRING_TYPE)
{
	m_strValue = strValue;
}

Value::Value(char *szValue) :m_objValue(), m_typeId(STRING_TYPE)
{
	m_strValue = std::move(szValue);
}

Value::Value(const char* szValue) :m_objValue(), m_typeId(STRING_TYPE)
{
	m_strValue = std::move(szValue);
}

Value::Value(uint64_t uValue):m_objValue(), m_typeId(UINT64_TYPE), m_strValue()
{
	m_objValue.uValue64 = uValue;
}

Value::Value(int64_t uValue) : m_objValue(), m_typeId(INT64_TYPE), m_strValue()
{
	m_objValue.iValue64 = uValue;
}

Value::Value(uint32_t uValue) : m_objValue(), m_typeId(UINT32_TYPE), m_strValue()
{
	m_objValue.uValue32 = uValue;
}
Value::Value(int uValue) : m_objValue(), m_typeId(INT32_TYPE), m_strValue()
{
	m_objValue.iValue = uValue;
}
Value::Value(bool uValue) : m_objValue(), m_typeId(BOOL_TYPE), m_strValue()
{
	m_objValue.bValue = uValue;
}
Value::Value(double uValue) : m_objValue(), m_typeId(REAL_TYPE), m_strValue()
{
	m_objValue.dValue = uValue;
}

Value::~Value()
{
}

std::string Value::getValue(std::string uDefalt)
{
	if (m_typeId == STRING_TYPE && !m_strValue.empty())
		return m_strValue;
	else if (OnIsSameType(m_typeId, UINT64_TYPE))
		return std::move(std::to_string(this->m_objValue.uValue64));
	else if (m_typeId == REAL_TYPE)
		return std::move(std::to_string(this->m_objValue.dValue));
	return std::move(uDefalt);
}

std::string Value::getValue(char* szDefalt)
{
	return getValue(std::string(szDefalt));
}

std::string Value::getValue(const char* szDefalt)
{
	return getValue(std::string(szDefalt));
}

uint64_t Value::getValue(uint64_t uDefalt) 
{
	return OnGetValue(m_typeId, m_objValue.uValue64, m_strValue, uDefalt);
}

int64_t Value::getValue(int64_t uDefalt)
{
	return (int64_t)OnGetValue(m_typeId, (uint64_t)m_objValue.iValue64, m_strValue, (uint64_t)uDefalt);
}

uint32_t Value::getValue(uint32_t uDefalt)
{
	return (uint32_t)OnGetValue(m_typeId, (uint64_t)m_objValue.uValue32, m_strValue, (uint64_t)uDefalt);
}

int Value::getValue(int uDefalt)
{
	return (int)OnGetValue(m_typeId, (uint64_t)m_objValue.iValue, m_strValue, (uint64_t)uDefalt);;
}
bool Value::getValue(bool uDefalt)
{
	if (m_typeId == BOOL_TYPE)
		return m_objValue.bValue;
	else if (OnIsSameType(m_typeId, UINT64_TYPE))
		return m_objValue.bValue;
	return uDefalt;
}
double Value::getValue(double uDefalt)
{
	if (m_typeId == REAL_TYPE)
		return m_objValue.dValue;
	else if(OnIsSameType(m_typeId, UINT64_TYPE))
		return (double)m_objValue.uValue64;
	else if (m_typeId == STRING_TYPE)
	{
		double dValue = 0;
		if (str2Real(m_strValue, dValue))
			return dValue;
	}
	return uDefalt;
}

Value& Value::operator=(Value value)
{
	m_typeId = std::move(value.m_typeId);
	if (m_typeId != STRING_TYPE)
	{
		m_strValue.clear();
		m_objValue = value.m_objValue;
	}
	else
	{
		m_objValue = ValueHolder();
		m_strValue = std::move(value.m_strValue);
	}
	return *this;
}

Value& Value::operator=(std::string strValue)
{
	*this = Value(strValue);
	return *this;
}

Value& Value::operator=(char* szValue)
{
	*this = Value(szValue);
	return *this;
}

Value& Value::operator=(const char* szValue)
{
	*this = Value(szValue);
	return *this;
}

Value& Value::operator=(uint64_t uValue)
{
	*this = Value(uValue);
	return *this;
}

Value& Value::operator=(int64_t uValue)
{
	*this = Value(uValue);
	return *this;
}

Value& Value::operator=(uint32_t uValue)
{
	*this = Value(uValue);
	return *this;
}

Value& Value::operator=(int iValue)
{
	*this = Value(iValue);
	return *this;
}

Value& Value::operator=(bool uValue)
{
	*this = Value(uValue);
	return *this;
}

Value& Value::operator=(double uValue)
{
	*this = Value(uValue);
	return *this;
}

bool Value::operator==(const Value valueParam)
{
	return cmpValueFun(valueParam, "==");;
}

bool Value::cmpValueFun(const Value& valueParam, std::string strOpr)
{
	if (OnIsSameType(m_typeId, valueParam.m_typeId))
	{
		if (m_typeId == STRING_TYPE)
		{
			if(strOpr == "==")
				return !m_strValue.compare(valueParam.m_strValue);
			else if (strOpr == ">")
				return m_strValue.compare(valueParam.m_strValue) > 0;
			else if (strOpr == "<")
				return m_strValue.compare(valueParam.m_strValue) < 0;
			else if (strOpr == ">=")
				return m_strValue.compare(valueParam.m_strValue) >= 0;
			else if (strOpr == "<=")
				return m_strValue.compare(valueParam.m_strValue) <= 0;
		}	
		else if (m_typeId == REAL_TYPE)
		{
			const double eps = 1e-6;
			auto funOpr = g_mapOperateFun<bool,double>.at(strOpr);
			if (strOpr == "==")
				return funOpr(fabs(valueParam.m_objValue.dValue - m_objValue.dValue), eps);
			else
				return funOpr(valueParam.m_objValue.dValue,m_objValue.dValue + eps);
		}
		else
		{
			auto funOpr = g_mapOperateFun<bool, uint64_t>.at(strOpr);
			return funOpr(m_objValue.uValue64, valueParam.m_objValue.uValue64);
		}
	}
	return false;
}

bool Value::operator==(const std::string strValue)
{
	return *this == Value(strValue);
}

bool Value::operator==(char* szValue)
{
	return *this == Value(szValue);
}

bool Value::operator==(const char* szValue)
{
	return *this == Value(szValue);
}

bool Value::operator==(const uint64_t uValue)
{
	return *this == Value(uValue);
}

bool Value::operator==(const int64_t uValue)
{
	return *this == Value(uValue);
}

bool Value::operator==(const uint32_t uValue)
{
	return *this == Value(uValue);
}

bool Value::operator==(const int uValue)
{
	return *this == Value(uValue);
}

bool Value::operator==(const bool uValue)
{
	return *this == Value(uValue);
}

bool Value::operator==(const double uValue)
{
	return *this == Value(uValue);
}

bool Value::operator!=(const Value valueParam)
{
	return !(*this == valueParam);
}

bool Value::operator!=(const std::string strValue)
{
	return *this != Value(strValue);
}

bool Value::operator!=(char* szValue)
{
	return *this != Value(szValue);
}

bool Value::operator!=(const char* szValue)
{
	return *this != Value(szValue);
}

bool Value::operator!=(const uint64_t uValue)
{
	return *this != Value(uValue);
}

bool Value::operator!=(const int64_t iValue)
{
	return *this != Value(iValue);
}

bool Value::operator!=(const uint32_t uValue)
{
	return *this != Value(uValue);
}

bool Value::operator!=(const int uValue)
{
	return *this != Value(uValue);
}

bool Value::operator!=(const bool bValue)
{
	return *this != Value(bValue);
}

bool Value::operator!=(const double dValue)
{
	return *this != Value(dValue);
}

bool Value::operator<(const Value valueParam)
{
	return cmpValueFun(valueParam, "<");
}

bool Value::operator<(const std::string strValue)
{
	return *this < Value(strValue);
}

bool Value::operator<(char* szValue)
{
	return *this < Value(szValue);
}

bool Value::operator<(const char* szValue)
{
	return *this < Value(szValue);
}

bool Value::operator<(const uint64_t uValue)
{
	return *this < Value(uValue);
}

bool Value::operator<(const int64_t uValue)
{
	return *this < Value(uValue);
}

bool Value::operator<(const uint32_t uValue)
{
	return *this < Value(uValue);
}

bool Value::operator<(const int uValue)
{
	return *this < Value(uValue);
}

bool Value::operator<(const double uValue)
{
	return *this < Value(uValue);
}

bool Value::operator<=(const Value valueParam)
{
	return cmpValueFun(valueParam, "<=");
}

bool Value::operator<=(const std::string strValue)
{
	return *this <= Value(strValue);
}

bool Value::operator<=(char* szValue)
{
	return *this <= Value(szValue);
}

bool Value::operator<=(const char* szValue)
{
	return *this <= Value(szValue);
}

bool Value::operator<=(const uint64_t uValue)
{
	return *this <= Value(uValue);
}

bool Value::operator<=(const int64_t uValue)
{
	return *this <= Value(uValue);
}

bool Value::operator<=(const uint32_t uValue)
{
	return *this <= Value(uValue);
}

bool Value::operator<=(const int uValue)
{
	return *this <= Value(uValue);
}

bool Value::operator<=(const double uValue)
{
	return *this <= Value(uValue);
}

bool Value::operator>(const Value valueParam)
{
	return cmpValueFun(valueParam, ">");
}

bool Value::operator>(const std::string strValue)
{
	return *this > Value(strValue);
}

bool Value::operator>(char* szValue)
{
	return *this > Value(szValue);
}

bool Value::operator>(const char* szValue)
{
	return *this > Value(szValue);
}

bool Value::operator>(const uint64_t uValue)
{
	return *this > Value(uValue);
}

bool Value::operator>(const int64_t uValue)
{
	return *this > Value(uValue);
}

bool Value::operator>(const uint32_t uValue)
{
	return *this > Value(uValue);
}

bool Value::operator>(const int uValue)
{
	return *this > Value(uValue);
}


bool Value::operator>(const double uValue)
{
	return *this > Value(uValue);
}

bool Value::operator>=(const Value& valueParam)
{
	return cmpValueFun(valueParam, ">=");
}

bool Value::operator>=(const std::string strValue)
{
	return *this >= Value(strValue);
}

bool Value::operator>=(char* szValue)
{
	return *this >= Value(szValue);
}

bool Value::operator>=(const char* szValue)
{
	return *this >= Value(szValue);
}

bool Value::operator>=(const uint64_t uValue)
{
	return *this >= Value(uValue);
}

bool Value::operator>=(const int64_t uValue)
{
	return *this >= Value(uValue);
}

bool Value::operator>=(const uint32_t uValue)
{
	return *this >= Value(uValue);
}

bool Value::operator>=(const int uValue)
{
	return *this >= Value(uValue);
}

bool Value::operator>=(const double uValue)
{
	return *this >= Value(uValue);
}

Value Value::calcValueFun(const Value& vParam, std::string strOpr)
{
	Value vTempRet;
	if (OnIsSameType(m_typeId, vParam.m_typeId, true))
	{
		vTempRet.m_typeId = m_typeId;
		if (m_typeId == STRING_TYPE)
		{
			//auto funOpr = g_mapCalcFun<std::string, std::string>.at(strOpr);
			vTempRet.m_strValue = m_strValue + vParam.m_strValue;
		}
		else if (m_typeId == REAL_TYPE && vParam.m_typeId == REAL_TYPE)
		{
			auto funOpr = g_mapOperateFun<double, double>.at(strOpr);
			vTempRet.m_objValue.dValue = funOpr(m_objValue.dValue, vParam.m_objValue.dValue);
		}
		else if (m_typeId == REAL_TYPE && vParam.m_typeId != REAL_TYPE)
		{
			auto funOpr = g_mapOperateFun<double, double>.at(strOpr);
			vTempRet.m_objValue.dValue = funOpr(m_objValue.dValue, (double)vParam.m_objValue.uValue64);
		}
		else if (m_typeId != REAL_TYPE && vParam.m_typeId == REAL_TYPE)
		{
			auto funOpr = g_mapOperateFun<double, double>.at(strOpr);
			vTempRet.m_objValue.dValue = funOpr((double)m_objValue.uValue64, vParam.m_objValue.dValue);
			vTempRet.m_typeId = REAL_TYPE;
		}
		else
		{
			auto funOpr = g_mapOperateFun<uint64_t, uint64_t>.at(strOpr);
			vTempRet.m_objValue.uValue64 = funOpr(m_objValue.uValue64, vParam.m_objValue.uValue64);
		}

	}
	return vTempRet;
}

Value Value::operator+(Value vParam)
{
	return calcValueFun(vParam, "+");
}

Value Value::operator+(std::string strValue)
{
	return calcValueFun(Value(strValue), "+");
}

Value Value::operator+(char* szValue) 
{
	return  *this + Value(szValue);
}

Value Value::operator+(const char* szValue) 
{
	return *this + Value(szValue);
}

Value Value::operator+(uint64_t uValue) 
{
	return  *this + Value(uValue);
}

Value Value::operator+(int64_t iValue) 
{
	return  *this + Value(iValue);
}

Value Value::operator+(uint32_t iValue)
{
	return  *this + Value(iValue);
}

Value Value::operator+(int iValue)
{
	return  *this + Value(iValue);
}

Value Value::operator+(double iValue)
{
	return  *this + Value(iValue);
}

Value Value::operator+=(Value vParam)
{
	*this = calcValueFun(vParam, "+");
	return *this;
}

Value Value::operator+=(std::string strValue)
{
	return  *this += Value(strValue);
}

Value Value::operator+=(char* szValue)
{
	return  *this += Value(szValue);
}

Value Value::operator+=(const char* szValue)
{
	return  *this += Value(szValue);
}

Value Value::operator+=(uint64_t uValue)
{
	return  *this += Value(uValue);
}

Value Value::operator+=(int64_t uValue)
{
	return  *this += Value(uValue);
}

Value Value::operator+=(uint32_t uValue)
{
	return  *this += Value(uValue);
}

Value Value::operator+=(int uValue)
{
	return  *this += Value(uValue);
}

Value Value::operator+=(double uValue)
{
	return  *this += Value(uValue);
}

Value Value::operator-(Value vParam)
{
	return calcValueFun(vParam, "-");
}

Value Value::operator-(uint64_t iValue)
{
	return  *this - Value(iValue);
}

Value Value::operator-(int64_t iValue)
{
	return  *this - Value(iValue);
}

Value Value::operator-(uint32_t iValue)
{
	return  *this - Value(iValue);
}
Value Value::operator-(int iValue)
{
	return  *this - Value(iValue);
}

Value Value::operator-(double iValue)
{
	return  *this - Value(iValue);
}

Value Value::operator-=(Value vParam)
{
	*this = calcValueFun(vParam, "-");
	return *this;
}

Value Value::operator-=(uint64_t iValue)
{
	return  *this -= Value(iValue);
}

Value Value::operator-=(int64_t iValue)
{
	return  *this -= Value(iValue);
}

Value Value::operator-=(uint32_t iValue)
{
	return  *this -= Value(iValue);
}

Value Value::operator-=(int iValue)
{
	return  *this -= Value(iValue);
}

Value Value::operator-=(double iValue)
{
	return  *this -= Value(iValue);
}


Value Value::operator*(Value vParam)
{
	return calcValueFun(vParam, "*");
}

Value Value::operator*(uint64_t iValue)
{
	return  *this * Value(iValue);
}

Value Value::operator*(int64_t iValue)
{
	return  *this * Value(iValue);
}

Value Value::operator*(uint32_t iValue)
{
	return  *this * Value(iValue);
}

Value Value::operator*(int iValue)
{
	return  *this * Value(iValue);
}

Value Value::operator*(double iValue)
{
	return  *this * Value(iValue);
}

Value Value::operator*=(Value vParam)
{
	Value valueRet = calcValueFun(vParam, "*");
	*this = valueRet;
	return *this;
}

Value Value::operator*=(uint64_t iValue)
{
	return  *this *= Value(iValue);
}

Value Value::operator*=(int64_t iValue)
{
	return  *this *= Value(iValue);
}

Value Value::operator*=(uint32_t iValue)
{
	return  *this *= Value(iValue);
}

Value Value::operator*=(int iValue)
{
	return  *this *= Value(iValue);
}

Value Value::operator*=(double iValue)
{
	return  *this *= Value(iValue);
}

Value Value::operator/(Value vParam)
{
	return  calcValueFun(vParam, "/");
}

Value Value::operator/(uint64_t iValue)
{
	return  *this / Value(iValue);
}

Value Value::operator/(int64_t iValue)
{
	return  *this / Value(iValue);
}

Value Value::operator/(uint32_t iValue)
{
	return  *this / Value(iValue);
}

Value Value::operator/(int iValue)
{
	return  *this / Value(iValue);
}

Value Value::operator/(double iValue)
{
	return  *this / Value(iValue);
}

Value Value::operator/=(Value vParam)
{
	*this = calcValueFun(vParam, "/");;
	return *this;
}

Value Value::operator/=(uint64_t iValue)
{

	return  *this /= Value(iValue);
}

Value Value::operator/=(int64_t iValue)
{
	return  *this /= Value(iValue);
}

Value Value::operator/=(uint32_t iValue)
{
	return  *this /= Value(iValue);
}

Value Value::operator/=(int iValue)
{
	return  *this /= Value(iValue);
}

Value Value::operator/=(double iValue)
{
	return  *this /= Value(iValue);
}

Value_Type Value::getType()
{
	if (m_typeId == REAL_TYPE)
		return TYPE_REAL;
	if (m_typeId == UINT64_TYPE)
		return TYPE_UINT64;
	if (m_typeId == INT64_TYPE)
		return TYPE_INT64;
	if (m_typeId == INT32_TYPE)
		return TYPE_INT32;
	if (m_typeId == UINT32_TYPE)
		return TYPE_UINT32;
	if (m_typeId == BOOL_TYPE)
		return TYPE_BOOL;
	if (m_typeId == STRING_TYPE)
		return TYPE_STRING;
	return TYPE_MAX;
}


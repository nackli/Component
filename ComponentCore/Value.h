#pragma once
#include <string>
#include <typeindex>
typedef enum VALUE_TYPE {
	TYPE_UINT64,
	TYPE_INT64,
	TYPE_UINT32,
	TYPE_INT32,
	TYPE_BOOL,
	TYPE_REAL,
	TYPE_STRING,
	TYPE_MAX
}Value_Type;
class Value
{
public:
	explicit Value();
	explicit Value(std::string );
	explicit Value(char *);
	explicit Value(const char *);
	explicit Value(uint64_t );
	explicit Value(int64_t );
	explicit Value(uint32_t );
	explicit Value(int );
	explicit Value(bool );
	explicit Value(double );
	~Value();

	//param is default value
	std::string getValue(std::string );
	std::string  getValue(char *);
	std::string  getValue(const char*);
	uint64_t getValue(uint64_t );
	int64_t getValue(int64_t );
	uint32_t getValue(uint32_t );
	int getValue(int );
	bool getValue(bool );
	double getValue(double );

	Value& operator=(Value);
	Value& operator=(std::string);
	Value& operator=(char *);
	Value& operator=(const char*);
	Value& operator=(uint64_t);
	Value& operator=(int64_t);
	Value& operator=(uint32_t);
	Value& operator=(int);
	Value& operator=(bool);
	Value& operator=(double);

	bool operator==(const Value);
	bool operator==(const std::string);
	bool operator==(char*);
	bool operator==(const char*);
	bool operator==(const uint64_t);
	bool operator==(const int64_t);
	bool operator==(const uint32_t);
	bool operator==(const int);
	bool operator==(const bool);
	bool operator==(const double);

	bool operator!=(const Value);
	bool operator!=(const std::string);
	bool operator!=(char*);
	bool operator!=(const char*);
	bool operator!=(const uint64_t);
	bool operator!=(const int64_t);
	bool operator!=(const uint32_t);
	bool operator!=(const int);
	bool operator!=(const bool);
	bool operator!=(const double);

	bool operator<(const Value);
	bool operator<(const std::string);
	bool operator<(char*);
	bool operator<(const char*);
	bool operator<(const uint64_t);
	bool operator<(const int64_t);
	bool operator<(const uint32_t);
	bool operator<(const int);
	bool operator<(const double);

	bool operator<=(const Value);
	bool operator<=(const std::string);
	bool operator<=(char*);
	bool operator<=(const char*);
	bool operator<=(const uint64_t);
	bool operator<=(const int64_t);
	bool operator<=(const uint32_t);
	bool operator<=(const int);
	bool operator<=(const double);

	bool operator>(const Value);
	bool operator>(const std::string);
	bool operator>(char*);
	bool operator>(const char*);
	bool operator>(const uint64_t);
	bool operator>(const int64_t);
	bool operator>(const uint32_t);
	bool operator>(const int);
	bool operator>(const double);

	bool operator>=(const Value&);
	bool operator>=(const std::string);
	bool operator>=(char*);
	bool operator>=(const char*);
	bool operator>=(const uint64_t);
	bool operator>=(const int64_t);
	bool operator>=(const uint32_t);
	bool operator>=(const int);
	bool operator>=(const double);

	Value operator+(Value);
	Value operator+(std::string);
	Value operator+(char*);
	Value operator+(const char*);
	Value operator+(uint64_t);
	Value operator+(int64_t);
	Value operator+(uint32_t);
	Value operator+(int);
	Value operator+(double);

	Value operator+=(Value);
	Value operator+=(std::string);
	Value operator+=(char*);
	Value operator+=(const char*);
	Value operator+=(uint64_t);
	Value operator+=(int64_t);
	Value operator+=(uint32_t);
	Value operator+=(int);
	Value operator+=(double);

	Value operator-(Value);
	Value operator-(uint64_t);
	Value operator-(int64_t);
	Value operator-(uint32_t);
	Value operator-(int);
	Value operator-(double);

	Value operator-=(Value);
	Value operator-=(uint64_t);
	Value operator-=(int64_t);
	Value operator-=(uint32_t);
	Value operator-=(int);
	Value operator-=(double);

	Value operator*(Value);
	Value operator*(uint64_t);
	Value operator*(int64_t);
	Value operator*(uint32_t);
	Value operator*(int);
	Value operator*(double);

	Value operator*=(Value);
	Value operator*=(uint64_t);
	Value operator*=(int64_t);
	Value operator*=(uint32_t);
	Value operator*=(int);
	Value operator*=(double);

	Value operator/(Value);
	Value operator/(uint64_t);
	Value operator/(int64_t);
	Value operator/(uint32_t);
	Value operator/(int);
	Value operator/(double);

	Value operator/=(Value);
	Value operator/=(uint64_t);
	Value operator/=(int64_t);
	Value operator/=(uint32_t);
	Value operator/=(int);
	Value operator/=(double);

	Value_Type getType();
private:
	union ValueHolder {
		uint64_t uValue64;
		int64_t iValue64;
		uint32_t uValue32;
		int iValue;
		bool bValue;
		double dValue;
		//char* strValue; // if allocated_, ptr to { unsigned, char[] }.
	} m_objValue;
	std::type_index m_typeId;
	std::string m_strValue;
private:
	bool cmpValueFun(const Value& valueParam, std::string);
	Value calcValueFun(const Value& valueParam, std::string);
};


#pragma once
#include <string>
class ObjectClass {
public:
	ObjectClass();

	virtual	~ObjectClass();

	virtual bool initObject() = 0;

	virtual std::string getClassType();

	bool setObjectName(const std::string strObjectName);

	std::string getObjectName();

private:
	std::string m_strObjectName;
};
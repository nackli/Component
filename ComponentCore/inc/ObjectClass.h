#pragma once
#include <string>
#include <memory>
class Properties;
class ObjectClass {
public:
	ObjectClass();

	virtual	~ObjectClass();

	virtual bool initObject() = 0;

	virtual std::string getClassType();

	bool setObjectName(const std::string strObjectName);

	std::string getObjectName();

	void addPropertiesPtr(std::shared_ptr<Properties> pProp);

	std::shared_ptr<Properties> getProperties();

private:
	std::string m_strObjectName;
	std::shared_ptr<Properties> m_pProp;
};
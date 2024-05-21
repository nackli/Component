#pragma once
#include <string>
#include <memory>
//class Properties;
class ObjectBase {
public:
	ObjectBase();

	virtual	~ObjectBase();

	virtual bool initObject() = 0;

	virtual std::string getClassType();

	bool setObjectName(const std::string strObjectName);

	std::string getObjectName();

	bool setObjectId(const std::string strObjectId);

	std::string getObjectId();

	//void addPropertiesPtr(std::shared_ptr<Properties> pProp);

	//std::shared_ptr<Properties> getProperties();

private:
	std::string m_strObjectName;
	std::string m_strObjectId;
//	std::shared_ptr<Properties> m_pProp;
};
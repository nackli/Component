#pragma once
#include <string>
#include <memory>
class ObjectBase {
public:
	enum CLASS_TYPE
	{
		TYPE_UNINIT,
		TYPE_OUT,
		TYPE_IN,
	};
	ObjectBase();

	virtual	~ObjectBase();

	virtual std::string getClassType();

	bool setObjectName(const std::string strObjectName);

	std::string getObjectName();

	bool setObjectId(const std::string strObjectId);

	std::string getObjectId();

	void setTypeClass(CLASS_TYPE typeClass) { m_emTypeClass = typeClass; }

	CLASS_TYPE getTypeClass() { return m_emTypeClass; }
private:
	CLASS_TYPE m_emTypeClass;
	std::string m_strObjectName;
	std::string m_strObjectId;
};
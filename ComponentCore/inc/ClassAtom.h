#pragma once
#include <string>
#include <memory>
#include "ObjectBase.h"
#include "Properties.h"
#include "Value.h"
class ClassAtom: public ObjectBase,public Properties
{
public:
	ClassAtom();

	virtual	~ClassAtom();

	bool initClassAtom();

	virtual bool initObject() = 0;

	bool writeData(Value);

	Value readData();
private:
	std::shared_ptr<ObjectBase> m_connObject;
};
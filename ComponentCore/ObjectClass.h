#pragma once
#include <string>
class ObjectClass {
public:
	ObjectClass();

	virtual	~ObjectClass();

	virtual bool initObject() = 0;

	virtual std::string getClassType();

	virtual const std::string getGeneratorId() const final;
};
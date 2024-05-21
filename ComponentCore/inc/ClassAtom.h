#pragma once
#include <string>
#include <memory>
#include "ObjectBase.h"
#include "Properties.h"
class ClassAtom: public ObjectBase,public Properties
{
public:
	ClassAtom();

	virtual	~ClassAtom();

private:
};
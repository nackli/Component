#pragma once
#include <string>
#include <memory>
#include "ObjectClass.h"
#include "Properties.h"
class ClassAtom: public ObjectClass,public Properties
{
public:
	ClassAtom();

	virtual	~ClassAtom();

private:
};
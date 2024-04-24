#include "CTestClass.h"
#include "StaticClass.h"
CTestClass::CTestClass() 
{
}

CTestClass::~CTestClass() 
{

}

bool CTestClass::initObject()
{
	std::string str = getClassType();
	return true;
}

REGISTER_RESOURCE(CTestClass);
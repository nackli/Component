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

REG_CLASS_RES(CTestClass);
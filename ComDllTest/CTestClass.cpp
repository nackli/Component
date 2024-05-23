#include "CTestClass.h"
#include "StaticClass.h"
#include <iostream>
namespace xg {
	namespace nack {
		CTestClass::CTestClass()
		{
		}

		CTestClass::~CTestClass()
		{

		}

		bool CTestClass::initObject()
		{
			std::string str = getClassType();
			std::cout << str << std::endl;
			this->writeData(Value("nihaozhongguo"));
			return true;
		}

		REG_CLASS_RES(CTestClass);
	}
}
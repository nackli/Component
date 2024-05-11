#include "CTestObj.h"
#include "StaticClass.h"
#include "StringUtils.h"
#include <iostream>
namespace xg {
	namespace nanjing {
		CTestObj::CTestObj()
		{
		}

		CTestObj::~CTestObj()
		{

		}

		bool CTestObj::initObject()
		{
			std::string str = getClassType();
			std::cout << str << std::endl;

			return true;
		}

		REG_CLASS_RES(CTestObj);
	}
}

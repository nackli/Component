#include "CTestObj.h"
#include "StaticClass.h"
#include "StringUtils.h"
#include <iostream>
#include "Properties.h"
#include "ClassManage.h"
#include "ConnManage.h"
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
			int i = sizeof(CTestObj);
			std::string str = getClassType();
			std::string str1 = "";
 			std::cout << str << " " << this->getValue("Config File").getValue("") << std::endl;
			Value vData = this->readData();

			return true;
		}

		REG_CLASS_RES(CTestObj);
	}
}

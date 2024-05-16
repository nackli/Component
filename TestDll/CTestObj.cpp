#include "CTestObj.h"
#include "StaticClass.h"
#include "StringUtils.h"
#include <iostream>
#include "Properties.h"
#include "ClassManage.h"
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
			
			std::cout << str << " " << getProperties()->getValue("Config File").getValue("") << std::endl;
			std::shared_ptr<ObjectClass>  objClass = ClassManage::getDefaultClassManage().GetObjectPrtFromLoadClass("66e99f30-a866-3aa6-0000-000000000000");
			std::cout << objClass->getProperties()->getValue("Config File").getValue("") << std::endl;
			return true;
		}

		REG_CLASS_RES(CTestObj);
	}
}

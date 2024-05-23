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

		static void ReadDataThread(void* lpData)
		{
			CTestObj* pTemp = (CTestObj*)lpData;
			while (1)
			{
				if (pTemp)
				{
					Value vData = pTemp->readData();
					std::cout << vData.getValue("") << std::endl;
				}
	
				_sleep(1000);
			}
		}

		bool CTestObj::initObject()
		{
			int i = sizeof(CTestObj); 
			std::string str = getClassType();
			std::string str1 = "";
 			std::cout << str << " " << this->getValue("Config File").getValue("") << std::endl;
			
			std::thread t(ReadDataThread, this);
			t.detach();
			return true;
		}

		REG_CLASS_RES(CTestObj);
	}
}

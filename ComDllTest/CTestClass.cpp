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

		static void WriteDataThread(void *lpData)
		{
			CTestClass* pTemp = (CTestClass*)lpData;
			while (1)
			{
				int iTet = rand();
				pTemp->writeData(Value("nihaozhongguo") + std::to_string(iTet));
				_sleep(1000);
			}
		}

		bool CTestClass::initObject()
		{
			std::string str = getClassType();
			std::cout << str << std::endl;
	
			std::thread t(WriteDataThread, this);
			t.detach();
			return true;
		}

		REG_CLASS_RES(CTestClass);
	}
}
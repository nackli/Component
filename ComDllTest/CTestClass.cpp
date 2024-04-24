#include "CTestClass.h"
#include "StaticClass.h"
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
			return true;
		}

		REGISTER_RESOURCE(CTestClass);
	}
}
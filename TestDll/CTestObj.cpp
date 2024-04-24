#include "CTestObj.h"
#include "StaticClass.h"
#include "StringUtils.h"
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
			return true;
		}

		REGISTER_RESOURCE(CTestObj);
	}
}

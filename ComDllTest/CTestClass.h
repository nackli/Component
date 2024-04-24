#pragma once
#include "ObjectClass.h"
namespace xg {
	namespace nack {
		class CTestClass :public ObjectClass
		{
		public:
			CTestClass();
			~CTestClass();
			bool initObject();
		};
	}
}
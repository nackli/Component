#pragma once
#include "ClassAtom.h"
namespace xg {
	namespace nack {
		class CTestClass :public ClassAtom
		{
		public:
			CTestClass();
			~CTestClass();
			bool initObject();
		};
	}
}
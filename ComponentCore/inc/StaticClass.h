#pragma once
#include <string>
#include "ClassManage.h"
#include "StringUtils.h"
#ifndef WIN32
#include <cxxabi.h>
#include <memory>
#endif
template<typename Class>
class StaticClassType {
public: 
    StaticClassType()
    {
        std::string strClassName = getTypeName();
        auto factory = std::unique_ptr<ObjectFactory>(std::make_unique<ObjectFactoryDef<Class>>());
        ClassManage::getDefaultClassManage().registerClass(strClassName, std::move(factory));
    }

    ~StaticClassType() 
    {
        ClassManage::getDefaultClassManage().unregisterClass();
    }

    static std::string getTypeName()
    {
#ifndef WIN32
        char* szDemangleName = abi::__cxa_demangle(typeid(Class).name(), NULL, NULL, NULL);
        if (szDemangleName == nullptr)
            return {};
        std::string strTypeame = std::string(szDemangleName);
        std::free(szDemangleName);
        szDemangleName= nullptr;
        return strTypeame;
#else
        return StringUtils::getTypeName2WithDot(typeid(Class).name());
#endif
    }

    static const StaticClassType& get() 
    {
        static const StaticClassType instance;
        return instance;
    }
};
#define REG_CLASS_RES(CLASS_NAME)  static const auto& CLASS_NAME##_registrar = StaticClassType<CLASS_NAME>::get()
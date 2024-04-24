#pragma once
#include <string>
#include "ObjectFactory.h"
#include "ClassManage.h"
#ifndef WIN32
#include <cxxabi.h>
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
        std::string strTypeame = szDemangleName;
        std::free(szDemangleName);
        return szDemangleName;
#else
        return typeid(Class).name();
#endif
    }

    static const StaticClassType& get() 
    {
        static const StaticClassType instance;
        return instance;
    }
};

#define REGISTER_RESOURCE(CLASSNAME)  static const auto& CLASSNAME##_registrar = StaticClassType<CLASSNAME>::get()
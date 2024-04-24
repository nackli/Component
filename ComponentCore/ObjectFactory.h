#pragma once
#include <string>
#include <memory>
#include "ObjectClass.h"
class ObjectFactory {
public:
    ObjectFactory() {};

    /**
     * Virtual destructor.
     */
    virtual ~ObjectFactory() = default;


    virtual std::unique_ptr<ObjectClass> createObject()
    {
        return nullptr;
    }
};
template <class T = ObjectClass>
class ObjectFactoryDef :public ObjectFactory {
public:
    ObjectFactoryDef() {};

    /**
     * Virtual destructor.
     */
    virtual ~ObjectFactoryDef() = default;


    virtual std::unique_ptr<ObjectClass> createObject() override
    {
        return std::make_unique<T>();
    }
};

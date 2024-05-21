#pragma once
#include <string>
#include <memory>
class ObjectBase;
class ObjectFactory {
public:
    ObjectFactory() {};

    /**
     * Virtual destructor.
     */
    virtual ~ObjectFactory() = default;


    virtual std::shared_ptr<ObjectBase> createObject()
    {
        return nullptr;
    }
};
template <class T = ObjectBase>
class ObjectFactoryDef :public ObjectFactory {
public:
    ObjectFactoryDef() {};

    /**
     * Virtual destructor.
     */
    virtual ~ObjectFactoryDef() = default;


    virtual std::shared_ptr<ObjectBase> createObject() override
    {
        return std::make_shared<T>();
    }
};

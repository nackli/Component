/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "YamlStructCpp.h"
#include <iostream>
#include "yaml-cpp/yaml.h"
//#pragma comment(lib,"yaml-cppd.lib")
#include "ClassManage.h"
#include "Value.h"
#include "Properties.h"
#include "ClassAtom.h"
#include <memory>
/****************************************************************************************************/
struct SchemaLable
{
    using Key = const char *;
    Key strHead;
    Key strRootGrop;

    Key strClasses;
    Key strObjectId;
    Key strObjectName;
    Key strClassName;
    Key strProperties;

    static SchemaLable getDefault();
};

SchemaLable SchemaLable::getDefault()
{
    struct SchemaLable schemaLable;
    schemaLable.strHead = "Flow Controller";
    schemaLable.strRootGrop = ".";

    schemaLable.strClasses = "Classes";
    schemaLable.strObjectId = "objectId";
    schemaLable.strObjectName = "objectName";
    schemaLable.strClassName = "className";
    schemaLable.strProperties = "Properties";
    return schemaLable;
}
/****************************************************************************************************/
template <typename T_To, typename T_From>
static inline std::unique_ptr<T_To> DynamicUniqueCast(std::unique_ptr<T_From> obj)
{
    return std::unique_ptr<T_To>{dynamic_cast<T_To*>(obj.get()) ? dynamic_cast<T_To*>(obj.release()) : nullptr};
}

static inline bool OnGetNodeValue(YAML::Node nodeClasses, std::string& strValue)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsScalar())
        return false;
    strValue = nodeClasses.Scalar();
    return true;
}

static inline bool OnGetNodeValue(YAML::Node nodeClasses, int& iValue)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsScalar())
        return false;
    iValue = nodeClasses.as<int>();
    return true;
}

static inline bool OnGetNodeValue(YAML::Node nodeItem, Properties::MapStr2Value& mapProperty)
{
    if (nodeItem.IsNull() || !nodeItem.IsMap())
        return false;
    for (auto item : nodeItem)
    {
        if (nodeItem[item.first].IsScalar())
            mapProperty.insert(std::make_pair(item.first.as<std::string>(), Value(item.second.as<std::string>())));
    }
    return true;
}

static inline bool parseClassConfig(YAML::Node& nodeClasses)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsSequence())
        return false;
    for (const auto& nodeClass : nodeClasses)
    {
        std::string strClass;
        if (OnGetNodeValue(nodeClass[SchemaLable::getDefault().strClassName], strClass))
        {
            std::shared_ptr<ClassAtom> objClass = std::dynamic_pointer_cast <ClassAtom>(
                ClassManage::getDefaultClassManage().createObjectClass(strClass));
            if (!objClass)
            {
                std::cout << "memory alloc fail" << std::endl;
                continue;
            }
   
            std::string strId;
            if (OnGetNodeValue(nodeClass[SchemaLable::getDefault().strObjectId], strId))
                objClass->setObjectId(strId);
            else
            {
                std::cout << "please set object id" << std::endl;
                continue;
            }
               

            std::string strObjectName;
            if(OnGetNodeValue(nodeClass[SchemaLable::getDefault().strObjectName], strObjectName))
                objClass->setObjectName(strObjectName);

            Properties::MapStr2Value mapProperty;
            if (OnGetNodeValue(nodeClass[SchemaLable::getDefault().strProperties], mapProperty))
                objClass->addValue(mapProperty);

            if (!ClassManage::getDefaultClassManage().insertClass(objClass))
                std::cout << "insert data error" << std::endl;
   
        }
    }
    return ClassManage::getDefaultClassManage().initClassInfo();;
}
/****************************************************************************************************/
YamlStructCpp::YamlStructCpp()
{
}

YamlStructCpp::~YamlStructCpp()
{
}

bool YamlStructCpp::loadYamlData(const std::string strFilePath)
{
	if (strFilePath.empty())
		return false;
    YAML::Node nodeConfigs;
    try {
        nodeConfigs = YAML::LoadFile(strFilePath);
    }
    catch (YAML::BadFile& e) {
        std::cout << "read error!" << e.what() << std::endl;
        return false;
    }

    YAML::Node  nodeClasses = nodeConfigs[SchemaLable::getDefault().strClasses];

    parseClassConfig(nodeClasses);
    return true;
}


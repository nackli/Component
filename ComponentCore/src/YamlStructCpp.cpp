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
        //auto typeItem = nodeItem[item.first].Type();
        if (nodeItem[item.first].IsScalar())
            mapProperty.insert(std::make_pair(item.first.as<std::string>(), Value(item.second.as<std::string>())));
        //std::cout << item.first << "=" << typeItem << std::endl;
    }
    return true;
}

static inline bool OnCreateClassObject(std::string &strClassName, std::string &strLabel,
    std::string& strObjName, std::shared_ptr<Properties> pProp)
{
    if (strClassName.empty() || strLabel.empty())
        return false;
    if(ClassManage::getDefaultClassManage().insertClass(strLabel, strClassName, strObjName, pProp))
        return true;
    return false;
}

static inline bool parseClassConfig(YAML::Node& nodeClasses)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsSequence())
        return false;
    for (const auto& nodeClass : nodeClasses)
    {
        std::string strId;
        std::string strClass;
        std::string strObjectName;
        Properties::MapStr2Value mapProperty;
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strObjectId], strId);
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strObjectName], strObjectName);
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strClassName], strClass);
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strProperties], mapProperty);
        std::shared_ptr<Properties> pProp = std::make_shared<Properties>();
        pProp->addValue(mapProperty);
        OnCreateClassObject(strClass, strId, strObjectName, pProp);       
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
    //YAML::NodeType::value typeConfig = nodeConfigs.Type();
    //YAML::NodeType::value typeProcess = nodeConfigs["Classes"].Type();
    YAML::Node  nodeClasses = nodeConfigs[SchemaLable::getDefault().strClasses];
    //for (auto item : nodeConfigs)
    //{
    //    YAML::NodeType::value typeItem = nodeConfigs[item.first].Type();
    //    std::cout << item.first << "=" << typeItem << std::endl;
    //}
    parseClassConfig(nodeClasses);
    return true;
}


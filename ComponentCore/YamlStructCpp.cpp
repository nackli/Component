#include "YamlStructCpp.h"
#include <iostream>
#pragma comment(lib,"yaml-cppd.lib")
#include "ClassManage.h"


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

static bool OnGetNodeValue(YAML::Node nodeClasses, std::string& strValue)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsScalar())
        return false;
    strValue = nodeClasses.Scalar();
    return true;
}

//static bool OnGetNodeValue(YAML::Node nodeClasses, std::string& strValue)
//{
//    if (nodeClasses.IsNull() || !nodeClasses.IsScalar())
//        return false;
//    strValue = nodeClasses.Scalar();
//    return true;
//}

static bool OnGetNodeValue(YAML::Node nodeClasses, int& iValue)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsScalar())
        return false;
    iValue = nodeClasses.as<int>();
    return true;
}

static bool OnGetNodeValue(YAML::Node nodeItem, std::map<std::string,std::string> &mapProperty)
{
    if (nodeItem.IsNull() || !nodeItem.IsMap())
        return false;
    for (auto item : nodeItem)
    {
        YAML::NodeType::value typeItem = nodeItem[item.first].Type();
        if(nodeItem[item.first].IsScalar())
            mapProperty.insert(std::make_pair(item.first.as<std::string>(), item.second.as<std::string>()));
        std::cout << item.first << "=" << typeItem << std::endl;
    }
    return true;
}

bool YamlStructCpp::parseClassConfig(YAML::Node& nodeClasses)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsSequence())
        return false;
    for (const auto& nodeClass : nodeClasses)
    {
        std::string strId;
        std::string strClass;
        std::string strObjectName;
        std::map<std::string, std::string> mapProperty;
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strObjectId], strId);
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strObjectName], strObjectName);
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strClassName], strClass);
        OnGetNodeValue(nodeClass[SchemaLable::getDefault().strProperties], mapProperty);
        ClassManage::getDefaultClassManage().initLoadClass(strClass, strId, strObjectName);
    }

    return true;
}
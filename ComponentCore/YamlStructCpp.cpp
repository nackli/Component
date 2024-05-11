#include "YamlStructCpp.h"
#include <iostream>
#pragma comment(lib,"yaml-cppd.lib")
#include "ClassManage.h"
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
        nodeConfigs = YAML::LoadFile("./config.yml");
    }
    catch (YAML::BadFile& e) {
        std::cout << "read error!" << e.what() << std::endl;
        return false;
    }
    //YAML::NodeType::value typeConfig = nodeConfigs.Type();
    //YAML::NodeType::value typeProcess = nodeConfigs["Classes"].Type();
    YAML::Node  nodeClasses = nodeConfigs["Classes"];
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

static bool OnGetNodeValue(YAML::Node nodeClasses, int& iValue)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsScalar())
        return false;
    iValue = nodeClasses.as<int>();
    return true;
}

bool YamlStructCpp::parseClassConfig(YAML::Node& nodeClasses)
{
    if (nodeClasses.IsNull() || !nodeClasses.IsSequence())
        return false;
    for (const auto& procNode : nodeClasses)
    {
        std::string strId;
        std::string strClass;
        OnGetNodeValue(procNode["id"], strId);
        OnGetNodeValue(procNode["class"], strClass);
        ClassManage::getDefaultClassManage().initLoadClass(strClass, strId);
    }

    return true;
}
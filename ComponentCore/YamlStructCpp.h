#pragma once
#include <string>
#include "yaml-cpp/yaml.h"
class YamlStructCpp
{
public:
	YamlStructCpp();
	~YamlStructCpp();
	bool loadYamlData(const std::string);
private:
	bool parseClassConfig(YAML::Node&);
};


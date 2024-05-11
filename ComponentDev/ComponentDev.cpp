// ComponentDev.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <sstream>
#include <iomanip> 
#include <random>
#include "../ComponentCore/ClassManage.h"
#include "../ComponentCore/StringUtils.h"
#include "yaml-cpp/yaml.h"
#include "ObjectClass.h"


#pragma comment(lib,"./Debug/yaml-cppd.lib")
std::string getTimeAsString(std::string strFormat, time_t theTime)
{
    struct tm timeinfo = { 0 };
    localtime_s(&timeinfo , &theTime);

    std::ostringstream os;
    os << std::put_time(&timeinfo, strFormat.c_str());
    return os.str();

}
using Keys = std::vector<std::string>;
static void OnLoadYml()
{
    YAML::Node nodeConfigs;
    try {
        nodeConfigs = YAML::LoadFile("./config.yml");
    }
    catch (YAML::BadFile& e) {
        std::cout << "read error!" <<e.what()<< std::endl;
        return;
    }
    YAML::NodeType::value typeConfig = nodeConfigs.Type();
    Keys keyProcs = { "Processors", "Procs" };
    YAML::NodeType::value typeProcess = nodeConfigs["Processors"].Type();
    YAML::Node  nodeProcessors = nodeConfigs["Processors"];
    for (auto item : nodeConfigs)
    {
        YAML::NodeType::value typeItem = nodeConfigs[item.first].Type();
        std::cout << item.first << "=" << typeItem << std::endl;
    }
   
    for (const auto& procNode : nodeProcessors)
    {
        YAML::NodeType::value atat = procNode["id"].Type();
        std::string str = procNode["name"].as<std::string>();
        std::string str1 = procNode["class"].as<std::string>();
        int at = 0;
    }
}

int main()
{
    ::LoadLibrary(_T("ComDllTest.dll"));
    ::LoadLibrary(_T("TestDll.dll"));
    //if (hTest)
    {
        ClassManage::getDefaultClassManage().initLoadClass("xg.nanjing.CTestObj", "nihaonizainali");
        std::unique_ptr<ObjectClass> obj = ClassManage::getDefaultClassManage().GetObjectPrtFromLoadClass("nihaonizainali");
        if (obj)
            obj->initObject();
    }
    OnLoadYml();

    std::cout << "Hello World!\n";
   
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

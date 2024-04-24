// ComponentDev.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <sstream>
#include <iomanip> 
#include <random>
#pragma comment(lib,"../yaml-cpp/Debug/yaml-cppd.lib")
#include "../ComponentCore/ClassManage.h"
#include "../ComponentCore/StringUtils.h"
#include "yaml-cpp/yaml.h"

std::string getTimeAsString(std::string strFormat, time_t theTime)
{
    struct tm timeinfo = { 0 };
    localtime_s(&timeinfo , &theTime);

    std::ostringstream os;
    os << std::put_time(&timeinfo, strFormat.c_str());
    return os.str();

}

static void OnLoadYml()
{
    YAML::Node config;
    try {
        config = YAML::LoadFile("./config.yml");
    }
    catch (YAML::BadFile& e) {
        std::cout << "read error!" <<e.what()<< std::endl;
        return;
    }
    YAML::NodeType::value type12 = config.Type();
    YAML::NodeType::value type = config["Processors"].Type();
    YAML::Node  stra = config["Processors"];
    for (auto item : config)
    {
        std::cout << item.first << std::endl;
    }
   
    for (const auto& procNode : stra)
    {
        YAML::NodeType::value atat = procNode["id"].Type();
        std::string str = procNode["name"].as<std::string>();
        int at = 0;
    }
    YAML::NodeType::value at = stra.Type();
    std::string strafe = stra.as<std::string>();
}

int main()
{

    auto pairKv = StringUtils::spiltKv("nhao = zhongguo = shanghang");

    auto strExit = StringUtils::spiltLast("nhao");
    //OnLoadYml();
    std::string strTest = "xg.nanjing.CTestObj.txt";
    std::string std = StringUtils::getSplitData<std::string>(strTest, '.',4);
    ::LoadLibrary(_T("ComDllTest.dll"));
    ::LoadLibrary(_T("TestDll.dll"));
   // if (hTest)
    //{
    char sz = '0';
    char sz1 = 'a';
    char sz2 = 'A';
        std::unique_ptr<ObjectClass> obj = ClassManage::createObjectClass("xg.nanjing.CTestObj");
        if(obj)
            obj->initObject();
    //}
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

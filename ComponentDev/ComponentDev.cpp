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
#include "../ComponentCore/YamlStructCpp.h"
#include "ObjectClass.h"


int main()
{
    ::LoadLibrary(_T("ComDllTest.dll"));
    ::LoadLibrary(_T("TestDll.dll"));

    YamlStructCpp yamlLoad;
    yamlLoad.loadYamlData("./config.yml");

    std::unique_ptr<ObjectClass> obj = ClassManage::getDefaultClassManage().GetObjectPrtFromLoadClass("66e99f30-a866-3aa6-0000-000000000000");
    if (obj)
        obj->initObject();


    std::unique_ptr<ObjectClass> obj1 = ClassManage::getDefaultClassManage().GetObjectPrtFromLoadClass("44e88fd0-a833-3ee6-0000-000000000000");
    if (obj1)
        obj1->initObject();

    std::cout << "Hello World!\n";
    system("pause");
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

/*
 * @Author: nackli nackli@163.com
 * @Date: 2024-05-17 22:53:14
 * @LastEditors: nackli nackli@163.com
 * @LastEditTime: 2024-05-18 16:11:29
 * @FilePath: /Component/ComponentDev/ComponentDev.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// ComponentDev.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include <dlfcn.h> 
#endif
#include <sstream>
#include <iomanip> 
#include <random>
#include "ClassManage.h"
#include "StringUtils.h"
#include "YamlStructCpp.h"
#include "ObjectBase.h"
#include "Value.h"
#include <string>


int main()
{
#ifdef WIN32
    ::LoadLibrary(_T("ComDllTest.dll"));
    ::LoadLibrary(_T("TestDll.dll"));
#else
    void *handle = dlopen("./ComDllTest/libComDllTest.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) 
    {  
            fprintf (stderr, "%s ", dlerror());  
            exit(1);  
    }  
    void *hTest = dlopen("./TestDll/libTestDll.so", RTLD_NOW | RTLD_GLOBAL);
    if (!hTest) 
    {  
            fprintf (stderr, "%s ", dlerror());  
            exit(1);  
    }   
#endif
    YamlStructCpp yamlLoad;
    yamlLoad.loadYamlData("./config.yml");

    while (1)
    {
        Sleep(10000);
    }
    std::cout << "Hello World!\n";
#ifdef WIN32    
    system("pause");
#endif
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

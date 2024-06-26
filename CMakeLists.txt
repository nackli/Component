
#Written by Nack li <nackli@163.com>
#Copyright (c) 2024. All Rights Reserved.

#version
cmake_minimum_required(VERSION 3.16)
# project name
project(ComponentDev VERSION 1.0.0 LANGUAGES CXX)
set(BUILD_NUMBER "" CACHE STRING "Build number")
# set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

if(MSVC)
	#runtime library
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /Zi")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Zi")

	set(CMAKE_GENERATOR_PLATFORM Win32)
  add_compile_options(/W3 /utf-8 /bigobj /MP)
	#pdb 
	#set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG /OPT:REF /OPT:ICF")
	#set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
else()
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -O2 -fPIC -g")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -fPIC  -g")
endif()	

# default user option
option(ENABLE_TEST "Enable test" ON)

if(ENABLE_TEST)
  add_definitions(-DENABLE_TEST -D_CRT_SECURE_NO_WARNINGS)
endif()

# set msvc info
macro(add_msvc_options target)
  if(MSVC)
    target_compile_options(${target} PRIVATE
    /W4                # 设置警告级别为 4
    /WX                # 将警告视为错误
    /MP                # 启用多处理器编译
    /permissive-       # 禁用不严格的语言 conformance
    /Zc:__cplusplus    # 启用正确的 __cplusplus 宏值
    /Zc:inline         # 移除未使用的函数
    /Gm-               # 禁用最小生成（minimal rebuild）
    #/EHsc              # 指定异常处理模型
    )
  endif()
endmacro()

# generate exe
#add_executable(ComponentCore ${SOURCE_FILES})

#add_msvc_options(ComponentCore)

# add include path
#target_include_directories(ComponentCore PRIVATE include)

# link static lib
#find_library(STATIC_LIB libStatic.lib PATHS "${CMAKE_SOURCE_DIR}/libs/static")
#target_link_libraries(MyApp PRIVATE ${STATIC_LIB})

#  link dynamic lib
#find_library(DYNAMIC_LIB libDynamic.dll PATHS "${CMAKE_SOURCE_DIR}/libs/dynamic")
#find_library(DYNAMIC_LIB_IMPORT libDynamic.lib PATHS "${CMAKE_SOURCE_DIR}/libs/dynamic")
#target_link_libraries(MyApp PRIVATE ${DYNAMIC_LIB_IMPORT})

# 使用 Windows 的 DLL delay-load 机制
#set_target_properties(MyApp PROPERTIES LINK_FLAGS "/DELAYLOAD:libDynamic.dll")
# yaml-cpp
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

include(ExternalProject)
include(BundledYamlCpp)
use_bundled_yamlcpp(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "CompentDev")
endif()

# add sub project
 add_subdirectory(ComponentCore)
if(ENABLE_TEST)
  add_subdirectory(ComDllTest)
  add_subdirectory(TestDll)
  add_subdirectory(ComponentDev)
  add_dependencies(CompentDev ComDllTest TestDll)
endif()



# 指定安装规则
#install(TARGETS MyApp RUNTIME DESTINATION bin)
#install(FILES "${CMAKE_SOURCE_DIR}/libs/dynamic/libDynamic.dll" DESTINATION bin)
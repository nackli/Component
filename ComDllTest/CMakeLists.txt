cmake_minimum_required(VERSION 3.8)
#project(ComponentDev VERSION 0.14.0)
include_directories(../ComponentCore/inc)
#link_directories(${CMAKE_BINARY_DIR})

file(GLOB DEV_SOURCES "*.cpp")

if(MSVC)
    set(EXECUTABLE_FILE_NAME "ComDllTest.dll")
    set(EXECUTABLE_FILE_DESCRIPTION "${PRODUCT_NAME} agent")
endif()


add_library(ComDllTest SHARED ${DEV_SOURCES})
target_link_libraries(ComDllTest ComponentCore)

if(MSVC)
    set_target_properties(ComDllTest PROPERTIES COMPILE_FLAGS "/EHsc")
endif()

set_target_properties(ComDllTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(ComDllTest PROPERTIES OUTPUT_NAME ComDllTest)
set_target_properties(ComDllTest PROPERTIES ENABLE_EXPORTS True)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    target_compile_definitions(ComDllTest PUBLIC SERVICE_NAME="Nack Test Dev")
    add_definitions(-DWIN32_LEAN_AND_MEAN)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-reorder")
endif()

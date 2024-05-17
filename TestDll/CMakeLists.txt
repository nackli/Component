cmake_minimum_required(VERSION 3.8)
#project(ComponentDev VERSION 0.14.0)
include_directories(../ComponentCore/inc)
#link_directories(${CMAKE_BINARY_DIR})
file(GLOB DEV_SOURCES "*.cpp")

if(WIN32)
    set(EXECUTABLE_FILE_NAME "TestDll.dll")
    set(EXECUTABLE_FILE_DESCRIPTION "${PRODUCT_NAME} agent")

endif()

add_library(TestDll SHARED ${DEV_SOURCES})
target_link_libraries(TestDll ComponentCore)

set_target_properties(TestDll PROPERTIES COMPILE_FLAGS "/EHsc")
set_target_properties(TestDll PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(TestDll PROPERTIES OUTPUT_NAME TestDll)
#set_target_properties(TestDll PROPERTIES ENABLE_EXPORTS True)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    target_compile_definitions(TestDll PUBLIC SERVICE_NAME="Nack Test Dev")
    add_definitions(-DWIN32_LEAN_AND_MEAN)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-reorder")
endif()

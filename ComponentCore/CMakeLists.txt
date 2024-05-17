cmake_minimum_required(VERSION 3.16)

#project(ComponentDev VERSION 0.14.0)
include_directories(../yaml-cpp-src/include ./inc)
link_directories(../yaml-cpp-src/build/)

file(GLOB DEV_SOURCES "src/*.cpp")

if(WIN32)
    set(EXECUTABLE_FILE_NAME "ComponentCore.dll")
    set(EXECUTABLE_FILE_DESCRIPTION "${PRODUCT_NAME} agent")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)
#add_library(${DEV_SOURCES} ${RUNTIME_OUTPUT_DIRECTORY}/exports.def)
add_library(ComponentCore SHARED ${DEV_SOURCES})
target_link_libraries(ComponentCore PRIVATE yaml-cppd.lib)

if(WIN32)
	set_target_properties(ComponentCore PROPERTIES COMPILE_FLAGS "/EHsc")
endif()

set_target_properties(ComponentCore PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(ComponentCore PROPERTIES OUTPUT_NAME ComponentCore)
#set_target_properties(ComponentCore PROPERTIES ENABLE_EXPORTS True)

if (WIN32)
    target_compile_definitions(ComponentCore PUBLIC SERVICE_NAME="Nack Test Dev")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-reorder")
endif()

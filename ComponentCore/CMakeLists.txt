cmake_minimum_required(VERSION 3.16)
#project(ComponentDev VERSION 0.14.0)
include_directories(./inc)

if (MSVC)
set(COMCORE_LIB_PATH "${CMAKE_CURRENT_BINARY_DIR}/ComponentCore.lib")
else()
set(COMCORE_LIB_PATH "${CMAKE_CURRENT_BINARY_DIR}/ComponentCore")
endif()

file(GLOB DEV_SOURCES "src/*.cpp")

if(MSVC)
    set(EXECUTABLE_FILE_NAME "ComponentCore.dll")
    set(EXECUTABLE_FILE_DESCRIPTION "${PRODUCT_NAME} agent")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


set(BUILD_SHARED_LIBS ON)
#add_library(${DEV_SOURCES} ${RUNTIME_OUTPUT_DIRECTORY}/exports.def)

add_library(ComponentCore SHARED ${DEV_SOURCES})

if(MSVC)
    target_link_libraries(ComponentCore PRIVATE yaml-cppd.lib)
    set_target_properties(ComponentCore PROPERTIES COMPILE_FLAGS "/EHsc")
else()
    target_link_libraries(ComponentCore PRIVATE yaml-cpp)
endif()


set_target_properties(ComponentCore PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(ComponentCore PROPERTIES OUTPUT_NAME ComponentCore)
#set_target_properties(ComponentCore PROPERTIES ENABLE_EXPORTS True)

if (WIN32)
    target_compile_definitions(ComponentCore PUBLIC SERVICE_NAME="Nack Test Dev")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-reorder")
endif()

set(COMCORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "" FORCE)

target_include_directories(ComponentCore INTERFACE ${COMCORE_INCLUDE_DIR})
set_target_properties(ComponentCore PROPERTIES IMPORTED_LOCATION "${COMCORE_LIB_PATH}")

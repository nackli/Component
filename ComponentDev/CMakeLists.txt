cmake_minimum_required(VERSION 3.8)

include_directories(../ComponentCore)

file(GLOB DEV_SOURCES "*.cpp")

if(WIN32)
    set(EXECUTABLE_FILE_NAME "CompentDev.exe")
    set(EXECUTABLE_FILE_DESCRIPTION "${PRODUCT_NAME} agent")
endif()


add_executable(CompentDev ${DEV_SOURCES})
target_link_libraries(CompentDev ComponentCore)

set_target_properties(CompentDev PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(CompentDev PROPERTIES OUTPUT_NAME CompentDev)
#set_target_properties(CompentDev PROPERTIES ENABLE_EXPORTS True)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
if (WIN32)
    target_compile_definitions(CompentDev PUBLIC SERVICE_NAME="Nack Test Dev")
endif()

cmake_minimum_required(VERSION 3.8)

include_directories(../ComponentCore/inc)

file(GLOB DEV_SOURCES "*.cpp")

if(MSVC)
    set(EXECUTABLE_FILE_NAME "CompentDev.exe")
    set(EXECUTABLE_FILE_DESCRIPTION "${PRODUCT_NAME} agent")
endif()


add_executable(CompentDev ${DEV_SOURCES})
target_link_libraries(CompentDev ComponentCore)

if(MSVC)
    set_target_properties(CompentDev PROPERTIES COMPILE_FLAGS "/EHsc")
endif()

set_target_properties(CompentDev PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(CompentDev PROPERTIES OUTPUT_NAME CompentDev)
#set_target_properties(CompentDev PROPERTIES ENABLE_EXPORTS True)

if (MSVC)
    target_compile_definitions(CompentDev PUBLIC SERVICE_NAME="Nack Test Dev")
endif()

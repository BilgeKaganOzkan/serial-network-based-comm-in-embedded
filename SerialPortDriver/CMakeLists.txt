cmake_minimum_required(VERSION 3.5)

project(main
        VERSION 1.0)

set(CMAKE_CXX_STANDARD 11 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SOURCES
    src/SerialComm.cpp
    src/MqttComm.cpp
    src/IniParser.cpp
    src/Message.cpp
    app/main.cpp)

include_directories(./lib)

find_package(PahoMqttCpp REQUIRED)

add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE PahoMqttCpp::paho-mqttpp3-static)

set_target_properties(main PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    #OUTPUT_NAME "my_program_name" # Çıktı dosyasının adını değiştirebilirsiniz
)
cmake_minimum_required(VERSION 3.16)

project(CollectorConfigEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(CollectorConfigEditor
    ./src/Console.cpp
    ./src/main.cpp
    ./src/Menu.cpp
    ./src/PollTarget.cpp
    ./src/jsonSerializer.cpp
    ./src/fileStorage.cpp
    ./src/HttpServer.cpp
    ./src/NetworkManager.cpp
)

target_compile_options(CollectorConfigEditor PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_include_directories(CollectorConfigEditor PRIVATE
    third_party
)

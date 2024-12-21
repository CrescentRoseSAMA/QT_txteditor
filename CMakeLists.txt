cmake_minimum_required(VERSION 3.6)
project(start)

set(CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE AUTOUIC ON)



# 注意 ： 要想使用qt5_add_resources，必须先find_package到Qt的路径或者手动指定QT_DIR
set(QT_SOURCE_FILE ui.qrc) # 将资源文件放到工程目录下，该部分会由RCC编译器预编译为cpp文件
qt5_add_resources(QT_RESOURCES ${QT_SOURCE_FILE})

set(CPP_SOURCE main.cpp mainwin.cpp)



add_executable(start ${CPP_SOURCE} ${QT_RESOURCES})

target_link_libraries(start PRIVATE Qt5::Core Qt5::Widgets)
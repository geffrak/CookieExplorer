cmake_minimum_required(VERSION 3.9)
project(CookieExplorer)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core Widgets WebEngine WebEngineWidgets REQUIRED)

add_executable(CookieExplorer main.cpp)

target_link_libraries(CookieExplorer Qt5::Core Qt5::Widgets Qt5::WebEngineCore Qt5::WebEngine Qt5::WebEngineWidgets )


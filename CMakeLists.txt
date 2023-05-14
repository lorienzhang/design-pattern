CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(DesignPattern)

set(CMAKE_CXX_STANDARD 11)


# add_executable(ScopeGurad ./strategy/strategy1.cpp)

# 观察者observer模式
add_executable(observer ./observer/FileDownloader5.cpp)
# add_executable(observer ./observer/FileDownloader_Generic1.cpp)
# add_executable(observer ./observer/FileDownloader_Generic2.cpp)
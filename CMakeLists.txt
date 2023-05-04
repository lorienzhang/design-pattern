CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(DesignPattern)

aux_source_directory(./ScopeGuard DIR_SRC)

add_executable(ScopeGurad ${DIR_SRC})

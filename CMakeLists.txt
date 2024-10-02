cmake_minimum_required(VERSION 3.29)
project(MonsterFactory)

set(CMAKE_CXX_STANDARD 14)

include_directories(MonsterFactoryCore/src)

add_executable(MonsterFactory
    MonsterFactoryCore/src/cliente.h
    MonsterFactoryCore/src/combiner.h
    MonsterFactoryCore/src/delivery.h
    MonsterFactoryCore/src/furnace.h
    MonsterFactoryCore/src/garbageCollector.h
    MonsterFactoryCore/src/inspector.h
    MonsterFactoryCore/src/logFunctions.cpp
    MonsterFactoryCore/src/material.h
    MonsterFactoryCore/src/monster.h
    MonsterFactoryCore/src/quality.h
    MonsterFactoryCore/src/queues.h
    MonsterFactoryCore/src/sources.h
    MonsterFactoryCore/src/storage.h
    MonsterFactoryCore/src/tray.h
    MonsterFactoryCore/main.cpp
)

cmake_minimum_required(VERSION 3.16)

project(MonsterFactoryGuiQt2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        gamescreen.cpp
        gamescreen.h
        gamescreen.ui
        assets.qrc
        worker.cpp

        MonsterFactoryCore/src/cliente.cpp
        MonsterFactoryCore/src/combiner.cpp
        MonsterFactoryCore/src/delivery.cpp
        MonsterFactoryCore/src/furnace.cpp
        MonsterFactoryCore/src/garbageCollector.cpp
        MonsterFactoryCore/src/inspector.cpp
        MonsterFactoryCore/src/logFunctions.cpp
        MonsterFactoryCore/src/material.cpp
        MonsterFactoryCore/src/monster.cpp
        MonsterFactoryCore/src/quality.cpp
        MonsterFactoryCore/src/queues.cpp
        MonsterFactoryCore/src/sources.cpp
        MonsterFactoryCore/src/storage.cpp
        MonsterFactoryCore/src/tray.cpp
        logFunctions.h
        delivery.h
        cliente.h
        combiner.h
        furnace.h
        garbageCollector.h
        inspector.h
        material.h
        monster.h
        quality.h
        queues.h
        sources.h
        tray.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

qt_add_executable(MonsterFactoryGuiQt2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        gamescreen.h gamescreen.cpp gamescreen.ui
        assets.qrc
        logFunctions.h
        core.h
        delivery.h
        storage.h
        cliente.h
        combiner.h
        furnace.h
        garbageCollector.h
        inspector.h
        material.h
        monster.h
        quality.h
        queues.h
        sources.h
        tray.h
        worker.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MonsterFactoryGuiQt2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MonsterFactoryGuiQt2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MonsterFactoryGuiQt2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MonsterFactoryGuiQt2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MonsterFactoryGuiQt2)
endif()
set_target_properties(MonsterFactoryGuiQt2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MonsterFactoryGuiQt2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MonsterFactoryGuiQt2)
endif()

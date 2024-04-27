cmake_minimum_required(VERSION 3.5)

project(ICP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        user.cpp
        user.h
        obstacle.cpp
        obstacle.h
        enemy.cpp
        enemy.h
        button.cpp
        button.h
        horizontalbar.cpp
        horizontalbar.h
        star.cpp
        star.h
        heart.cpp
        heart.h
        gameinfo.cpp
        gameinfo.h
        timer.cpp
        timer.h
        popup.cpp
        popup.h
        enemyitem.cpp
        enemyitem.h
        mapwindow.cpp
        mapwindow.h
        mapwindow.ui
        ObstacleItem.h
        robotdialog.cpp
        robotdialog.cpp
        robotitem.cpp
        robotitem.h
        gamemaster.cpp
        gamemaster.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ICP
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        user.h user.cpp
        obstacle.h obstacle.cpp
        enemy.h enemy.cpp
        button.h button.cpp
        horizontalbar.h horizontalbar.cpp
        star.h star.cpp
        heart.h heart.cpp
        gameinfo.h gameinfo.cpp
        timer.cpp timer.h
        popup.cpp popup.h
        enemyitem.cpp enemyitem.h
        mapwindow.cpp mapwindow.h
        robotdialog.cpp robotdialog.h
        robotitem.cpp robotitem.h
        gamemaster.cpp gamemaster.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ICP APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ICP SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ICP
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ICP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ICP)
endif()
set_target_properties(ICP PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ICP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ICP)
endif()

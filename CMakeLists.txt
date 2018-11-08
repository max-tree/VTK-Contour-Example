cmake_minimum_required(VERSION 3.4)
project(VTKContourExample)
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(QT5GUI)
FIND_PACKAGE(QT5OpenGL)
FIND_PACKAGE(VTK REQUIRED)
include(${VTK_USE_FILE})

include_directories(${VTK_INCLUDE_DIRS})

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

SET(MYSOURCE
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    )
add_executable(${PROJECT_NAME} 
    ${MYSOURCE}
    ${MY_RES}
    )

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL
    ${VTK_LIBRARIES}
    )



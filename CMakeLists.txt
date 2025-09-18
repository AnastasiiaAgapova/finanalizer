cmake_minimum_required(VERSION 3.16)

project(finanalizer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Charts)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(finanalizer
  main.cpp
  transactions/transaction.h transactions/transaction.cpp
  transactions/connector.h
  transactions/threecolumncsvparser.h transactions/threecolumncsvparser.cpp
  transactions/categorydetector.h
  transactions/simplecategorydetector.h transactions/simplecategorydetector.cpp
  transactions/database.h transactions/database.cpp
  widgets/mainwindow.h widgets/mainwindow.cpp
  widgets/databasemodel.h widgets/databasemodel.cpp
  transactions/filter.h
  transactions/filters/timeperiod.h transactions/filters/timeperiod.cpp
  transactions/filters/category.h transactions/filters/category.cpp
  widgets/piechart.h widgets/piechart.cpp
  widgets/namedpieslice.h widgets/namedpieslice.cpp
  widgets/piechartbuilder.h widgets/piechartbuilder.cpp
  widgets/daterangeedit.h widgets/daterangeedit.cpp
  appconfig.h appconfig.cpp
  transactions/databasestorage.h transactions/databasestorage.cpp

)

target_include_directories(finanalizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(finanalizer PRIVATE Qt${QT_VERSION_MAJOR}::Core
                                          Qt${QT_VERSION_MAJOR}::Widgets
                                          Qt${QT_VERSION_MAJOR}::Charts)
target_link_libraries(finanalizer PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS finanalizer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

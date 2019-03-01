cmake_minimum_required(VERSION 3.0)

project(hospital)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS} lib)

# lib

file(GLOB_RECURSE LIB_SRCS lib/*.cpp)
file(GLOB_RECURSE LIB_HDRS lib/*.hpp)
add_library(hospital-lib STATIC ${LIB_HDRS} ${LIB_SRCS})

# EXE

file(GLOB_RECURSE EXE_SRCS src/*.cpp)
file(GLOB_RECURSE EXE_HDRS src/*.hpp)
file(GLOB_RECURSE EXE_FORMS forms/*.ui)

add_executable(hospital ${EXE_HDRS} ${EXE_SRCS} ${EXE_FORMS})
target_link_libraries(hospital PUBLIC ${Qt5Core_QTMAIN_LIBRARIES} ${Qt5Widgets_LIBRARIES})
target_compile_features(hospital PUBLIC cxx_std_17)

# test

find_package(GTest MODULE)

if(GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})
    file(GLOB_RECURSE TEST_SRCS test/*.cpp)
    add_executable(hospital-test ${TEST_SRCS})
    target_link_libraries(hospital-test PRIVATE hospital-lib GTest::GTest GTest::Main ${Qt5Core_QTMAIN_LIBRARIES} ${Qt5Widgets_LIBRARIES})
    add_test(AllTestsIn hospital-test)
endif(GTEST_FOUND)








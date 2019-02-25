cmake_minimum_required(VERSION 3.0)

project(hospital)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS src/*.hpp)
file(GLOB_RECURSE FORMS forms/*.ui)

add_executable(hospital ${HDRS} ${SRCS} ${FORMS})
target_link_libraries(hospital PUBLIC ${Qt5Core_QTMAIN_LIBRARIES} ${Qt5Widgets_LIBRARIES})
target_compile_features(hospital PUBLIC cxx_std_17)

if(WIN32 AND MINGW)
	list(APPEND NOTELIST_LINK_OPTIONS "-mwindows")
endif()

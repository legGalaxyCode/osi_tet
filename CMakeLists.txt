cmake_minimum_required(VERSION 3.17)
project(sfml-test)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/Program Files/SFML-2.5.1/lib/cmake/SFML")
set(THOR_DIR "C:/Program Files/Thor/cmake")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
add_executable(sfml-test main.cpp button.cpp button.h)
target_link_libraries(sfml-test sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

#find_package(Thor 2 REQUIRED)
#include_directories(${THOR_INCLUDE_DIR})
#target_link_libraries(sfml-test ${THOR_LIBRARY})


#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
#find_package(SFML REQUIRED system window graphics network audio)
#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(sfml-test ${SFML_LIBRARIES})
#endif()
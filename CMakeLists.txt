cmake_minimum_required(VERSION 3.29)
project(NNFramework)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_BUILD_TYPE Release)


set(OPENCV_DIR "C:/Users/28762/Desktop/cppLibs/opencv")
set(BOOST_DIR "C:/Users/28762/Desktop/cppLibs/boost_1_86_0/boost")
set(PYTHON_DIR "C:/Users/28762/AppData/Local/Programs/Python/Python313")


#include_directories(
#        ${PYTHON_DIR}/include
#)

add_executable(
        ${PROJECT_NAME}
        #NNFramework/src/mainFW.cpp
        #NNFramework/headers/opencv.h
        NNFramework/src/macro.cpp
        NNFramework/headers/deprecated.h
)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${OPENCV_DIR}/build/include # includes of OpenCV
        ${PYTHON_DIR}/include
)

target_link_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${OPENCV_DIR}/build/x64/vc16/lib # libs of OpenCV
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        opencv_world4100d.lib
        ${PYTHON_DIR}/libs/python313.lib
)



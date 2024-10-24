cmake_minimum_required(VERSION 3.29)
project(NNFramework)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_BUILD_TYPE Release)   # 针对 Python312 中没有关于 python312_d.lib 因此选择 Release


set(OPENCV_DIR "C:/Users/28762/Desktop/cppLibs/opencv")
set(BOOST_DIR "C:/Users/28762/Desktop/cppLibs/boost_1_86_0/boost")
set(PYTHON_DIR "C:/Users/28762/anaconda3/envs/NNF")
# set(HASKELL_DIR "C:/ghcup/ghc/9.4.8") # todo: 待测试(Linux)


find_package(Python3 COMPONENTS Interpreter REQUIRED)


add_compile_options(


)

add_executable(
        ${PROJECT_NAME}
        #NNFramework/src/mainFW.cpp
        #NNFramework/headers/opencv.h
        # NNFramework/src/macro.cpp
        # NNFramework/headers/deprecated.h
        NNFramework/src/test.cpp
        # NNFramework/headers/mt_queue.hpp
)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${OPENCV_DIR}/build/include # includes of OpenCV
        ${PYTHON_DIR}/include
        ${CMAKE_SOURCE_DIR}/hk/app
        ${CMAKE_SOURCE_DIR}/NNFramework/headers
        # ${HASKELL_DIR}/include # todo: 待测试 Linux
)

target_link_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${OPENCV_DIR}/build/x64/vc16/lib # libs of OpenCV
        # ${HASKELL_DIR}/lib/x86_64-windows-ghc-9.4.8/ghc-9.4.8 # todo: 待测试 Linux
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        opencv_world4100d.lib
        ${PYTHON_DIR}/libs/python312.lib
        # ${HASKELL_DIR}/lib/x86_64-windows-ghc-9.4.8/ghc-9.4.8/libHSghc-9.4.8_p.a # todo: 待测试 Linux
)



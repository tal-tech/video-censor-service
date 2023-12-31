cmake_minimum_required(VERSION 3.10)

set(SERVICE_NAME cppservice_ch)

project(${SERVICE_NAME})

set (CPP_SERVICE_MAJOR_VERSION 0)
set (CPP_SERVICE_MINOR_VERSION 8)
set (CPP_SERVICE_PATCH_VERSION 1)
set (CPP_SERVICE_VERSION ${CPP_SERVICE_MAJOR_VERSION}.${CPP_SERVICE_MINOR_VERSION}.${CPP_SERVICE_PATCH_VERSION})

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/package")


######################################################################
#全局编译标志
######################################################################

SET (CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,$ORIGIN/../lib" )

SET (CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,$ORIGIN/../lib" )






set(CMAKE_SKIP_BUILD_RPATH TRUE)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -fsanitize-address-use-after-scope")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=bounds-strict")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")

######################################################################
#全局链接和包含
######################################################################
# include_directories(${PROJECT_SOURCE_DIR}/include)
# file(GLOB TAlASR_LIB ${PROJECT_SOURCE_DIR}/lib/lib*.*)
#################################################################L#####
#全局编译输出指定
######################################################################

IF(CMAKE_BUILD_TYPE MATCHES Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug/lib/${BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug/lib/${BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug/bin/${BUILD_TYPE})
add_definitions(-D__STDC_CONSTANT_MACROS)

find_package(PkgConfig REQUIRED)
pkg_check_modules(AVCODEC REQUIRED IMPORTED_TARGET libavcodec)
pkg_check_modules(AVFORMAT REQUIRED IMPORTED_TARGET libavformat)
pkg_check_modules(AVFILTER REQUIRED IMPORTED_TARGET libavfilter)
pkg_check_modules(AVDEVICE REQUIRED IMPORTED_TARGET libavdevice)
pkg_check_modules(AVUTIL REQUIRED IMPORTED_TARGET libavutil)
pkg_check_modules(SWSCALE REQUIRED IMPORTED_TARGET libswscale)

SET(Python3_INCLUDE_DIRS "/usr/include/python3.7m")
SET(Python3_LIBRARIES "/usr/lib/python3.7/config-3.7m-x86_64-linux-gnu/libpython3.7.so")
message("Python3: " ${Python3_INCLUDE_DIRS})
message("Python3: " ${Python3_LIBRARIES})

######################################################################
#子工程目录
######################################################################

# add_subdirectory(chrome-base)
add_subdirectory(audio-censor-service)
# add_subdirectory(demuxer)
######################################################################
#算法sdk编译对象
######################################################################



######################################################################
#http service编译对象
######################################################################

# target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/audio-censor-service/audio-censor.h)
# message("audio-censor ${CMAKE_SOURCE_DIR}/audio-censor-service/audio-censor.h")

add_executable(test
    test.cpp)

target_link_libraries(test
    ${Python3_LIBRARIES}
    base
    audio-censor
    # pthread
    # PkgConfig::AVCODEC
    # PkgConfig::AVFORMAT
    # PkgConfig::AVFILTER
    # PkgConfig::AVDEVICE
    # PkgConfig::AVUTIL
    # PkgConfig::SWSCALE
    # demuxer
    
    )


######################################################################
#程序发布设置
######################################################################

# install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ DESTINATION bin)
# install(DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ DESTINATION lib)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/kafka/cppkafka/lib/ DESTINATION lib)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/proto/libs/ DESTINATION lib)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/alg/resource/ DESTINATION bin/res)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/alg/lib/ DESTINATION lib)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/alg/third_party/ DESTINATION lib)
# install(DIRECTORY config/ DESTINATION bin/config)

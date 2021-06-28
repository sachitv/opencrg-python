cmake_minimum_required(VERSION VERSION 3.4...3.18)

project(opencrg-c-api)

if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix.
    add_compile_options(-fPIC)
endif()

#Generate the static library from the library sources
add_library(opencrg-c-api STATIC 
    src/crgContactPoint.c
    src/crgEvalpk.c
    src/crgEvaluv2xy.c
    src/crgEvalxy2uv.c
    src/crgEvalz.c
    src/crgLoader.c
    src/crgMgr.c
    src/crgMsg.c
    src/crgOptionMgmt.c
    src/crgPortability.c
    src/crgStatistics.c
)

target_include_directories(opencrg-c-api
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include/public
)

target_include_directories(opencrg-c-api
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/include/private
)

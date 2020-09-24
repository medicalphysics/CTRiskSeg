# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.10...3.20)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(ctriskseglib VERSION 0.1.0 LANGUAGES CXX)

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Find packages go here.
find_package(Threads REQUIRED) # for threading support
find_package(Torch REQUIRED)

set(HEADER_LIST 
    "${ctriskseglib_SOURCE_DIR}/include/ctriskseg/ctriskseg.h"
    "${ctriskseglib_SOURCE_DIR}/include/ctriskseg/transform.h"
    )

add_library(libctriskseg 
    src/ctriskseg.cpp
    src/transform.cpp
    ${HEADER_LIST}
	)
target_include_directories(libctriskseg PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(libctriskseg PRIVATE 
    Threads::Threads
    ${TORCH_LIBRARIES}
    )

## Install
install(TARGETS libctriskseg 
    EXPORT libctriskseg
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    )

# Due to windows not being windows on 34/64 bits and xraylib puts it's dll in system32 folder we try to install 
# the library from system32 folder regardless of cmake or NSIS being 64 or 32 bits
if(WIN32)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    install(FILES ${TORCH_DLLS} DESTINATION bin OPTIONAL)
endif(WIN32)
install(FILES ${HEADER_LIST} DESTINATION include)

# Testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Docs by doxygen
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    find_package(Doxygen)
    find_package(Sphinx)
    if(Doxygen_FOUND AND Sphinx_FOUND)
	    add_subdirectory(docs)
    else()
	    message(STATUS "Doxygen or Sphinx not found, not building docs")
    endif()
endif()

# Examples
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(BUILD_EXAMPLES "Build examples" ON)
    if(BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()
endif()
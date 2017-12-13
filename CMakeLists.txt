# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(access_approval_pam)

# The version number.
set (AccessApprovalPam_VERSION_MAJOR 0)
set (AccessApprovalPam_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/src/config.h"
  )

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/build")

SET(libSRCs src/pam_access_approval.c)
ADD_LIBRARY(pam_access_approval SHARED ${libSRCs})
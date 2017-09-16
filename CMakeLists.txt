#Minimum cmake version asked
cmake_minimum_required(VERSION 2.8)

#Project Name
project(mUsbStereoGrabber)

##
#External packages
##
add_subdirectory(external)


#Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -pthread")

##########
#Packages#
##########

######
#Srcs#
######

find_package(OpenCV REQUIRED)

##########
#Includes#
##########

##
#Classic packages
##
#if( MYPACKAGE_FOUND )
#   include_directories(${MYPACKAGE_INCLUDE_DIRS})
#endif()

##
#External packages
##
include_directories(
   include
   external/externalLibraryExample/include
   )

#LIBS
set(ALL_LIBS
   MIEOSPO_EXTLIBEXAMPLE_LIB
   )

###################
#Generated helpers#
###################
#Generated helpers such as paths and others stuffs that can be used in cpp afterward
#Usefull when you need an absolute path
add_subdirectory(helpers)
include_directories(${CMAKE_BINARY_DIR}/generated/helpers )

#########
#Outputs#
#########
#Set outputs dir
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

################
#Subdirectories#
################
#internalLibraryExample
add_subdirectory(src/internalLibraryExample)
include_directories(include/internalLibraryExample)
#Tests
add_subdirectory(src)

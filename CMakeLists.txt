#Minimum cmake version asked
cmake_minimum_required(VERSION 2.8)

#Project Name
project(mUsbStereoGrabber)

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

include_directories(
   include
   )

#########
#Outputs#
#########
#Set outputs dir
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

################
#Subdirectories#
################

add_subdirectory(src)

#LIBS
set(mUsbStereoGrabber_ALL_LIBS
   mUsbStereoGrabber_LIB
   )



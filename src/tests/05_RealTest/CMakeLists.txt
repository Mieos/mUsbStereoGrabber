#03_USEHELPERS

#Create the subdirectory for the binary files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/05_RealTest)

#Include the headers
#NONE

#Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/05_RealTest)

#Create the binary files
add_executable(test05Run main.cpp)
target_link_libraries(test05Run mUsbStereoGrabber_LIB)

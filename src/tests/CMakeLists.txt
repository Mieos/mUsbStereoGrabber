#Test stereo camera

#Create the subdirectory for the binary files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

#Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

#Create the binary files
add_executable(runStereoCameraTest main.cpp)
target_link_libraries(runStereoCameraTest mUsbStereoGrabber_LIB)

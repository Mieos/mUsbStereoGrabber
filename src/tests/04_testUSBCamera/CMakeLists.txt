#03_USEHELPERS

#Create the subdirectory for the binary files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/04_testUSBCamera)

#Include the headers
#NONE

#Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/04_testUSBCamera)

#Create the binary files
add_executable(test04Run main.cpp)
target_link_libraries(test04Run ${OpenCV_LIBS})

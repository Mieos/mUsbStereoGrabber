add_library(mUsbStereoGrabber_LIB UsbOpencvStereoGrabber.cpp)
target_link_libraries(mUsbStereoGrabber_LIB ${OpenCV_LIBS})

add_subdirectory(tests)

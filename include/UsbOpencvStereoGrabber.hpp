#ifndef __USBOPENCVSTEREOGRABBER_HPP_INCLUDED__
#define __USBOPENCVSTEREOGRABBER_HPP_INCLUDED__

#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>

class UsbOpencvStereoGrabber {

public:
   //Contructor & destructor
   UsbOpencvStereoGrabber(size_t fpsWanted=10); 
   ~UsbOpencvStereoGrabber();
   //Get the current left and right frame
   //Return false if unitialzed, true if success
   bool getFrames(cv::Mat & leftI, cv::Mat & rightI);

private:
   cv::Mat currentImageLeft;
   cv::Mat currentImageRight;
   bool initialized;
   bool leftReady,rightReady, allReady;
   bool endAsked;
   static void runLeftThread(UsbOpencvStereoGrabber* context);
   static void runRightThread(UsbOpencvStereoGrabber* context);
   std::thread leftThread, rightThread;
   std::mutex lmutex, rmutex;
   size_t fpsUsed;
};

#endif //__USBOPENCVSTEREOGRABBER_HPP_INCLUDED__

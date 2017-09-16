#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>

class UsbOpencvStereoGrabber {

public:
   UsbOpencvStereoGrabber();
   ~UsbOpencvStereoGrabber();
   bool getFrames(cv::Mat & leftI, cv::Mat & rightI);

private:
   cv::Mat currentImageLeft;
   cv::Mat currentImageRight;
   bool initialized;
   bool leftReady,rightReady;
   bool endAsked;
   static void runLeftThread(UsbOpencvStereoGrabber* context);
   static void runRightThread(UsbOpencvStereoGrabber* context);
   std::thread leftThread, rightThread;
   std::mutex lmutex, rmutex;
};
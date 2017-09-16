#include "UsbOpencvStereoGrabber.hpp"
#include <unistd.h>

void UsbOpencvStereoGrabber::runLeftThread(UsbOpencvStereoGrabber* context){
   cv::VideoCapture capLeft(0);

   if(!capLeft.isOpened()){  // check if we succeeded
      std::cout << "Error opening USB camera" << std::endl;
      context->endAsked=true;
   }


   while(!context->endAsked){
      usleep(100);
      cv::Mat frame;
      capLeft >> frame;
      context->lmutex.lock();
      context->currentImageLeft = frame.clone();
      context->leftReady=true;
      context->lmutex.lock();
   }

}

void UsbOpencvStereoGrabber::runRightThread(UsbOpencvStereoGrabber* context){

   cv::VideoCapture capRight(1);
   capRight.set(CV_CAP_PROP_FPS,10);

   if(!capRight.isOpened()){  // check if we succeeded
      std::cout << "Error opening USB camera" << std::endl;
      context->endAsked=true;
   }

   while(!context->endAsked){
      usleep(100);
      cv::Mat frame;
      capRight >> frame;
      context->rmutex.lock();
      context->currentImageRight = frame.clone();   
      context->rightReady=true;
      context->rmutex.unlock();
   }



}


UsbOpencvStereoGrabber::UsbOpencvStereoGrabber() : initialized(false), endAsked(false), leftReady(false){
   this->leftThread = std::thread(runLeftThread, this);
   this->rightThread = std::thread(runRightThread, this);
}

UsbOpencvStereoGrabber::~UsbOpencvStereoGrabber(){
   this->endAsked=true;
   this->leftThread.join();
   this->rightThread.join();
}

bool UsbOpencvStereoGrabber::getFrames(cv::Mat & leftI, cv::Mat & rightI){
   if(!((this->leftReady)&&(this->rightReady))){
      return false;
   }
   this->rmutex.lock();
   this->lmutex.lock();
   leftI = this->currentImageLeft.clone();
   rightI = this->currentImageRight.clone();
   this->lmutex.unlock();
   this->rmutex.unlock();
   return true;
}


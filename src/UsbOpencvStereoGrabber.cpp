#include "UsbOpencvStereoGrabber.hpp"
#include <unistd.h>

//Constructor
UsbOpencvStereoGrabber::UsbOpencvStereoGrabber(size_t fpsWanted) : initialized(false), endAsked(false), leftReady(false), allReady(false), fpsUsed(fpsWanted){
   this->leftThread = std::thread(runLeftThread, this);
   this->rightThread = std::thread(runRightThread, this);
}

//Destructor
UsbOpencvStereoGrabber::~UsbOpencvStereoGrabber(){
   //This will stop the main loop of the threads
   this->endAsked=true;
   //Waiting threads
   this->leftThread.join();
   this->rightThread.join();
}

void UsbOpencvStereoGrabber::runLeftThread(UsbOpencvStereoGrabber* context){
   
   //Left first
   cv::VideoCapture capLeft(0);
   //FPS limit
   capLeft.set(CV_CAP_PROP_FPS,context->fpsUsed);

   //Check if the camera is connected
   if(!capLeft.isOpened()){  // check if we succeeded
      std::cout << "Error opening USB camera (left)" << std::endl;
      context->endAsked=true;
   }

   //Init the grabber left
   cv::Mat initFrame;
   capLeft >> initFrame;
   context->currentImageLeft = initFrame.clone();
   context->leftReady=true;

   //Main loop
   while(!context->endAsked){
      cv::Mat frame;
      capLeft >> frame;
      context->lmutex.lock();
      context->currentImageLeft = frame.clone();
      context->lmutex.unlock();
   }

}

void UsbOpencvStereoGrabber::runRightThread(UsbOpencvStereoGrabber* context){

   //Wait for left first
   while(!context->leftReady){
      usleep(10000);
   }

   //Now right
   cv::VideoCapture capRight(1); 
   //FPS limit
   capRight.set(CV_CAP_PROP_FPS,context->fpsUsed);

   if(!capRight.isOpened()){  // check if we succeeded
      std::cout << "Error opening USB camera (right)" << std::endl;
      context->endAsked=true;
   }

   //Init the grabber right
   cv::Mat initFrame;
   capRight >> initFrame;
   context->currentImageRight = initFrame.clone();
   context->rightReady=true;

   //Can start grabbing images
   context->allReady=true;

   //Main loop
   while(!context->endAsked){
      cv::Mat frame;
      capRight >> frame;
      context->rmutex.lock();
      context->currentImageRight = frame.clone();   
      context->rmutex.unlock();
   }

}

bool UsbOpencvStereoGrabber::getFrames(cv::Mat & leftI, cv::Mat & rightI){
   
   //Check if initialized
   if(!allReady){
      return false;
   }

   //Lock
   this->rmutex.lock();
   this->lmutex.lock();
   //Clone images
   leftI = this->currentImageLeft.clone();
   rightI = this->currentImageRight.clone();
   //Unlock
   this->lmutex.unlock();
   this->rmutex.unlock();
   return true;
   
}


#include <iostream>
#include <string>
#include <unistd.h>
#include "UsbOpencvStereoGrabber.hpp"

//Test Stereo Grabber
int main(int argc, char *argv[]){

   std::cout << std::endl << "Test Stereo Camea USB:" << std::endl << std::endl;

   UsbOpencvStereoGrabber grabber(20);

   bool endAsk=false;

   cv::Mat lI, rI;
   int waitkeyNum = -1;

   std::cout << "Camera started : press esc to end" << std::endl;
   while(!endAsk){

      usleep(100);
      
      if(grabber.getFrames(lI,rI)){
         cv::imshow("Left", lI);
         cv::imshow("Right", rI);
         waitkeyNum = cv::waitKey(30);
         if(waitkeyNum==27){ //Seems like this number computer dependant.. TODO fix that
            endAsk=true;
         }
      }

   }

   std::cout << std::endl << "Ending.. " << std::endl << std::endl;

   return 0;
}

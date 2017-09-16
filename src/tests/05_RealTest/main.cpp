#include <iostream>
#include <string>

#include <unistd.h>

#include "pathsHelpers.hpp"

#include "UsbOpencvStereoGrabber.hpp"

int main(int argc, char *argv[]){

   std::cout << std::endl << "Test :" << std::endl << std::endl;

   //Get and print the path to data
   std::string path = MIEOS_HELPERS_DATAPATH_GENERATED;

   UsbOpencvStereoGrabber grabber;

   bool endAsk=false;

   cv::Mat lI, rI;
   int waitkeyNum = -1;

   std::cout << "WAITING" << std::endl;
   usleep(1000000);
   std::cout << "OK?" << std::endl;
   
   while(!endAsk){

      if(grabber.getFrames(lI,rI)){
         cv::imshow("Left", lI);
         cv::imshow("Right", rI);
         waitkeyNum = cv::waitKey(30);
         if(waitkeyNum==27){ //Seems like this number computer dependant.. TODO fix that
            endAsk=true;
         }
      } else {
         std::cout << "NOPE" << std::endl;
      }


   }


   //Read a data file
   std::cout << std::endl;

   std::cout << "Ending.. " << std::endl << std::endl;

   return 0;
}

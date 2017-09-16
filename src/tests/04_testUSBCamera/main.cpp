#include <iostream>
#include <string>
#include <fstream>

#include "pathsHelpers.hpp"

#include "opencv2/opencv.hpp"

int main(int argc, char *argv[]){

   std::cout << std::endl << "TestUSB :" << std::endl << std::endl;

   //Get and print the path to data
   std::string path = MIEOS_HELPERS_DATAPATH_GENERATED;

   cv::VideoCapture cap(0); // open the default camera

   if(!cap.isOpened()){  // check if we succeeded
      std::cout << "Error opening USB camera" << std::endl;
      return -1;
   }

   int waitkeyNum=-1;
   bool endAsked=false;

   while(!endAsked){
      cv::Mat frame;
      cap >> frame;

      imshow("Image", frame);

      waitkeyNum = cv::waitKey(30);

      if(waitkeyNum==27){ //Seems like this number computer dependant.. TODO fix that
         endAsked=true;
      } else {
         //std::cout << waitkeyNum << std::endl;
      }
   
   }
  //Read a data file
   std::cout << std::endl;

   std::cout << "Ending.. " << std::endl << std::endl;

   return 0;
}

#include <stdio.h>
#include <iostream>
#include "hog_functions.h"
#include "trainedResults.h"

int main (void)
{
  //Loop
  int nImages = 470;
  char* imageName = (char*)malloc(256);
  //Image sizes
  int widthMono = 128;
  int heightMono = 96;
  int widthStereo = 256;
  int heightStereo = 96;
  int templateW = 24;
  int templateH = 28;
  //Tracker parameters
  int padding = 2;
  int cellSide = 2;
  int nBins = 4;
  //Detection parameters
  int wRoi;
  int hRoi;
  int xRoi;
  int yRoi;
  int xant = 0;
  int yant = 0;
  int xdetCenter = 0;
  int ydetCenter = 0;
  int xdetGlobalCenter = 0;
  int ydetGlobalCenter = 0;
  //Memory occupancy
  ROIsize(&wRoi,&hRoi);//72+2*50+2
  uint8_t *imageStereoFormat;
  uint8_t imageMono[widthMono*heightMono];
  uint8_t imageRoi[wRoi*hRoi];
  float hogVector[nBins*(wRoi-2)*(hRoi-2)/(cellSide*cellSide)];
  float theta[templateW*templateH*nBins/(cellSide*cellSide) + 1];
  loadTheta(theta);

  //Main
  for (int i = 415;i <= nImages;i++) {
    sprintf(imageName,"images/imageBoth%d.png",i);
    printf("%s\n",imageName);
    //Read image from database and convert it to the same format as in the stereoboard
    imageStereoFormat = image2stereoFormat(imageName,widthStereo,heightStereo);
    //Show full stereo image
    // showImage(imageStereoFormat,widthStereo,heightStereo,true);
    //Adaptative size of the Roi:not implemented
    ROIsize(&wRoi,&hRoi);
    //Location of the roi image in the full image
    ROIcorner(&xRoi,&yRoi,wRoi,hRoi,xdetCenter,ydetCenter,widthMono,heightMono);
    //Copy image to work with from now on
    imageROIcopy(imageStereoFormat,imageRoi,xRoi,yRoi,wRoi,hRoi,widthStereo);
    calculateHOGvector(imageRoi,hogVector,wRoi,hRoi,cellSide,nBins);
    //Detection functions
    detect(hogVector,theta,&xdetCenter,&ydetCenter,&xant,&yant,wRoi,hRoi,templateW,templateH,cellSide,nBins);
    //Get global coordinates
    coordinatesGlobal(&xdetGlobalCenter,&ydetGlobalCenter,xdetCenter,ydetCenter,xRoi,yRoi);
    //Mono image from stereo image
    stereo2mono(imageMono,imageStereoFormat,widthMono,heightMono,widthStereo);
    // Draw mono detection
    squareDraw(imageMono,widthMono,heightMono,xdetGlobalCenter,ydetGlobalCenter,templateW,templateH);
    //Show mono image with detection
    showImage(imageMono,widthMono,heightMono,true);
    //Draw roi detection
    squareDraw(imageRoi,wRoi,hRoi,xdetCenter,ydetCenter,templateW,templateH);
    //Show roi image with detection
    // showImage(imageRoi,wRoi,hRoi,true);
    //Delete image name
    imageName[0] = '\0';
  }
  return 0;
}

#ifndef HOG_POCKET_H
#define HOG_POCKET_H

#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

uint8_t* image2stereoFormat(char* imageName,int widthStereo,int heightStereo);
void stereo2mono(uint8_t* imageMono,uint8_t* imageStereoFormat,int widthMono,int heightMono,int widthStereo);
void showImage(uint8_t* imageStereoFormat,int widthStereo,int heightStereo,bool wait);
void loadTheta(float* theta);
void ROIsize(int* wRoi,int* hRoi);
void ROIcorner(int* xRoi,int* yRoi,int wRoi,int hRoi,int xdetCenter,int ydetCenter,int widthMono,int heightMono);
void imageROIcopy(uint8_t* imageStereoFormat,uint8_t* imageRoi,int xRoi,int yRoi,int wRoi,int hRoi,int widthStereo);
void calculateCellGradients(uint8_t* imageRoi,float* tempGrad,int wRoi,int hRoi,int xInRoi,int yInRoi,int cellSide);
void calculateCellBins(float* tempGrad,float* tempBin,uint8_t nBins);
void calculateHOGcell(uint8_t* imageRoi,float* tempGrad,float* tempBin,int wRoi,int hRoi,int cellSide,int nBins,int xInRoi,int yInRoi);
void calculateHOGvector(uint8_t* imageRoi,float* hogVector,int wRoi,int hRoi,int cellSide,int nBins);
void detectProto(float* hogVector,float* theta,int* xdetCenter,int* ydetCenter,int wRoi,int hRoi,int templateW,int templateH,int cellSide,int nBins);
void detect(float* hogVector,float* theta,int* xdetCenter,int* ydetCenter,int* xant,int* yant,int wRoi,int hRoi,int templateW,int templateH,int cellSide,int nBins);
float hogScore(float* StereoHog,float* theta,int size);
void coordinatesGlobal(int* xdetGlobalCenter,int* ydetGlobalCenter,int xdetCenter,int ydetCenter,int xRoi,int yRoi);
void squareDraw(uint8_t* imageRoi,int wRoi,int hRoi,int xdetCenter,int ydetCenter,int templateW,int templateH);

#endif

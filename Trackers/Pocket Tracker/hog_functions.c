#include "hog_functions.h"
#include "trainedResults.h"

uint8_t* image2stereoFormat(char* imageName,int widthStereo,int heightStereo)
{
  cv::Mat imageCV;
  uint8_t *imageStereoFormat;

  imageCV = cv::imread(imageName, CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

  if(! imageCV.data )                              // Check for invalid input
  {
    std::cout <<  "Could not open or find the image" << std::endl ;
    exit(-1);
  }

  imageStereoFormat = (uint8_t*)malloc(widthStereo*heightStereo*sizeof(uint8_t));

  for (int y = 0; y < heightStereo; y++) {
    for (int x = 0; x < widthStereo; x++) {
      imageStereoFormat[y*widthStereo+x] = imageCV.data[y*widthStereo+x];
    }
  }
  return imageStereoFormat;
}

void stereo2mono(uint8_t* imageMono,uint8_t* imageStereoFormat,int widthMono,int heightMono,int widthStereo)
{
  for (uint8_t y = 0; y < heightMono; y++) {
    for (uint8_t x = 0; x < widthMono; x++) {
      imageMono[y*widthMono+x] = imageStereoFormat[y*widthStereo + x*2];//image Left
      // imageMono[y*widthMono+x] = imageStereoFormat[y*widthStereo + x*2 + 1];//image Right
    }
  }
  return;
}

void showImage(uint8_t* imageStereoFormat,int widthStereo,int heightStereo,bool wait)
{

  cv::Mat imageCV(heightStereo,widthStereo,CV_8UC1,255);

  imageCV.data = imageStereoFormat;

  cv::namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Display window", imageCV );

  if (wait) {
    cv::waitKey(0);
  }
}

void loadTheta(float* theta)
{
  loadD(theta);
  return;
}

void ROIsize(int* wRoi,int* hRoi)
{
  *wRoi = 92 + 2;
  *hRoi = 70 + 2;
  return;
}

void ROIcorner(int* xRoi,int* yRoi,int wRoi,int hRoi,int xdetCenter,int ydetCenter,int widthMono,int heightMono)
{
  //If first time center the roi in the frame
  if (xdetCenter == 0 && ydetCenter == 0) {
    *xRoi = (widthMono - wRoi) / 2;
    *yRoi = (heightMono - hRoi) / 2;
    return;
  }
  //else, maintaining it inside the image
  *xRoi = xdetCenter - wRoi / 2;
  *yRoi = ydetCenter - hRoi / 2;
  if (*xRoi > widthMono - wRoi) {
    *xRoi = widthMono - wRoi;
  }
  if (*xRoi < 1) {
    *xRoi = 1;
  }
  if (*yRoi > heightMono - hRoi) {
    *yRoi = heightMono - hRoi;
  }
  if (*yRoi < 1) {
    *yRoi = 1;
  }
  return;
}

void imageROIcopy(uint8_t* imageStereoFormat,uint8_t* imageRoi,int xRoi,int yRoi,int wRoi,int hRoi,int widthStereo)
{
  for (uint8_t y = 0; y < hRoi; y++) {
    for (uint8_t x = 0; x < wRoi; x++) {
      imageRoi[y*wRoi+x] = imageStereoFormat[(yRoi-1+y)*widthStereo + (xRoi-1)*2 + 2*x];
    }
  }
  return;
}

void calculateCellGradients(uint8_t* imageRoi,float* tempGrad,int wRoi,int hRoi,int xInRoi,int yInRoi,int cellSide)
{
  for (uint8_t y = 0; y < 2; y++) {
    for (uint8_t x = 0; x < 2; x++) {
      tempGrad[x*2+y*4] = imageRoi[(yInRoi+y-1)*wRoi+xInRoi+x+1] - imageRoi[(yInRoi+y-1)*wRoi+xInRoi+x-1];// x
      tempGrad[x*2+y*4+1] = imageRoi[(yInRoi+y)*wRoi+xInRoi+x] - imageRoi[(yInRoi+y-2)*wRoi+xInRoi+x];// y
    }
  }
  return;
}

void calculateCellBins(float* tempGrad,float* tempBin,uint8_t nBins)
{
  //Without normalization
  for (uint8_t i = 0; i < 4; i++) {
    //Calculate angle
    float binStep = 180 / nBins;
    float binHalfStep = binStep/2;
    float angle = atan2f(tempGrad[i*2+1],tempGrad[i*2]);
    float angleDeg = angle*(180.0/3.1415926);
    float vote = sqrt(tempGrad[i*2+1]*tempGrad[i*2+1]+tempGrad[i*2]*tempGrad[i*2]);

    if(angleDeg<0){
      angleDeg+=180;
    }

    //Split into the two closest bins
    for (uint8_t j = 0; j < nBins; j++){
      if (angleDeg < binStep*j + binHalfStep) {
        int nextBin = binStep*j + binHalfStep;
        int prevBin = binStep*(j-1) + binHalfStep;
        if (j < nBins-1) {
          tempBin[j] += vote*(angleDeg - prevBin)/binStep;
          //Lower than 10 deg
          if (prevBin < 0) {
            tempBin[nBins-1] += vote*(nextBin - angleDeg)/binStep;
            break;
          }
          tempBin[j-1] += vote*(nextBin - angleDeg)/binStep;
          break;
        }
        //Higher than 170 deg
        tempBin[0] += vote*(angleDeg - (nBins-1)*binStep)/binStep;
        tempBin[nBins-1] += vote*(binHalfStep+nBins*binStep - angleDeg)/binStep;
        break;
      }
    }
  }
  return;
}

void calculateHOGcell(uint8_t* imageRoi,float* tempGrad,float* tempBin,int wRoi,int hRoi,int cellSide,int nBins,int xInRoi,int yInRoi)
{
  calculateCellGradients(imageRoi,tempGrad,wRoi,hRoi,xInRoi,yInRoi,cellSide);
  calculateCellBins(tempGrad,tempBin,nBins);
  return;
}

void calculateHOGvector(uint8_t* imageRoi,float* hogVector,int wRoi,int hRoi,int cellSide,int nBins)
{
  float tempGrad[cellSide*cellSide*2];
  float tempBin[nBins];
  int nCells = 0;

  for (uint8_t yInRoi = 2; yInRoi < hRoi; yInRoi = yInRoi + 2) {
    for (uint8_t xInRoi = 2; xInRoi < wRoi; xInRoi = xInRoi + 2) {
      calculateHOGcell(imageRoi,tempGrad,tempBin,wRoi,hRoi,cellSide,nBins,xInRoi,yInRoi);
      for (size_t i = 0; i < nBins; i++) {
        hogVector[nCells*nBins+i] = tempBin[i];
      }
      for (uint8_t i = 0; i < nBins; i++) {
        tempBin[i] = 0;
      }
      nCells += 1;
    }
  }
  return;
}

void detectProto(float* hogVector,float* theta,int* xdetCenter,int* ydetCenter,int wRoi,int hRoi,int templateW,int templateH,int cellSide,int nBins)
{
  uint8_t cellsX;
  uint8_t cellsY;
  uint8_t templateXcells;
  uint8_t templateYcells;
  uint8_t xMax = 0;
  uint8_t yMax = 0;

  int counter = 0;
  float score = -1;
  float scoreMax = -1;

  cellsX = wRoi / cellSide;
  cellsY = hRoi / cellSide;
  templateXcells = templateW / cellSide;
  templateYcells = templateH / cellSide;

  int size = templateXcells*templateYcells*nBins + 1;
  float StereoHogTemp[size];
  StereoHogTemp[0] = 1;

  for (uint8_t r = 1;r <= cellsY - (templateYcells - 1);r++) { //y
    for (uint8_t s = 1;s <= cellsX - (templateXcells - 1);s++) { //x
      counter = 0;
      for (uint8_t i = 1;i <= templateYcells;i++) {
        for (uint8_t j = 1;j <= templateXcells;j++) {
          for (uint8_t b = 0;b <= nBins-1;b++) {
            StereoHogTemp[1 + counter*nBins + b] = hogVector[(r+i-2)*cellsX*nBins + (s+j-2)*nBins + b];
          }
          counter++;
        }
      }
      score = hogScore(StereoHogTemp,theta,size);
      if (score > scoreMax) {
        xMax = r;
        yMax = s;
        scoreMax = score;
      }
    }
  }
  *xdetCenter = xMax + templateW / 2;
  *ydetCenter = yMax + templateH / 2;
  return;
}

void detect(float* hogVector,float* theta,int* xdetCenter,int* ydetCenter,int* xant,int* yant,int wRoi,int hRoi,int templateW,int templateH,int cellSide,int nBins)
{
  int imageHeight = hRoi;
  int imageWidth = wRoi;
  int windowWidth = 24;
  int windowHeight = 28;

  int windowControl = 0;
  int counter;
  int imageXcells = (imageWidth-2)/cellSide;
  int templateXcells = templateW / cellSide;
  int templateYcells = templateH / cellSide;

  int xMax = 0;
  int yMax = 0;

  float score = -10000;
  float scoreMax = -10000;

  int size = templateXcells*templateYcells*nBins + 1;
  float StereoHogTemp[size];
  StereoHogTemp[0] = 1;

  for (uint8_t y = 2;y <= imageHeight - windowHeight;y = y+2) { //y
    for (uint8_t x = 2;x <= imageWidth - windowWidth;x = x+2) { //x
      windowControl++;
      counter = 0;
      for (uint8_t iy = 1;iy <= 28;iy = iy+2) {
        for (uint8_t ix = 1;ix <= 24;ix = ix+2) {

          for (uint8_t b = 0;b <= nBins-1;b++) {
            StereoHogTemp[1 + counter*nBins + b] = hogVector[((y-2+iy-2+1)/2)*nBins*imageXcells+((x-2+ix-2+1)/2)*nBins+b];
          }

          counter++;
        }
      }

      //Score with hog
      score = hogScore(StereoHogTemp,theta,size);
      //Distance hog + penalty
      // score += scoreDist(x,y,xant,yant);

      if (score > scoreMax) {
        xMax = x;
        yMax = y;
        scoreMax = score;
      }
    }
  }

  *xant = xMax;
  *yant = yMax;
  *xdetCenter = xMax + templateW / 2;
  *ydetCenter = yMax + templateH / 2;
  return;
}

void detectBlocks(float* hogVector,float* theta,int* xdetCenter,int* ydetCenter,int wRoi,int hRoi,int templateW,int templateH,int cellSide,int nBins)
{
  uint8_t cellsX;
  uint8_t cellsY;
  uint8_t templateXcells;
  uint8_t templateYcells;
  uint8_t xMax = 0;
  uint8_t yMax = 0;

  int counter = 0;
  float score = -1;
  float scoreMax = -1;

  cellsX = wRoi / cellSide;
  cellsY = hRoi / cellSide;
  templateXcells = templateW / cellSide;
  templateYcells = templateH / cellSide;

  int size = templateXcells*templateYcells*nBins + 1;
  float StereoHogTemp[size];
  StereoHogTemp[0] = 1;

  for (uint8_t r = 1;r <= cellsY - (templateYcells - 1);r++) { //y
    for (uint8_t s = 1;s <= cellsX - (templateXcells - 1);s++) { //x
      counter = 0;
      for (uint8_t i = 1;i <= templateYcells;i++) {
        for (uint8_t j = 1;j <= templateXcells;j++) {
          for (uint8_t b = 0;b <= 8;b++) {
            StereoHogTemp[1 + counter*nBins + b] = hogVector[(r+i-2)*cellsX*nBins + (s+j-2)*nBins + b];
          }
          counter++;
        }
      }
      score = hogScore(StereoHogTemp,theta,size);
      if (score > scoreMax) {
        xMax = r;
        yMax = s;
        scoreMax = score;
      }
    }
  }
  *xdetCenter = xMax + templateW / 2;
  *ydetCenter = yMax + templateH / 2;
  return;
}

float hogScore(float* StereoHog,float* theta,int size)
{
  float score = 0;

  for (int i = 0;i < size;i++) {
    score += StereoHog[i]*theta[i];
  }
  return score;
}

//float scoreDist(int x,int y,int xant,int yant)
//{
//  float Pen = 0;
//  if (xant + yant == 0)
//  {
//    return 0;
//  }
//  float scorePen = -Pen*sqrtf(x-xant,y-yant);
//  return scorePen
//}

void coordinatesGlobal(int* xdetGlobalCenter,int* ydetGlobalCenter,int xdetCenter,int ydetCenter,int xRoi,int yRoi)
{
  *xdetGlobalCenter = xdetCenter + xRoi;
  *ydetGlobalCenter = ydetCenter + yRoi;
  return;
}

void squareDraw(uint8_t* image,int imageWidth,int imageHeight,int xdetCenter,int ydetCenter,int templateW,int templateH)
{
  for (int y = 0; y < imageHeight; y++) {
    for (int x = 0; x < imageWidth; x++) {
      if (y == ydetCenter - templateH/2 && x > xdetCenter - templateW/2 && x < xdetCenter + templateW/2 ||
          y == ydetCenter + templateH/2 && x > xdetCenter - templateW/2 && x < xdetCenter + templateW/2 ||
          x == xdetCenter - templateW/2 && y > ydetCenter - templateH/2 && y < ydetCenter + templateH/2 ||
          x == xdetCenter + templateW/2 && y > ydetCenter - templateH/2 && y < ydetCenter + templateH/2) {
        image[y*imageWidth+x] = 0;
      }
    }
  }
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "distance_calc.hpp"

#include "kcftracker.hpp"

#include <dirent.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){

	if (argc > 5) return -1;

	bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = false;
	bool LAB = false;

	for(int i = 0; i < argc; i++){
		if ( strcmp (argv[i], "hog") == 0 )
		HOG = true;
		if ( strcmp (argv[i], "fixed_window") == 0 )
		FIXEDWINDOW = true;
		if ( strcmp (argv[i], "singlescale") == 0 )
		MULTISCALE = false;
		if ( strcmp (argv[i], "show") == 0 )
		SILENT = false;
		if ( strcmp (argv[i], "lab") == 0 ){
			LAB = true;
			HOG = true;
		}
		if ( strcmp (argv[i], "gray") == 0 )
		HOG = false;
	}

	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);
	Mat frame;
	Rect result;

	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened())  // check if opened
	return -1;
	//INITIAL BOX
	float xMin = 230;
	float yMin = 100;
	float width = 150;
	float height = 200;

	int isInit = 0;
	int key = -1;

	while (1){
		cap >> frame;
		double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
		//INIT
		if (isInit == 0) {
			rectangle(frame,Point(xMin,yMin),Point(xMin+width,yMin+height),Scalar(0,255,255),1,8);
			imshow("Image", frame);
			key = waitKey(1);
			while (key == -1)
			{
				cap >> frame;
				rectangle(frame,Point(xMin,yMin),Point(xMin+width,yMin+height),Scalar(0,255,255),1,8);
				imshow("Image", frame);
				key = waitKey(1);
			}
			tracker.init(Rect(xMin,yMin,width,height),frame);
			isInit = 1;
		}
		//UPDATE
		else{
			result = tracker.update(frame);
			distance_calc(result.height);
			printf("distancia relativa = %f\n",horizontal_displacement);
			rectangle(frame,Point(result.x,result.y),Point(result.x+result.width,result.y+result.height),Scalar(0,255,255),1,8);
		}
		if (!SILENT){
			imshow("Image",frame);
			waitKey(1);
		}
	}
}

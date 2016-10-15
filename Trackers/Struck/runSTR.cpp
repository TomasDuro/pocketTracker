/*
* Struck: Structured Output Tracking with Kernels
*
* Code to accompany the paper:
*   Struck: Structured Output Tracking with Kernels
*   Sam Hare, Amir Saffari, Philip H. S. Torr
*   International Conference on Computer Vision (ICCV), 2011
*
* Copyright (C) 2011 Sam Hare, Oxford Brookes University, Oxford, UK
*
* This file is part of Struck.
*
* Struck is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Struck is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Struck.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "Tracker.h"
#include "Config.h"

#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

static const int kLiveBoxWidth = 80;
static const int kLiveBoxHeight = 80;

void rectangle(Mat& rMat, const FloatRect& rRect, const Scalar& rColour)
{
	IntRect r(rRect);
	rectangle(rMat, Point(r.XMin(), r.YMin()), Point(r.XMax(), r.YMax()), rColour);
}

int main(void)
{
	int isFirstTime = 1;
	string configPath;
	Config conf;
	bool useCamera;
	FloatRect initBB;
	Mat result;
	Mat frameOrig;
	VideoCapture cap;
	Mat frame;
	int isInit = 0;
	int key = -1;
	// read config file
	if (isFirstTime)
	{
		configPath = "config.txt";
		conf = configPath;
		cout << conf << endl;
		if (conf.features.size() == 0)
		{
			cout << "error: no features specified in config" << endl;
			return EXIT_FAILURE;
		}
		// if no sequence specified then use the camera
		useCamera = (conf.sequenceName == "");
		if (useCamera)
		{
			if(!cap.open(0))
			{
				cout << "error: could not start camera capture" << endl;
				return EXIT_FAILURE;
			}
			initBB = IntRect(conf.frameWidth/2-kLiveBoxWidth/2,conf.frameHeight/2-kLiveBoxHeight/2,kLiveBoxWidth,kLiveBoxHeight);
			cout << "press any key to initialise tracker" << endl;
		}
		result = Mat(conf.frameHeight, conf.frameWidth, CV_8UC3);
		isFirstTime = 0;
	}
	Tracker tracker(conf);
	namedWindow("result");
	srand(conf.seed);
	while (1){
		cap >> frameOrig;
		resize(frameOrig,frame,Size(conf.frameWidth,conf.frameHeight));
		flip(frame,frame,1);
		frame.copyTo(result);
		//INIT
		if (isInit == 0) {
			rectangle(result,Point(initBB.XMin(),initBB.YMin()),Point(initBB.XMin()+initBB.Width(),initBB.YMin()+initBB.Height()),Scalar(0,255,255),1,8);
			imshow("result",result);
			key = waitKey(1);
			while (key == -1)
			{
				cap >> frameOrig;
				resize(frameOrig,frame,Size(conf.frameWidth,conf.frameHeight));
				flip(frame,frame,1);
				frame.copyTo(result);
				rectangle(result,Point(initBB.XMin(),initBB.YMin()),Point(initBB.XMin()+initBB.Width(),initBB.YMin()+initBB.Height()),Scalar(0,255,255),1,8);
				imshow("result",result);
				key = waitKey(1);
			}
			tracker.Initialise(frame,initBB);
			isInit = 1;
		}
		//UPDATE
		else{
			tracker.Track(frame);
			rectangle(result,tracker.GetBB(),CV_RGB(0,255,0));
			imshow("result",result);
			waitKey(1);
		}
	}
	return EXIT_SUCCESS;
}

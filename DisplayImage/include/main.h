/*
 * main.h
 *
 *  Created on: Sep 27, 2015
 *      Author: t1audrai
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>



using namespace std;
using namespace cv;

void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold);



#endif /* MAIN_H_ */

//
//  AlgebraicOperationsClass.hpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 5/3/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#ifndef AlgebraicOperationsClass_hpp
#define AlgebraicOperationsClass_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


bool addImages(Mat &img1, Mat &img2, Mat &dst);
Mat recursiveAveragingHelper(Mat&src,Mat&dst,int constant,int iterations);
bool recursiveAveraging(Mat&src,Mat&dst,int constant,int iterations);
bool subtractImages(Mat &img1, Mat &img2, Mat &dst);
bool leesAlgorithm(Mat &src, Mat&dst,int constantVal,int kernel);
bool modifiedLeesAlgorithm(Mat &src, Mat&dst,int beta,int alpha,int eta,int kernel);

#endif /* AlgebraicOperationsClass_hpp */

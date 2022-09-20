//
//  AlgebraicOperationsClass.cpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 5/3/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#include "AlgebraicOperationsClass.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


bool addImages(Mat &img1, Mat &img2, Mat &dst){
    
    int imgRows,imgCols,sum;
    
    if(img1.empty()||img2.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    if(img1.size()!=img2.size()){
        cout<<"Input images must be the same size!";
        return false;
    }
    
    imgRows = img1.size().height;
    imgCols = img1.size().width;
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            sum=img1.at<uchar>(i,j)+img2.at<uchar>(i,j);
            if(sum>255){ sum=255;}
            else if(sum<0){ sum=0;}
            dst.at<uchar>(i,j)=(uchar)sum;
        }
    }
    
    return true;
}

bool subtractImages(Mat &img1, Mat &img2, Mat &dst){
    
    int imgRows,imgCols,difference;
    
    if(img1.empty()||img2.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    if(img1.size()!=img2.size()){
        cout<<"Input images must be the same size!";
        return false;
    }
    
    imgRows = img1.size().height;
    imgCols = img1.size().width;
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            difference=img1.at<uchar>(i,j)-img2.at<uchar>(i,j);
            if(difference<0){difference=0;}
            dst.at<uchar>(i,j)=(uchar)difference;
        }
    }
    
    return true;
}

Mat recursiveAveragingHelper(Mat&src,Mat&dst,int constant,int iterations){
    
    if(iterations<=1){
        return constant+(1-constant)*src;
    }
    else{
        return constant*recursiveAveragingHelper(dst, dst, constant, iterations-1)+constant*src;
    }

}

bool recursiveAveraging(Mat&src,Mat&dst,int constant,int iterations){
    
    int imgRows, imgCols;
    
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    imgRows = src.size().height;
    imgCols = src.size().width;
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    dst=recursiveAveragingHelper(src,dst,constant,iterations);
    
    return true;
}


bool leesAlgorithm(Mat &src, Mat&dst,int constantVal,int kernel){
    
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    int imgRows, imgCols;
    int mean = 0.0;
    int val;
    int final = 0;
    cv::Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    mean += img_temp.at<uchar>(i + x, j + y);
                }
            }
            
            mean = mean / (kernel * kernel);
            val=mean+(constantVal*(src.at<uchar>(i - padding, j - padding)-mean));
            final = round(val);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
        }
    
    
    
    }
    
    return true;
}


bool modifiedLeesAlgorithm(Mat &src, Mat&dst,int beta,int alpha,int eta,int kernel){
    
    //if beta>1, edges sharpened, if alpha>1 grey value stretched to high brightness area, otherwise to low intesity area. Eta adjusts dynamic range
    
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    int imgRows, imgCols;
    int mean = 0.0;
    int val;
    int final = 0;
    cv::Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    mean += img_temp.at<uchar>(i + x, j + y);
                }
            }
            
            mean = mean / (kernel * kernel);
            val=(alpha*mean)+eta+(beta*(src.at<uchar>(i - padding, j - padding)-mean));
            final = round(val);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
        }
        
        
        
    }
    
    return true;
}



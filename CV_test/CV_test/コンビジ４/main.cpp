#include <iostream>
#include <opencv2/opencv.hpp>
#include <random.h>
#include <stdio.h>
#include <time.h>

using namespace cv;

#include<math.h>
#include<string.h>


typedef unsigned char uint8_t;
using cv::imread;
using cv::imwrite;
using cv::Mat;


Mat sobel_Filter(Mat input) {
    
    if (input.data != NULL) {
      
        Mat filtered = input.clone();
        
        for (int x = 1; x < input.cols-1; ++x) {
            for (int y = 1; y < input.rows-1; ++y) {
                
                uint8_t I[3][3];
                for( int i = 0; i < 3; ++i ){
                    for( int j = 0; j < 3; ++j ){
                        I[i][j] = input.at<uint8_t>(y+i-1, x+j-1);
                    }
                }

                int temp1 = 0, temp2 = 0, out;
                
                temp1 = -1 * I[0][0] - 2 * I[1][0] - 1*I[2][0] + 1 * I[0][2] + 2 * I[1][2] + 1 * I[2][2]; //df/dx
                temp2 = -1 * I[0][2] - 2 * I[1][2] - 1*I[2][2] + 1 * I[0][0] + 2 * I[0][1] + 1 * I[0][2];//df/dy
                out = abs( temp1 + temp2 );//ΔF

                filtered.at<uint8_t>(y, x) = out;
            }
        }
        
         imshow("out",filtered);
        waitKey();
        return filtered;
    }
    
    else {
        std::cout<<"error"<<std::endl;
        return Mat();
        
    }
}

int main() {

    imwrite("output.png",sobel_Filter(imread("lena.jpg",cv::IMREAD_GRAYSCALE)));

    return 0;
}

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
   
    Mat src = cv::imread("test0.png",cv::IMREAD_GRAYSCALE);                    //入力画像
    
    imshow("input_gray", src);

    
    if(src.rows == 0){
        std::cout<<"nononono"<<std::endl;
        return  0;
    }
    
    //ラべリング処理
    cv::Mat LabelImg;
    cv::Mat stats;  //面積値？
    cv::Mat centroids; //重心
    int nLab = cv::connectedComponentsWithStats(src, LabelImg, stats, centroids);

    // ラベリング結果の描画色を決定
    std::vector<cv::Vec3b> colors(nLab);
    colors[0] = cv::Vec3b(0, 0, 0);
    for (int i = 1; i < nLab; ++i) {
        colors[i] = cv::Vec3b(255, 255, 255);
    }
    
    // ラベリング結果の描画
    cv::Mat dst(src.size(), CV_8UC3);
    for (int i = 0; i < dst.rows; ++i) {
        int *lb = LabelImg.ptr<int>(i);
        cv::Vec3b *pix = dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < dst.cols; ++j) {
            pix[j] = colors[lb[j]];
        }
    }

    std::cout<<"図形の数 ="<<nLab<<std::endl;

    //重心
    for (int i = 1; i < nLab; ++i) {
        double *param = centroids.ptr<double>(i);
        int x = static_cast<int>(param[0]);
        int y = static_cast<int>(param[1]);
        
        std::stringstream num;
        num << i;
        cv::putText(dst, num.str(), cv::Point(x, y), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0, 0, 255), 2);
        
        std::cout<<"図形"<<i<<"の重心 x="<<x<<" y="<<y<<std::endl;
        
    }

    
    cv::imshow("Labels", dst);
    
    cv::imwrite("result.png", dst);
    cv::waitKey();
    
    waitKey();

    return 0;
}






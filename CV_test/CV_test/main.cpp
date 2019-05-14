#include <iostream>
#include <opencv2/opencv.hpp>
#include <random.h>
#include <stdio.h>
#include <time.h>

using namespace cv;
int w = 500 ,h = 500;
cv::Mat Map(cv::Size(w, h), CV_8UC3, cv::Scalar(0,0,0));
int map[500][500];

int N = 1000;
int snowN = 10;
//マウス入力用のパラメータ
struct mouseParam {
    int x;
    int y;
    int event;
    int flags;
};

//コールバック関数
void CallBackFunc(int eventType, int x, int y, int flags, void* userdata)
{
    mouseParam *ptr = static_cast<mouseParam*> (userdata);
    
    ptr->x = x;
    ptr->y = y;
    ptr->event = eventType;
    ptr->flags = flags;
}


void snow(Mat *Map,int x,int y){
    
    int x_p,y_p;
    
   
    
    bool jack = true;
    
        
    
    for(int i=0;i<N;i++){
        
        x_p = x;
        y_p = y;
        srand((int)time(0));
        
        
        jack = true;
        
        while(jack){
            
            int r = rand() % 2;
            
            
            if(y_p!=0 && (map[y_p][x_p] > map[y_p-1][x_p]) ){
                y_p--;
                
            }
            
            else if(y_p!=0 &&x_p!= w-1 && (map[y_p][x_p] > map[y_p-1][x_p+1]) && r ==1){
                y_p--;
                x_p++;
                
            }
            
            else if(x_p!= w-1 && (map[y_p][x_p] > map[y_p][x_p+1]) ){
                x_p++;
                
            }
            
            else if(x_p!= w-1 &&y_p!= h-1 && (map[y_p][x_p] > map[y_p+1][x_p+1]) && r ==1){
                y_p++;
                x_p++;
            }
            
            
            else if(y_p!= h-1 && (map[y_p][x_p] > map[y_p+1][x_p]) ){
                y_p++;
                
            }
            
            else if(y_p!= h-1 &&x_p!=0 && (map[y_p][x_p] > map[y_p+1][x_p-1]) && r ==1 ){
                y_p++;
                x_p--;
                
            }
            
            
            else if(x_p!=0 && (map[y_p][x_p] > map[y_p][x_p-1]) ){
                x_p--;
                
            }
            
            else if(y_p!=0 && x_p!=0 && (map[y_p][x_p] > map[y_p-1][x_p-1]) && r ==1){
                x_p--;
                y_p--;
            }
            
            
            else {
                map[y_p][x_p] += snowN;
                
                if(map[y_p][x_p]<(255)){
                    int jack=(rand()%2);
                    Map->at<Vec3b>(y_p, x_p)[0] +=snowN * jack;// * (rand()%2);
                    Map->at<Vec3b>(y_p, x_p)[1] +=snowN * jack;//* (rand()%2);
                    Map->at<Vec3b>(y_p, x_p)[2] +=snowN * jack;// * (rand()%2);
                }
                jack = false;
            }
            
        
        }
    
    
    }
    
}




int main()
{
   
    
    mouseParam mouseEvent;
    

    int key;
    time_t t;
    
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            map[i][j]=0;
    
    while(1){
    
        
        cv::imshow("map", Map);
        t = time(NULL);
        
        //コールバックの設定
        cv::setMouseCallback("map", CallBackFunc, &mouseEvent);
        
        key=cv::waitKey(5);
        
        if(key==27){
            
            printf("%s", ctime(&t));
            
            std::string name = "map";
            
            name+=ctime(&t);
            name+=".png";
            cv::imwrite(name,Map);
            
            break;
            
        }
        else if(key==114){
            
            printf("R");
            
            Mat zero(cv::Size(w, h), CV_8UC3, cv::Scalar(0,0,0));
            Map=zero;
            
            for(int i=0;i<h;i++)
                for(int j=0;j<w;j++)
                    map[i][j]=0;
            
        }
        
            //左クリックがあったら表示
            if (mouseEvent.event == cv::EVENT_LBUTTONDOWN) {
                //クリック後のマウスの座標を出力
                std::cout << mouseEvent.x << " , " << mouseEvent.y << std::endl;

                snow(&Map,mouseEvent.x,mouseEvent.y);
                
                
        
            }
    
        //snow(&Map,250,250);
    
    
    }

    return 0;
}






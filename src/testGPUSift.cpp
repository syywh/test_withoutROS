// SiftGPU模块
#include <SiftGPU.h>

//标准C++
#include <iostream>
#include <vector>

// OpenCV图像
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// boost库中计时函数
#include <boost/timer.hpp>

// OpenGL
#include <GL/gl.h>

using namespace std;

int main( int argc, char** argv)
{
    //声明SiftGPU并初始化
    SiftGPU sift;
    char* myargv[4] ={ "-fo", "-1", "-v", "1"};
    sift.ParseParam(4, myargv);

    //检查硬件是否支持SiftGPU
    int support = sift.CreateContextGL();
    if ( support != SiftGPU::SIFTGPU_FULL_SUPPORTED )
    {
        cerr<<"SiftGPU is not supported!"<<endl;
        return 2;
    }

    //测试直接读取一张图像
    cout<<"running sift"<<endl;
    boost::timer timer;
    //在此填入你想测试的图像的路径！不要用我的路径！不要用我的路径！不要用我的路径！
    sift.RunSIFT( "/home/dxq/code_ws/tests/data/test.png" );
    cout<<"siftgpu::runsift() cost time="<<timer.elapsed()<<endl;
    
    // 获取关键点与描述子
    int num = sift.GetFeatureNum();
    cout<<"Feature number="<<num<<endl;
    vector<float> descriptors(128*num);
    vector<SiftGPU::SiftKeypoint> keys(num);
    timer.restart();
    sift.GetFeatureVector(&keys[0], &descriptors[0]);
    cout<<"siftgpu::getFeatureVector() cost time="<<timer.elapsed()<<endl;

    // 先用OpenCV读取一个图像，然后调用SiftGPU提取特征
    cv::Mat img = cv::imread("/home/xiang/wallE-slam/data/rgb1.png", 0);
    int width = img.cols;
    int height = img.rows;
    timer.restart();
    // 注意我们处理的是灰度图，故照如下设置
    sift.RunSIFT(width, height, img.data, GL_INTENSITY8, GL_UNSIGNED_BYTE);
    cout<<"siftgpu::runSIFT() cost time="<<timer.elapsed()<<endl;

    return 0;
}
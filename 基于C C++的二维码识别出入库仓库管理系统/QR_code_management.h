#pragma once

#include "Base.h"
#include <opencv2/opencv.hpp>




// 将QR码缓冲区转换为OpenCV图像
//接受保存数据和保存的文件名字
void createQRCodeImage(const char* data, string outputPath);

//整合了上面的几个做成接口来使用
string GetQRFromImage(const std::string& filename);

//也是识别接口，不过准确率不高，只用了zbar库里的接口，没有算法优化
string recognizeQRCode(const std::string& imageFilename);


//zbar接口
string ZbarDecoder(cv::Mat img);

//对二值图像进行识别，如果失败则开运算进行二次识别
string GetQRInBinImg(cv::Mat binImg);

//main function
string GetQR(cv::Mat img);

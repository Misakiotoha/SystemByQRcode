/*
核心功能
基于OpenCV+QRcodegen+Zbar
实现了通过识别二维码来得到物品信息的功能
以及为某一个物品生成二维码
预留了很多接口给其他函数调用
*/
#include "Base.h"
#include <zbar.h>
#include <opencv2/opencv.hpp>
#include "qrcodegen.h"
#include <windows.h>
#include <locale>
#include <codecvt>


using namespace zbar;
/*
    识别部分
*/


/*
下面的识别精度在99%
来自https://www.cnblogs.com/skyrudy/p/4955641.html
提供整合接口
*/
//zbar接口
string ZbarDecoder(cv::Mat img)
{
    string result;
    ImageScanner scanner;
    const void* raw = (&img)->data;
    // configure the reader
    scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);
    // wrap image data
    Image image(img.cols, img.rows, "Y800", raw, img.cols * img.rows);
    // scan the image for barcodes
    int n = scanner.scan(image);
    // extract results
    result = image.symbol_begin()->get_data();
    image.set_data(NULL, 0);
    return result;
}

//对二值图像进行识别，如果失败则开运算进行二次识别
string GetQRInBinImg(cv::Mat binImg)
{
    string result = ZbarDecoder(binImg);
    if (result.empty())
    {
        cv::Mat openImg;
        cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        morphologyEx(binImg, openImg, cv::MORPH_OPEN, element);
        result = ZbarDecoder(openImg);
    }
    return result;
}

//主
string GetQR(cv::Mat img)
{
    cv::Mat binImg;
    //在otsu二值结果的基础上，不断增加阈值，用于识别模糊图像
    int thre = threshold(img, binImg, 0, 255, cv::THRESH_OTSU);
    string result;
    while (result.empty() && thre < 255)
    {
        threshold(img, binImg, thre, 255, cv::THRESH_BINARY);
        result = GetQRInBinImg(binImg);
        thre += 20;//阈值步长设为20，步长越大，识别率越低，速度越快
    }
    return result;
}

//整合了上面的几个做成接口来使用
string GetQRFromImage(const string& filename) 
{

    //处理异常，如果图片名字为空
    if (filename == "") {
        exit(1);

    }
    // 读取图像文件
    cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        return "Error: Unable to open or find the image file.";
    }
    
    // 调用已有的GetQR函数来识别二维码
    std::string res = GetQR(img);
    

    return res;
}

/*
下面的识别精度在90%
*/
string recognizeQRCode(const string& imageFilename) 
{
    //处理异常，如果图片名字为空
    if (imageFilename == "") {
        exit(1);

    }
    // 1. 读取图像  
    cv::Mat image = cv::imread(imageFilename, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        throw std::runtime_error("无法读取图像文件");
    }
    
    // 2. 初始化ZBar图像扫描器  
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    // 3. 转换OpenCV图像到ZBar图像  
    int width = image.cols;
    int height = image.rows;
    unsigned char* raw = new unsigned char[width * height];
    for (int y = 0; y < height; ++y) {
        memcpy(raw + y * width, image.ptr<uchar>(y), width * sizeof(uchar));
    }
    zbar::Image zbarImage(width, height, "Y800", raw, width * height);

    // 4. 扫描二维码  
    scanner.scan(zbarImage);

    // 5. 处理识别结果  
    std::string qrCodeData;
    for (zbar::Image::SymbolIterator symbol = zbarImage.symbol_begin();
        symbol != zbarImage.symbol_end(); ++symbol) {
        // 获取二维码数据  
        string data = symbol->get_data();
        qrCodeData = data;
        break; // 只关心第一个二维码  
    }

    // 6. 清理资源  
    delete[] raw;

    // 7. 返回识别结果  
    return qrCodeData;
}



/************************************分割线***************************************/




/*
生成部分
*/

// 将string字符串转换为二维码图片

void createQRCodeImage(const char* data, string outputPath) 
{  
    // QR码缓冲区  
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];  
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];  
  
    // 编码文本到QR码
    bool ok = qrcodegen_encodeText(data, tempBuffer, qrcode, qrcodegen_Ecc_MEDIUM,  
                                     qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX,  
                                     qrcodegen_Mask_AUTO, true);  
    
    if (!ok) {  
        fprintf(stderr, "Error: QR code encoding failed\n");  
        return;  
    }  
  
    // 获取QR码的尺寸  
    int size = qrcodegen_getSize(qrcode);  
  
    // 二维码缩放比例  
    int scale = 4;  
  
    // 创建OpenCV图像以存储二维码，初始化为白色背景  
    int imgWidth = size * scale;  
    cv::Mat image = cv::Mat::ones(imgWidth, imgWidth, CV_8UC3) * 255; // 白色背景  
  
    // 绘制二维码的黑色模块  
    for (int y = 0; y < size; y++) {  
        for (int x = 0; x < size; x++) {  
            if (qrcodegen_getModule(qrcode, x, y)) {  
                // 在白色背景上绘制黑色的模块  
                cv::Rect rect(x * scale, y * scale, scale, scale);  
                image(rect) = cv::Scalar(0, 0, 0); // 黑色  
            }  
        }  
    }  
  
    // 保存二维码图像到文件  
    cv::imwrite(outputPath, image);  
  
    //printf("QR code image saved as %s\n", outputPath);  
}  
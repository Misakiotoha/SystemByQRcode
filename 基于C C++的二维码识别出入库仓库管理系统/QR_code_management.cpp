/*
���Ĺ���
����OpenCV+QRcodegen+Zbar
ʵ����ͨ��ʶ���ά�����õ���Ʒ��Ϣ�Ĺ���
�Լ�Ϊĳһ����Ʒ���ɶ�ά��
Ԥ���˺ܶ�ӿڸ�������������
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
    ʶ�𲿷�
*/


/*
�����ʶ�𾫶���99%
����https://www.cnblogs.com/skyrudy/p/4955641.html
�ṩ���Ͻӿ�
*/
//zbar�ӿ�
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

//�Զ�ֵͼ�����ʶ�����ʧ����������ж���ʶ��
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

//��
string GetQR(cv::Mat img)
{
    cv::Mat binImg;
    //��otsu��ֵ����Ļ����ϣ�����������ֵ������ʶ��ģ��ͼ��
    int thre = threshold(img, binImg, 0, 255, cv::THRESH_OTSU);
    string result;
    while (result.empty() && thre < 255)
    {
        threshold(img, binImg, thre, 255, cv::THRESH_BINARY);
        result = GetQRInBinImg(binImg);
        thre += 20;//��ֵ������Ϊ20������Խ��ʶ����Խ�ͣ��ٶ�Խ��
    }
    return result;
}

//����������ļ������ɽӿ���ʹ��
string GetQRFromImage(const string& filename) 
{

    //�����쳣�����ͼƬ����Ϊ��
    if (filename == "") {
        exit(1);

    }
    // ��ȡͼ���ļ�
    cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        return "Error: Unable to open or find the image file.";
    }
    
    // �������е�GetQR������ʶ���ά��
    std::string res = GetQR(img);
    

    return res;
}

/*
�����ʶ�𾫶���90%
*/
string recognizeQRCode(const string& imageFilename) 
{
    //�����쳣�����ͼƬ����Ϊ��
    if (imageFilename == "") {
        exit(1);

    }
    // 1. ��ȡͼ��  
    cv::Mat image = cv::imread(imageFilename, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        throw std::runtime_error("�޷���ȡͼ���ļ�");
    }
    
    // 2. ��ʼ��ZBarͼ��ɨ����  
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    // 3. ת��OpenCVͼ��ZBarͼ��  
    int width = image.cols;
    int height = image.rows;
    unsigned char* raw = new unsigned char[width * height];
    for (int y = 0; y < height; ++y) {
        memcpy(raw + y * width, image.ptr<uchar>(y), width * sizeof(uchar));
    }
    zbar::Image zbarImage(width, height, "Y800", raw, width * height);

    // 4. ɨ���ά��  
    scanner.scan(zbarImage);

    // 5. ����ʶ����  
    std::string qrCodeData;
    for (zbar::Image::SymbolIterator symbol = zbarImage.symbol_begin();
        symbol != zbarImage.symbol_end(); ++symbol) {
        // ��ȡ��ά������  
        string data = symbol->get_data();
        qrCodeData = data;
        break; // ֻ���ĵ�һ����ά��  
    }

    // 6. ������Դ  
    delete[] raw;

    // 7. ����ʶ����  
    return qrCodeData;
}



/************************************�ָ���***************************************/




/*
���ɲ���
*/

// ��string�ַ���ת��Ϊ��ά��ͼƬ

void createQRCodeImage(const char* data, string outputPath) 
{  
    // QR�뻺����  
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];  
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];  
  
    // �����ı���QR��
    bool ok = qrcodegen_encodeText(data, tempBuffer, qrcode, qrcodegen_Ecc_MEDIUM,  
                                     qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX,  
                                     qrcodegen_Mask_AUTO, true);  
    
    if (!ok) {  
        fprintf(stderr, "Error: QR code encoding failed\n");  
        return;  
    }  
  
    // ��ȡQR��ĳߴ�  
    int size = qrcodegen_getSize(qrcode);  
  
    // ��ά�����ű���  
    int scale = 4;  
  
    // ����OpenCVͼ���Դ洢��ά�룬��ʼ��Ϊ��ɫ����  
    int imgWidth = size * scale;  
    cv::Mat image = cv::Mat::ones(imgWidth, imgWidth, CV_8UC3) * 255; // ��ɫ����  
  
    // ���ƶ�ά��ĺ�ɫģ��  
    for (int y = 0; y < size; y++) {  
        for (int x = 0; x < size; x++) {  
            if (qrcodegen_getModule(qrcode, x, y)) {  
                // �ڰ�ɫ�����ϻ��ƺ�ɫ��ģ��  
                cv::Rect rect(x * scale, y * scale, scale, scale);  
                image(rect) = cv::Scalar(0, 0, 0); // ��ɫ  
            }  
        }  
    }  
  
    // �����ά��ͼ���ļ�  
    cv::imwrite(outputPath, image);  
  
    //printf("QR code image saved as %s\n", outputPath);  
}  
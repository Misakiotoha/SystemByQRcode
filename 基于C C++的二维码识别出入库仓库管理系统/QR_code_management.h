#pragma once

#include "Base.h"
#include <opencv2/opencv.hpp>




// ��QR�뻺����ת��ΪOpenCVͼ��
//���ܱ������ݺͱ�����ļ�����
void createQRCodeImage(const char* data, string outputPath);

//����������ļ������ɽӿ���ʹ��
string GetQRFromImage(const std::string& filename);

//Ҳ��ʶ��ӿڣ�����׼ȷ�ʲ��ߣ�ֻ����zbar����Ľӿڣ�û���㷨�Ż�
string recognizeQRCode(const std::string& imageFilename);


//zbar�ӿ�
string ZbarDecoder(cv::Mat img);

//�Զ�ֵͼ�����ʶ�����ʧ����������ж���ʶ��
string GetQRInBinImg(cv::Mat binImg);

//main function
string GetQR(cv::Mat img);

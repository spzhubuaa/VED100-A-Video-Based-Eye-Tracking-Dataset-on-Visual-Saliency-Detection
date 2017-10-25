//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv/cv.h> 
//#include <iostream>
//#include <stdio.h>
//#include <math.h>
//#include <string.h>
//#include <io.h> 
//#include <sstream>
//
//using namespace std;
//using namespace cv;
//
//#define radium 48//热点半径
//#define gray 48//热点中心灰度值
//#define debug 0//（if语句判断）调试、预览生成结果
//char videoname[50] = { "832-480-BasketballDrill.avi" };//注意不要缺失: .avi
//char filepath[50] = { "D:\\Exp\\data\\Raw\\" };//数据文件地址
//
//#define frame 1000//预分配帧数
//
//struct database
//{
//	int x[300];
//	int y[300];
//}eyedata[frame];
//
//void circle(IplImage* img, Point point, int width, int height)//利用数据点产生灰度热点
//{
//	CvScalar s;
//	for (int i = 0; i <= radium * 2; i++)
//		for (int j = 0; j <= radium * 2; j++)
//		{
//			int distance = ((i - radium)*(i - radium) + (j - radium)*(j - radium));
//			if (distance >= radium*radium)
//				continue;
//			else if ((point.y + i - radium) <= 0 || (point.y + i - radium) >= height)
//				continue;
//			else if ((point.x + j - radium) <= 0 || (point.x + j - radium) >= width)
//				continue;
//			else
//			{
//				s = cvGet2D(img, point.y + i - radium, point.x + j - radium);
//				s.val[0] = s.val[0] + (gray - (gray / radium)*sqrt(distance)) / 3;
//				cvSet2D(img, point.y + i - radium, point.x + j - radium, s);
//			}
//		}
//}
//
//void colorize(IplImage* temp, IplImage* temp_color, int width, int height)//将不同灰度转为颜色
//{
//	CvScalar s;
//	CvScalar s_color;
//	int colorboard[256][3] = { { 255, 237, 237 },
//	{ 255, 224, 224 },
//	{ 255, 209, 209 },
//	{ 255, 193, 193 },
//	{ 255, 176, 176 },
//	{ 255, 159, 159 },
//	{ 255, 142, 142 },
//	{ 255, 126, 126 },
//	{ 255, 110, 110 },
//	{ 255, 94, 94 },
//	{ 255, 81, 81 },
//	{ 255, 67, 67 },
//	{ 255, 56, 56 },
//	{ 255, 46, 46 },
//	{ 255, 37, 37 },
//	{ 255, 29, 29 },
//	{ 255, 23, 23 },
//	{ 255, 18, 18 },
//	{ 255, 14, 14 },
//	{ 255, 11, 11 },
//	{ 255, 8, 8 },
//	{ 255, 6, 6 },
//	{ 255, 5, 5 },
//	{ 255, 3, 3 },
//	{ 255, 2, 2 },
//	{ 255, 2, 2 },
//	{ 255, 1, 1 },
//	{ 255, 1, 1 },
//	{ 255, 0, 0 },
//	{ 255, 0, 0 },
//	{ 255, 0, 0 },
//	{ 255, 0, 0 },
//	{ 255, 0, 0 },
//	{ 255, 0, 0 },
//	{ 255, 0, 0 },
//	{ 255, 0, 0 },
//	{ 255, 1, 0 },
//	{ 255, 4, 0 },
//	{ 255, 6, 0 },
//	{ 255, 10, 0 },
//	{ 255, 14, 0 },
//	{ 255, 18, 0 },
//	{ 255, 22, 0 },
//	{ 255, 26, 0 },
//	{ 255, 31, 0 },
//	{ 255, 36, 0 },
//	{ 255, 41, 0 },
//	{ 255, 45, 0 },
//	{ 255, 51, 0 },
//	{ 255, 57, 0 },
//	{ 255, 62, 0 },
//	{ 255, 68, 0 },
//	{ 255, 74, 0 },
//	{ 255, 81, 0 },
//	{ 255, 86, 0 },
//	{ 255, 93, 0 },
//	{ 255, 99, 0 },
//	{ 255, 105, 0 },
//	{ 255, 111, 0 },
//	{ 255, 118, 0 },
//	{ 255, 124, 0 },
//	{ 255, 131, 0 },
//	{ 255, 137, 0 },
//	{ 255, 144, 0 },
//	{ 255, 150, 0 },
//	{ 255, 156, 0 },
//	{ 255, 163, 0 },
//	{ 255, 169, 0 },
//	{ 255, 175, 0 },
//	{ 255, 181, 0 },
//	{ 255, 187, 0 },
//	{ 255, 192, 0 },
//	{ 255, 198, 0 },
//	{ 255, 203, 0 },
//	{ 255, 208, 0 },
//	{ 255, 213, 0 },
//	{ 255, 218, 0 },
//	{ 255, 222, 0 },
//	{ 255, 227, 0 },
//	{ 255, 232, 0 },
//	{ 255, 235, 0 },
//	{ 255, 238, 0 },
//	{ 255, 242, 0 },
//	{ 255, 245, 0 },
//	{ 255, 247, 0 },
//	{ 255, 250, 0 },
//	{ 255, 251, 0 },
//	{ 253, 252, 0 },
//	{ 250, 252, 1 },
//	{ 248, 252, 2 },
//	{ 244, 252, 2 },
//	{ 241, 252, 3 },
//	{ 237, 252, 3 },
//	{ 233, 252, 3 },
//	{ 229, 252, 4 },
//	{ 225, 252, 4 },
//	{ 220, 252, 5 },
//	{ 216, 252, 5 },
//	{ 211, 252, 6 },
//	{ 206, 252, 7 },
//	{ 201, 252, 7 },
//	{ 197, 252, 8 },
//	{ 191, 251, 8 },
//	{ 185, 249, 9 },
//	{ 180, 247, 9 },
//	{ 174, 246, 10 },
//	{ 169, 244, 11 },
//	{ 164, 242, 11 },
//	{ 158, 240, 12 },
//	{ 151, 238, 13 },
//	{ 146, 236, 14 },
//	{ 140, 233, 14 },
//	{ 134, 231, 15 },
//	{ 128, 228, 16 },
//	{ 122, 226, 17 },
//	{ 116, 223, 18 },
//	{ 110, 221, 19 },
//	{ 105, 218, 20 },
//	{ 99, 216, 21 },
//	{ 93, 214, 22 },
//	{ 88, 211, 23 },
//	{ 82, 209, 24 },
//	{ 76, 207, 25 },
//	{ 71, 204, 26 },
//	{ 66, 202, 28 },
//	{ 60, 200, 30 },
//	{ 55, 198, 31 },
//	{ 50, 196, 33 },
//	{ 45, 194, 34 },
//	{ 40, 191, 35 },
//	{ 36, 190, 37 },
//	{ 31, 188, 39 },
//	{ 27, 187, 40 },
//	{ 23, 185, 43 },
//	{ 19, 184, 44 },
//	{ 15, 183, 46 },
//	{ 12, 182, 48 },
//	{ 9, 181, 51 },
//	{ 6, 181, 53 },
//	{ 3, 180, 55 },
//	{ 1, 180, 57 },
//	{ 0, 180, 60 },
//	{ 0, 180, 62 },
//	{ 0, 180, 65 },
//	{ 0, 181, 68 },
//	{ 0, 182, 70 },
//	{ 0, 182, 74 },
//	{ 0, 183, 77 },
//	{ 0, 184, 80 },
//	{ 0, 184, 84 },
//	{ 0, 186, 88 },
//	{ 0, 187, 92 },
//	{ 0, 188, 95 },
//	{ 0, 190, 99 },
//	{ 0, 191, 104 },
//	{ 0, 193, 108 },
//	{ 0, 194, 112 },
//	{ 0, 196, 116 },
//	{ 0, 198, 120 },
//	{ 0, 200, 125 },
//	{ 0, 201, 129 },
//	{ 0, 203, 134 },
//	{ 0, 205, 138 },
//	{ 0, 207, 143 },
//	{ 0, 209, 147 },
//	{ 0, 211, 151 },
//	{ 0, 213, 156 },
//	{ 0, 215, 160 },
//	{ 0, 216, 165 },
//	{ 0, 219, 171 },
//	{ 0, 222, 178 },
//	{ 0, 224, 184 },
//	{ 0, 227, 190 },
//	{ 0, 229, 197 },
//	{ 0, 231, 203 },
//	{ 0, 233, 209 },
//	{ 0, 234, 214 },
//	{ 0, 234, 220 },
//	{ 0, 234, 225 },
//	{ 0, 234, 230 },
//	{ 0, 234, 234 },
//	{ 0, 234, 238 },
//	{ 0, 234, 242 },
//	{ 0, 234, 246 },
//	{ 0, 234, 248 },
//	{ 0, 234, 251 },
//	{ 0, 234, 254 },
//	{ 0, 234, 255 },
//	{ 0, 232, 255 },
//	{ 0, 228, 255 },
//	{ 0, 224, 255 },
//	{ 0, 219, 255 },
//	{ 0, 214, 254 },
//	{ 0, 208, 252 },
//	{ 0, 202, 250 },
//	{ 0, 195, 247 },
//	{ 0, 188, 244 },
//	{ 0, 180, 240 },
//	{ 0, 173, 236 },
//	{ 0, 164, 232 },
//	{ 0, 156, 228 },
//	{ 0, 147, 222 },
//	{ 0, 139, 218 },
//	{ 0, 130, 213 },
//	{ 0, 122, 208 },
//	{ 0, 117, 205 },
//	{ 0, 112, 203 },
//	{ 0, 107, 199 },
//	{ 0, 99, 196 },
//	{ 0, 93, 193 },
//	{ 0, 86, 189 },
//	{ 0, 78, 184 },
//	{ 0, 71, 180 },
//	{ 0, 65, 175 },
//	{ 0, 58, 171 },
//	{ 0, 52, 167 },
//	{ 0, 46, 162 },
//	{ 0, 40, 157 },
//	{ 0, 35, 152 },
//	{ 0, 30, 147 },
//	{ 0, 26, 142 },
//	{ 0, 22, 136 },
//	{ 0, 18, 131 },
//	{ 0, 15, 126 },
//	{ 0, 12, 120 },
//	{ 0, 9, 115 },
//	{ 0, 8, 110 },
//	{ 0, 6, 105 },
//	{ 0, 5, 100 },
//	{ 0, 4, 95 },
//	{ 0, 3, 90 },
//	{ 0, 2, 85 },
//	{ 0, 1, 80 },
//	{ 0, 0, 75 },
//	{ 0, 0, 70 },
//	{ 0, 0, 65 },
//	{ 0, 0, 60 },
//	{ 0, 0, 56 },
//	{ 0, 0, 53 },
//	{ 0, 0, 50 },
//	{ 0, 0, 46 },
//	{ 0, 0, 43 },
//	{ 0, 0, 40 },
//	{ 0, 0, 37 },
//	{ 0, 0, 34 },
//	{ 0, 0, 30 },
//	{ 0, 0, 27 },
//	{ 0, 0, 24 },
//	{ 0, 0, 21 },
//	{ 0, 0, 18 },
//	{ 0, 0, 15 },
//	{ 0, 0, 12 },
//	{ 0, 0, 9 },
//	{ 0, 0, 6 },
//	{ 0, 0, 3 },
//	{ 0, 0, 0 } };
//	for (int i = 0; i <= width - 1; i++)
//	{
//		for (int j = 0; j <= height - 1; j++)
//		{
//			s = cvGet2D(temp, j, i);
//			s_color.val[2] = colorboard[255 - int(s.val[0])][0];
//			s_color.val[1] = colorboard[255 - int(s.val[0])][1];
//			s_color.val[0] = colorboard[255 - int(s.val[0])][2];
//			cvSet2D(temp_color, j, i, s_color);
//		}
//	}
//}
//
//int main()
//{
//	char videopath[100] = { "D:\\Exp\\DataProcess\\avi\\" };
//	strcat(videopath, videoname);
//	char videoname_backup[50];
//	strcpy(videoname_backup, videoname);
//
//	char *strToken = nullptr;
//	char *nextToken = nullptr;
//	strToken = strtok_s(videoname, "-", &nextToken);
//	int width;
//	sscanf(strToken, "%d", &width);
//	strToken = strtok_s(nullptr, "-", &nextToken);
//	int height;
//	sscanf(strToken, "%d", &height);
//	char *outputname;
//	outputname = nextToken;
//
//	IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
//	IplImage *temp = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
//	IplImage *temp_color = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
//	cvZero(img);
//	cvZero(temp);
//	cvZero(temp_color);
//	Point pt;
//	CvCapture* videocapt = cvCreateFileCapture(videopath);//输入原始视频，avi格式
//	img = cvQueryFrame(videocapt);
//	if (!img) return -2;
//	//int ImgCount = 1;
//	//char path[25];
//	char outputpath[50] = { "D:\\Exp\\DataProcess\\output\\" };
//	strcat(outputpath, videoname_backup);
//	CvVideoWriter *pwriter;
//	pwriter = cvCreateVideoWriter(outputpath, CV_FOURCC('M', 'J', 'P', 'G'), 30, Size(width, height));//保存输出文件
//	outputname = strtok_s(nullptr, ".", &nextToken);
//
//	strcat(outputname, ".txt");
//	strcat(filepath, outputname);
//
//	FILE *fp = NULL;
//	fp = fopen(filepath, "r");//数据文件地址，只读
//	if (fp == NULL)
//	{
//		printf("failed to open txt\n");
//		return -1;
//	}
//
//	int n = 0;
//	float axisx = 0;
//	float axisy = 0;
//	int framecount[frame] = { -1 };
//	while (!feof(fp))//读入所有数据，并将同一帧的数据放到一起
//	{
//		fscanf(fp, "%d %f %f", &n, &axisx, &axisy);
//		n = n - 1;
//		if (framecount[n] <= 0)
//		{
//			framecount[n] = 1;
//		}
//		eyedata[n].x[framecount[n] - 1] = int(axisx / (3840.0 / width));
//		eyedata[n].y[framecount[n] - 1] = int(axisy / (2160.0 / height));
//		framecount[n]++;
//	}
//
//	for (int i = 0; i <= frame; i++)//生成热图并与原始图像合并
//	{
//		char imgname[50];
//		sprintf(imgname, "img %d.jpg", i);
//		//cvSaveImage(imgname, img);
//		for (int j = 0; j <= 300; j++)
//		{
//			if (eyedata[i].x[j] == 0)
//			{
//				break;
//			}
//			pt.x = eyedata[i].x[j];
//			pt.y = eyedata[i].y[j];
//			circle(temp, pt, width, height);
//		}
//
//		//colorize(temp, temp_color, width, height);
//		cvThreshold(temp, temp, 254, 255, 0);
//		//cvAddWeighted(img, 1, temp_color, 1, 0.0, img);
//		if (debug)
//		{
//			cvShowImage("Result", temp);
//			cvWaitKey(0);
//		}
//		sprintf(imgname, "output %d.jpg", i);
//		cvSaveImage(imgname, temp);
//		cvZero(temp);
//		cvZero(temp_color);
//		/*sprintf(path, "temp %d", ImgCount);
//		strcat(path, ".jpg");
//		cvSaveImage(path, temp);
//		sprintf(path, "img %d", ImgCount);
//		strcat(path, ".jpg");
//		cvSaveImage(path, img);
//		ImgCount++;*/
//		//cvShowImage("Result", temp_color);
//
//		cvWriteFrame(pwriter, img);
//		printf("%d\n", i);
//		img = cvQueryFrame(videocapt);
//		if (!img) break;
//	}
//
//	cvReleaseVideoWriter(&pwriter);
//	cout << "Program Finished" << endl;
//	//getchar();
//	return 0;
//}
#include<stdio.h>
#include<stdlib.h>

#define BMP_HEIGHT 180                                                                    //BMP的高度（最少为64）
#define BMP_WIDTH 480                                                                     //BMP的宽度(最少为480)

typedef unsigned short WORD;                                                              // 定义WORD为两个字节的类型

typedef int DWORD;                                                                        // 定义DWORD为四个字节的类型
 

#pragma pack(push)
#pragma pack(1)                                                                           // 定义为1字节对齐,否则文件头为16字节

typedef struct BMP_FILE_HEADER
{
	WORD bType;                                                                           // 文件标识符 
	DWORD bSize;                                                                          // 文件的大小 
	WORD bReserved1;                                                                      // 保留值,必须设置为0  
	WORD bReserved2;                                                                      // 保留值,必须设置为0 
	DWORD bOffset;                                                                        // 文件头的最后到图像数据位开始的偏移量 
} BMPFILEHEADER;                                                                          // 14 字节
 
typedef struct BMP_INFO                                                                   // 位图信息头
{
	DWORD bInfoSize;                                                                      // 信息头的大小   
	DWORD bWidth;                                                                         // 图像的宽度     
	DWORD bHeight;                                                                        // 图像的高度     
	WORD bPlanes;                                                                         // 图像的位面数   
	WORD bBitCount;                                                                       // 每个像素的位数 
	DWORD bCompression;                                                                   // 压缩类型 
	DWORD bmpImageSize;                                                                   // 图像的大小,以字节为单位 
	DWORD bXPelsPerMeter;                                                                 // 水平分辨率 
	DWORD bYPelsPerMeter;                                                                 // 垂直分辨率 
	DWORD bClrUsed;                                                                       // 使用的色彩数 
	DWORD bClrImportant;                                                                  // 重要的颜色数 
} BMPINF;                                                                                 // 40 字节
 

typedef struct RGB_QUAD                                                                   // 彩色表:调色板
{
	char rgbBlue;                                                                         // 蓝色强度 
	char rgbGreen;                                                                        // 绿色强度 
	char rgbRed;                                                                          // 红色强度 
} RGBQUAD;
#pragma pack(pop)

char mat[16][2];                                                                          // 用于存放中文数据
char word[14][1];                                                                         // 用于存放英文数据
FILE *fp;                                                                                 // bmp文件指针

int creat_bmp(void);                                                                      //函数声明
int chinese_put(char *buf);
int english_put(char buf);

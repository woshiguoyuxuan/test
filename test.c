#include"my_bmp.h"

int main(void)
{
	int hei,wid,k,i,j;
	int offset_bmp;
	char r,g,b;
	unsigned char byte_data;
	
	unsigned char buf1[3] = "嵌";
	unsigned char buf2[3] = "入";
	unsigned char buf3[3] = "式";
	unsigned char buf4[5] = {'L','i','n','u','x'};
	unsigned char buf5[3] = "开";
	unsigned char buf6[3] = "发";
	creat_bmp();                                                                           //创建BMP文件
	RGBQUAD image[BMP_HEIGHT][BMP_WIDTH];                                                  //定义一个存放BMP颜色数据的二维数组
	
	offset_bmp = (3*BMP_WIDTH)%4;                                                          //由于内存自动4字节对齐，所以设置偏移量防止被丢弃数据
	if(offset_bmp != 0)
	{
		offset_bmp = 4 - offset_bmp;
	}
	
	for(i = 0; i < 3; i++)                                                                 //前三个中文写入BMP文件
	{
		switch(i)
		{
			case 0:
				chinese_put(buf1); 
				break;
			case 1:
				chinese_put(buf2); 
				break;
			case 2:
				chinese_put(buf3); 
				break;
			default:
				printf("undifine information!\n");
				return -1;
		}
		for(hei = 60;hei < 124;hei++)                                                      //从60列开始写入
		{
			for(wid = 64 * i;wid < 64 * (i + 1); wid += 32)
			{
				for(k = 0; k < 8; k++)
				{
					for(j = 0; j < 4; j++)
					{
						if( mat[(hei - 60)/4][(wid - 64 * i)/32]&(0x80>>k) )               //每个点填充4*4个像素
						{
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbBlue  = 0;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbGreen = 0;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbRed   = 0;
						}
						else
						{
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbBlue  = 0xff;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbGreen = 0xff;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbRed   = 0xff;
						}
					}
				}
			}
		}
	}
	for(i = 0; i < 5; i++)                                                                  //把5个英文写入BMP文件
	{
		english_put(buf4[i]);
		for(hei = 68;hei < 124;hei++)                                                       //从68列开始写入
		{
			for(wid = 192 + 32 * i; wid < 192 + 32 * (i + 1); wid += 32)        
			{
				for(k = 0; k < 8; k++)
				{
					for(j = 0; j < 4; j++)
					{
						if( word[(hei - 68)/4] [(wid - (192 + 32 * i))/32]&(0x80>>k) )    
						{
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbBlue  = 0;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbGreen = 0;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbRed   = 0;
						}
						else
						{
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbBlue  = 0xff;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbGreen = 0xff;
							image[BMP_HEIGHT - hei - 1][wid+4*k+j].rgbRed   = 0xff;
						}
					}
				}
			}
		}
	}
	for(i = 0; i < 2; i++)                                                                  //后两个中文写入BMP文件
	{
		switch(i)
		{
			case 0:
				chinese_put(buf5); 
				break;
			case 1:
				chinese_put(buf6); 
				break;
			default:
				printf("undifine information!\n");
				return -1;
		}
		for(hei = 60;hei < 124;hei++)                                                        //从60列开始写入
		{
			for(wid = 352 + 64 * i;wid < 352 + 64 * (i + 1); wid += 32)
			{
				for(k = 0; k < 8; k++)
				{
					for(j = 0;j < 4; j++)
					{
						if( mat[(hei - 60)/4][(wid - (352 + 64 * i))/32]&(0x80>>k) )         //每个点填充4*4个像素
						{
							image[BMP_HEIGHT - hei - 1][wid+j+4*k].rgbBlue  = 0;
							image[BMP_HEIGHT - hei - 1][wid+j+4*k].rgbGreen = 0;
							image[BMP_HEIGHT - hei - 1][wid+j+4*k].rgbRed   = 0;
						}
						else
						{
							image[BMP_HEIGHT - hei - 1][wid+j+4*k].rgbBlue  = 0xff;
							image[BMP_HEIGHT - hei - 1][wid+j+4*k].rgbGreen = 0xff;
							image[BMP_HEIGHT - hei - 1][wid+j+4*k].rgbRed   = 0xff;
						}
					}
				}
			}
		}
	}
	fseek(fp, 54, SEEK_SET);                                                                  //写入像素数组的数据到BMP文件
	for (i = 0; i < BMP_HEIGHT; i++)  
	{  
		for (j = 0; j < BMP_WIDTH; j++)  
		{  
			byte_data = image[i][j].rgbBlue;  
			fwrite(&byte_data, sizeof(unsigned char), 1, fp);  
			byte_data = image[i][j].rgbGreen;  
			fwrite(&byte_data, sizeof(unsigned char), 1, fp);  
			byte_data = image[i][j].rgbRed;  
			fwrite(&byte_data, sizeof(unsigned char), 1, fp);               
		}  
		if (offset_bmp!=0)  
		{   
			byte_data = 0;
			fwrite(&byte_data, sizeof(unsigned char), offset_bmp, fp);                        //4字节对齐产生的多余空间补零
		}  
	}  
	fclose(fp);
	return 0;
	
	
}
int creat_bmp(void)                                                                           //创建BMP文件及参数初始化
{
	BMPFILEHEADER bmpFileHeader;                                                              // BMP 文件头的结构体
	BMPINF bmpInfo;                                                                           // BMP 文件信息结构体
	if((fp = fopen("a.bmp", "wb")) == NULL) 
	{
		printf("Cann't open the file!\n");
		return 0;
	}
	bmpInfo.bInfoSize = 40;
	bmpInfo.bBitCount = 24;
	bmpInfo.bHeight = BMP_HEIGHT;
	bmpInfo.bWidth = BMP_WIDTH;
	bmpInfo.bmpImageSize = bmpInfo.bHeight*bmpInfo.bWidth*bmpInfo.bBitCount/8;
	bmpInfo.bCompression = 0;
	bmpInfo.bClrImportant = 0;
	bmpInfo.bClrUsed = 0;
	bmpInfo.bXPelsPerMeter = 0;
	bmpInfo.bYPelsPerMeter = 0;
	bmpInfo.bPlanes = 1;                                                                      
 
	bmpFileHeader.bType = 0x4D42;
	bmpFileHeader.bOffset = 54;
	bmpFileHeader.bSize = bmpInfo.bmpImageSize + bmpFileHeader.bOffset;
	bmpFileHeader.bReserved1 = 0;
	bmpFileHeader.bReserved2 = 0;
	
	fseek(fp, 0, SEEK_SET); 
    int num1 = fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);                          // 把BMP 文件头的结构体数据写入文件
	if(ferror(fp) != 0)
	{
		if(!feof(fp))
		{
			perror("write 1 failed");
			return -1;
		}
	}
	fseek(fp, 14, SEEK_SET); 
	int num2 = fwrite(&bmpInfo, sizeof(bmpInfo), 1, fp);                                      // 把BMP 文件信息的结构体数据写入文件
	if(ferror(fp) != 0)
	{
		if(!feof(fp))
		{
			perror("write 2 failed");
			return -1;
		}
	}
	
}
int chinese_put(char *buf)                                                                   //把传入的中文数据导入到全局变量mat中
{
	unsigned char qh,wh;
	unsigned long offset;
	qh = buf[0] - 0xa0;
	wh = buf[1] - 0xa0;
	offset = ( 94 * (qh - 1) + (wh - 1) ) * 32;                                              // 中文字库偏移量
	FILE *HZK; 
	 
	if((HZK=fopen("./HZK1616.dat", "rb")) == NULL) 
	{ 
		printf("Can’t Open hzk16\n"); 
		return -1; 
	} 
	fseek(HZK, offset, SEEK_SET);                                                            // 偏移到合适位置
	fread(mat, 32, 1, HZK);                                                                  // 读取数据
	fclose(HZK);
}
int english_put(char buf)                                                                    //把传入的英文数据导入到全局变量word中
{
	unsigned long offset;
	offset = buf*14;                                                                         // 英文字库偏移量
	FILE *asci;
	if((asci = fopen("./ASC0814.dat","rb")) == NULL)
	{
		printf("open ascii failed!\n");
		return -1;
	}
	fseek(asci,offset,SEEK_SET);
	fread(word,14,1,asci);
	fclose(asci);	
}

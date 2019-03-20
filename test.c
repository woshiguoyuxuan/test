#include"my_bmp.h"

int main(void)
{
	int hei,wid,k,i,j;
	int offset_bmp;
	char r,g,b;
	unsigned char byte_data;
	
	unsigned char buf1[3] = "Ƕ";
	unsigned char buf2[3] = "��";
	unsigned char buf3[3] = "ʽ";
	unsigned char buf4[5] = {'L','i','n','u','x'};
	unsigned char buf5[3] = "��";
	unsigned char buf6[3] = "��";
	creat_bmp();                                                                           //����BMP�ļ�
	RGBQUAD image[BMP_HEIGHT][BMP_WIDTH];                                                  //����һ�����BMP��ɫ���ݵĶ�ά����
	
	offset_bmp = (3*BMP_WIDTH)%4;                                                          //�����ڴ��Զ�4�ֽڶ��룬��������ƫ������ֹ����������
	if(offset_bmp != 0)
	{
		offset_bmp = 4 - offset_bmp;
	}
	
	for(i = 0; i < 3; i++)                                                                 //ǰ��������д��BMP�ļ�
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
		for(hei = 60;hei < 124;hei++)                                                      //��60�п�ʼд��
		{
			for(wid = 64 * i;wid < 64 * (i + 1); wid += 32)
			{
				for(k = 0; k < 8; k++)
				{
					for(j = 0; j < 4; j++)
					{
						if( mat[(hei - 60)/4][(wid - 64 * i)/32]&(0x80>>k) )               //ÿ�������4*4������
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
	for(i = 0; i < 5; i++)                                                                  //��5��Ӣ��д��BMP�ļ�
	{
		english_put(buf4[i]);
		for(hei = 68;hei < 124;hei++)                                                       //��68�п�ʼд��
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
	for(i = 0; i < 2; i++)                                                                  //����������д��BMP�ļ�
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
		for(hei = 60;hei < 124;hei++)                                                        //��60�п�ʼд��
		{
			for(wid = 352 + 64 * i;wid < 352 + 64 * (i + 1); wid += 32)
			{
				for(k = 0; k < 8; k++)
				{
					for(j = 0;j < 4; j++)
					{
						if( mat[(hei - 60)/4][(wid - (352 + 64 * i))/32]&(0x80>>k) )         //ÿ�������4*4������
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
	fseek(fp, 54, SEEK_SET);                                                                  //д��������������ݵ�BMP�ļ�
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
			fwrite(&byte_data, sizeof(unsigned char), offset_bmp, fp);                        //4�ֽڶ�������Ķ���ռ䲹��
		}  
	}  
	fclose(fp);
	return 0;
	
	
}
int creat_bmp(void)                                                                           //����BMP�ļ���������ʼ��
{
	BMPFILEHEADER bmpFileHeader;                                                              // BMP �ļ�ͷ�Ľṹ��
	BMPINF bmpInfo;                                                                           // BMP �ļ���Ϣ�ṹ��
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
    int num1 = fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);                          // ��BMP �ļ�ͷ�Ľṹ������д���ļ�
	if(ferror(fp) != 0)
	{
		if(!feof(fp))
		{
			perror("write 1 failed");
			return -1;
		}
	}
	fseek(fp, 14, SEEK_SET); 
	int num2 = fwrite(&bmpInfo, sizeof(bmpInfo), 1, fp);                                      // ��BMP �ļ���Ϣ�Ľṹ������д���ļ�
	if(ferror(fp) != 0)
	{
		if(!feof(fp))
		{
			perror("write 2 failed");
			return -1;
		}
	}
	
}
int chinese_put(char *buf)                                                                   //�Ѵ�����������ݵ��뵽ȫ�ֱ���mat��
{
	unsigned char qh,wh;
	unsigned long offset;
	qh = buf[0] - 0xa0;
	wh = buf[1] - 0xa0;
	offset = ( 94 * (qh - 1) + (wh - 1) ) * 32;                                              // �����ֿ�ƫ����
	FILE *HZK; 
	 
	if((HZK=fopen("./HZK1616.dat", "rb")) == NULL) 
	{ 
		printf("Can��t Open hzk16\n"); 
		return -1; 
	} 
	fseek(HZK, offset, SEEK_SET);                                                            // ƫ�Ƶ�����λ��
	fread(mat, 32, 1, HZK);                                                                  // ��ȡ����
	fclose(HZK);
}
int english_put(char buf)                                                                    //�Ѵ����Ӣ�����ݵ��뵽ȫ�ֱ���word��
{
	unsigned long offset;
	offset = buf*14;                                                                         // Ӣ���ֿ�ƫ����
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char clip_value(unsigned char x, unsigned char min_val,unsigned char max_val)
{   
    if(x > max_val)
        return max_val;
    else if(x < min_val)
        return min_val;
    else
        return x;
}

//RGB TO YUV420
void RGB24_TO_YUV420(unsigned char *RgbBuf, int w, int h, unsigned char *yuvBuf)
{
    unsigned char *ptrY, *ptrU, *ptrV, *ptrRGB;
    memset(yuvBuf,0,w*h*3/2);
    ptrY = yuvBuf;
    ptrU = yuvBuf + w * h;
    ptrV = ptrU + (w*h*1/4);
    unsigned char y, u, v, r, g, b;
    for(int j = 0; j < h; j++)
    {
        ptrRGB = RgbBuf + w*j*3;
        for(int i = 0;i < w;i++)
        {
            r = *(ptrRGB++);
            g = *(ptrRGB++);
            b = *(ptrRGB++);     
            y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16;
            u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128;
            v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128;
            *(ptrY++) = clip_value(y,0,255);
			if (j%2==0&&i%2 ==0){
				*(ptrU++) =clip_value(u,0,255);
			}
			else{
				if (i%2==0){
				*(ptrV++) =clip_value(v,0,255);
				}
			}            
        }
    }
}

int simplest_rgb24_to_yuv420(char *url_in, int w, int h, int num, char *url_out)
{
    FILE *fp = fopen(url_in, "rb+");
    FILE *fp1 = fopen(url_out, "wb+");

    unsigned char *pic_rgb24 = (unsigned char *)malloc(w*h*3);
    unsigned char *pic_yuv420 = (unsigned char *)malloc(w*h*3/2);

    for(int i = 0; i<num; i++)
    {
        fread(pic_rgb24, 1, w*h*3,fp);
        RGB24_TO_YUV420(pic_rgb24, w, h, pic_yuv420);
        fwrite(pic_yuv420, 1, w*h*3/2, fp1);
    }

    free(pic_rgb24);
    free(pic_yuv420);
    fclose(fp);
    fclose(fp1);

    return 0;
}

int main(int argc,char *argv[])
{
    printf("rgb24 convert to yuv420...\r\n");
    simplest_rgb24_to_yuv420("lena_256x256_rgb24.rgb",256,256,1,"output_lena.yuv");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simplest_yuv420_border(char *url, int w, int h, int border, int num)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_border.yuv", "wb+");

    unsigned char *pic = (unsigned char *)malloc(w * h * 3 / 2);

    for(int i = 0;i < num;i++)
    {
        fread(pic, 1, w * h * 3 / 2, fp);

        //Y
        for (int j = 0;j < h;j++)
        {
            for (int k = 0;k < w;k++)
            {
                if(k<border || k > (w - border) || j < border || j > (h - border))
                {
                    pic[j*w + k] = 255;
                }
            }

        }
        fwrite(pic, 1, w * h * 3 / 2, fp1);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);

    return 0;
}

int main(int argc,char *argv[])
{
    printf("yuv420 add border...\r\n");
    simplest_yuv420_border("lena_256x256_yuv420p.yuv", 256, 256, 20, 1);
    return 0;
}
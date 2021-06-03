#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simplest_rgb24_split(char *url, int w, int h, int num)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_r.y","wb+");
    FILE *fp2 = fopen("output_g.y","wb+");
    FILE *fp3 = fopen("output_b.y","wb+");

    unsigned char *pic = (unsigned char *)malloc(w * h * 3);
    unsigned char *picr = (unsigned char *)malloc(w * h * 3);
    unsigned char *picg = (unsigned char *)malloc(w * h * 3);
    unsigned char *picb = (unsigned char *)malloc(w * h * 3);
    
    memset(picr, 0, w * h * 3);
    memset(picg, 0, w * h * 3);
    memset(picb, 0, w * h * 3);
    
    int pc = 0;

    for(int i = 0;i < num; i++)
    {
        fread(pic, 1, w*h*3, fp);
        for(int j = 0;j < w * h * 3;j = j + 3)
        {
        	picr[j] =  *(pic + j);      //R
           	picg[j + 1] =  *(pic + j + 1);      //g
           	picb[j + 2] =  *(pic + j + 2);      //b

            printf("j = %d, r = %d g = %d b = %d\r\n",j, picr[j],picg[j + 1],picb[j + 2]);
        }
    }
    
    //R
    fwrite(picr, 1, w * h * 3, fp1);

    //G
    fwrite(picg,1, w * h * 3, fp2);

    //B
    fwrite(picb, 1, w * h * 3, fp3);

    free(pic);
    free(picr);
    free(picg);
    free(picb);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}

int main(int argc,char *argv[])
{
    printf("parse rgb24 to split r,g,b...\r\n");
    simplest_rgb24_split("cie1931_500x500.rgb", 500, 500,1);
    return 0;
}
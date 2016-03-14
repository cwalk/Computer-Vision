/*Clayton Walker
 CAP 4453 Spring 2015
 Assignment 1
 */
#include <stdio.h>                          /* Sobel.c */
#include <math.h>

int pic[256][256];
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
double ival[256][256],maxival;

int main(argc,argv)
int argc;
char **argv;
{

    int i,j,p,q,mr,sum1,sum2;
    double lowThreshold, highThreshold;
    FILE *fo1, *fo2, *fo3, *fp1, *fopen();
//    char inputFilename[20], outputFilename[20];
//    printf("What is the name of your input file?\n");
//    scanf("%s", inputFilename);
//    printf("What is the name of your output file?\n");
//    scanf("%s", outputFilename);
//
//    fp1 = fopen(inputFilename, "rb");
//    fo1 = fopen(outputFilename, "wb");

    printf("What is your low Threshold?\n");
    scanf("%lf", &lowThreshold);
    printf("What is your high Threshold?\n");
    scanf("%lf", &highThreshold);

    fp1 = fopen("face05.pgm", "rb");
    fo1 = fopen("HW1Magout.pgm", "wb");
    fo2 = fopen("HW1LOWout.pgm", "wb");
    fo3 = fopen("HW1HIGHout.pgm", "wb");

    fprintf(fo1,"P5\n256 256\n255\n");  /* Print out the .pgm header */
    fprintf(fo2,"P5\n256 256\n255\n");
    fprintf(fo3,"P5\n256 256\n255\n");

    //To get rid of input file's Header
    char test[20];
    for (i=1;i<=4;i++)
    {
        fscanf(fp1,"%s", test);
        //printf("%s", test);
    }

    for (i=0; i<256; i++)
    {
        for (j=0; j<256; j++)
        {
            pic[i][j]  =  getc (fp1);
            pic[i][j]  &= 0377;
        }
    }

    mr = 1;
    for (i=mr; i<256-mr; i++)
    {
        for (j=mr; j<256-mr; j++)
        {
            sum1 = 0;
            sum2 = 0;
            for (p=-mr; p<=mr; p++)
            {
                for (q=-mr; q<=mr; q++)
                {
                    sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
                    sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
                }
            }
            outpicx[i][j] = sum1;
            outpicy[i][j] = sum2;
        }
    }

    maxival = 0;
    for (i=mr; i<256-mr; i++)
    {
        for (j=mr; j<256-mr; j++)
        {
            ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
                                     (outpicy[i][j]*outpicy[i][j])));
            if (ival[i][j] > maxival)
                maxival = ival[i][j];
        }
    }

    for (i=0; i<256; i++)
    {
        for (j=0; j<256; j++)
        {
            ival[i][j] = (ival[i][j] / maxival) * 255;
            fprintf(fo1,"%c",(char)((int)(ival[i][j])));
        }
    }

    for (i=0; i<256; i++)
    {
        for (j=0; j<256; j++)
        {
            //Low Threshold algorithm
            if(ival[i][j] > lowThreshold)
                fprintf(fo2,"%c",(char)((int)(255)));
            else
                fprintf(fo2,"%c",(char)((int)(0)));

            //High Threshold algorithm
            if(ival[i][j] > highThreshold)
                fprintf(fo3,"%c",(char)((int)(255)));
            else
                fprintf(fo3,"%c",(char)((int)(0)));
        }
    }

    fclose(fp1);
    fclose(fo1);
    fclose(fo2);
    fclose(fo3);
    return 0;
}

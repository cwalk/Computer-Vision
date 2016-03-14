/*Clayton Walker
CAP 4453 Spring 2015
Assignment 2
*/

#include <stdio.h>                  /*  Marr-Hildreth.c  (or marrh.c) */
#include <math.h>
#define  PICSIZE 256
#define  MAXMASK 100

    int    pic[PICSIZE][PICSIZE];
    double outpicx[PICSIZE][PICSIZE];
    double outpicy[PICSIZE][PICSIZE];
    double ival[PICSIZE][PICSIZE];
    double maskx[MAXMASK][MAXMASK];
    double masky[MAXMASK][MAXMASK];
    double peaks[PICSIZE][PICSIZE];
    double finalEdges[PICSIZE][PICSIZE];


int main(argc,argv)
int argc;
char **argv;
{
        int     i, j, k, l, p, q, s, t, mr, centx, centy, moretodo;
        double  maskval, sum1, sum2, sig, maxival, dir, lowThreshold, highThreshold;
        FILE    *fo1, *fo2, *fo3, *fp1, *fopen();

        /*printf("What is your low Threshold?\n");
        scanf("%lf", &lowThreshold);
        printf("What is your high Threshold?\n");
        scanf("%lf", &highThreshold);*/

        fp1 = fopen("garb34.pgm", "rb");
        fo1 = fopen("garb34mag.pgm", "wb");
        fo2 = fopen("garb34peaks.pgm", "wb");
        fo3 = fopen("garb34final.pgm", "wb");

        fprintf(fo1,"P5\n256 256\n255\n");  /* Print out the .pgm header */
        fprintf(fo2,"P5\n256 256\n255\n");
        fprintf(fo3,"P5\n256 256\n255\n");

        //To get rid of input file's Header
        char test[20];
        for (i=0;i<=3;i++)
        {
            fscanf(fp1,"%s", test);
            //printf("%s", test);
        }

        //make sig 1
        sig = 1;

        mr = (int)(sig * 3);
        centx = (MAXMASK / 2);
        centy = (MAXMASK / 2);

        /**PART1**/
        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
                {
                  pic[i][j]  =  getc (fp1);
                }
        }

        for (p=-mr;p<=mr;p++)
        {  for (q=-mr;q<=mr;q++)
           {
               maskval = ((-q)*(exp(-1*(((p*p)+(q*q))/(2*(sig*sig))))));
               (maskx[p+centy][q+centx]) = maskval;
               maskval = ((-p)*(exp(-1*(((p*p)+(q*q))/(2*(sig*sig))))));
               (masky[p+centy][q+centx]) = maskval;
           }
        }

        for (i=mr;i<=255-mr;i++)
        { for (j=mr;j<=255-mr;j++)
          {
             sum1 = 0;
             sum2 = 0;
             for (p=-mr;p<=mr;p++)
             {
                for (q=-mr;q<=mr;q++)
                {
                   sum1 += pic[i+p][j+q] * maskx[p+centy][q+centx];
                   sum2 += pic[i+p][j+q] * masky[p+centy][q+centx];
                }
             }
              outpicx[i][j] = sum1;
              outpicy[i][j] = sum2;
             //conv[i][j] = sum;
          }
        }


    //Bring in Sqrt of squares code from Sobel.c
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

    /**PART 2**/
    for (i=mr;i<256-mr;i++)
    {
        for (j=mr;j<256-mr;j++)
        {
            if((outpicx[i][j]) == 0.0)
            {
                outpicx[i][j] = 0.00001;
            }
            dir = outpicy[i][j]/outpicx[i][j];
            if((dir <= 0.4142) && (dir > -0.4142))
            {
                if((ival[i][j] > ival[i][j-1]) && (ival[i][j] > ival[i][j+1]))
                {
                  peaks[i][j] = 255;
                }
            }
            else if((dir <= 2.4142) && (dir > 0.4142))
            {
                if((ival[i][j] > ival[i-1][j-1]) && (ival[i][j] > ival[i+1][j+1]))
                {
                    peaks[i][j] = 255;
                }
            }
            else if((dir <= -0.4142) && (dir > -2.4142))
            {
                if((ival[i][j] > ival[i+1][j-1]) && (ival[i][j] > ival[i-1][j+1]))
                {
                    peaks[i][j] = 255;
                }
            }
            else
            {
                if((ival[i][j] > ival[i-1][j]) && (ival[i][j] > ival[i+1][j]))
                {
                    peaks[i][j] = 255;
                }
            }
        }
    }

    for (i=0;i<PICSIZE;i++)
    {
        for (j=0;j<PICSIZE;j++)
        {
            if (peaks[i][j] == 255)
                fprintf(fo2,"%c",(char)((int)(255)));
            else
                fprintf(fo2,"%c",(char)((int)(0)));
        }
    }

    /**PART4**/
    double Percent = 0.05;
    int Histogram[PICSIZE] = { 0 };
    for (i=0; i<256; i++)
    {
        for (j=0; j<256; j++)
        {
            //printf("Histogram[%d] is now %lf because ival[%d][%d] is %lf, plus 1.\n", i, Histogram[i], i, j, ival[i][j]);
            (Histogram[(int)ival[i][j]])++;

        }
    }
    double CutOff = Percent*PICSIZE*PICSIZE;
    //printf("CutOff is %lf\n", CutOff);
    double AreaOfTops = 0;
    for(i=255;i>0;i--)
    {
        //printf("AreaOfTops before is %lf, because Histogram[%d] is %lf\n", AreaOfTops, i, Histogram[i]);
        AreaOfTops += Histogram[i];
        //printf("AreaOfTops after is %lf, because Histogram[%d] is %lf\n", AreaOfTops, i, Histogram[i]);
        if(AreaOfTops>CutOff)
        {
            //printf("We are now breaking out of loop. AreaOfTops is %lf and CutOff is %lf\n", AreaOfTops, CutOff);
            break;
        }
    }
    //printf("i before highThreshold is %d\n", i);
    highThreshold = i;
    lowThreshold = 0.35*highThreshold;
    //printf("High Threshold is %lf\nLow Threshold is %lf\n", highThreshold, lowThreshold);


    /**PART3**/
    for (i=0; i<256; i++)
    {
        for (j=0; j<256; j++)
        {
            if(peaks[i][j] == 255)
            {
                if(ival[i][j] > highThreshold)
                {
                    peaks[i][j] = 0;
                    finalEdges[i][j] = 255;
                }
                else if(ival[i][j] < lowThreshold)
                {
                    peaks[i][j] = 0;
                    finalEdges[i][j] = 0;
                }
            }
        }
    }
    moretodo = 1;
    while(moretodo == 1)
    {
        moretodo = 0;
        for (i=0; i<256; i++)
        {
            for (j=0; j<256; j++)
            {
                if(peaks[i][j] == 255)
                {
                    for (k=-1; k<=1; k++)
                    {
                        for (l=-1; l<=1; l++)
                        {
                            if(finalEdges[i+k][j+l] ==255)
                            {
                                peaks[i][j] = 0;
                                finalEdges[i][j] = 255;
                                moretodo = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    for (i=0; i<256; i++)
    {
        for (j=0; j<256; j++)
        {
            fprintf(fo3,"%c",(char)((int)(finalEdges[i][j])));
        }
    }

    fclose(fp1);
    fclose(fo1);
    fclose(fo2);
    fclose(fo3);
    return 0;
}


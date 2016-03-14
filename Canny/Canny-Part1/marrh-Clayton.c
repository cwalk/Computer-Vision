#include <stdio.h>                  /*  Marr-Hildreth.c  (or marrh.c) */
#include <math.h>
#define  PICSIZE 256
#define  MAXMASK 100

         int    pic[PICSIZE][PICSIZE];
         double outpic1[PICSIZE][PICSIZE];
         double outpic2[PICSIZE][PICSIZE];
         int    edgeflag[PICSIZE][PICSIZE];
         double mask[MAXMASK][MAXMASK];
         double conv[PICSIZE][PICSIZE];

int main(argc,argv)
int argc;
char **argv;
{
        int     i,j,p,q,s,t,mr,centx,centy;
        double  maskval,sum1,sum2,sig,maxival,minival,maxval,ZEROTOL;
        FILE    *fo1, *fo2, *fo3, *fp1, *fopen();
        /*char    *foobar;

        argc--; argv++;
        foobar = *argv;
        fp1=fopen(foobar,"rb");

        argc--; argv++;
        foobar = *argv;
        fo1=fopen(foobar,"wb");

        argc--; argv++;
        foobar = *argv;
        fo2=fopen(foobar,"wb");

        argc--; argv++;
        foobar = *argv;
        sig = atof(foobar);

        argc--; argv++;
        foobar = *argv;
        ZEROTOL = atof(foobar);
    
        printf("What is your low Threshold?\n");
        scanf("%lf", &lowThreshold);
        printf("What is your high Threshold?\n");
        scanf("%lf", &highThreshold);*/
    
        fp1 = fopen("garb34.pgm", "rb");
        fo1 = fopen("Test1out.pgm", "wb");
        fo2 = fopen("Test2out.pgm", "wb");
        fo3 = fopen("Test3out.pgm", "wb");
    
        fprintf(fo1,"P5\n256 256\n255\n");  /* Print out the .pgm header */
        fprintf(fo2,"P5\n256 256\n255\n");
        fprintf(fo3,"P5\n256 256\n255\n");

        mr = (int)(sig * 3);
        centx = (MAXMASK / 2);
        centy = (MAXMASK / 2);

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
                   sum1 += pic[i+p][j+q] * mask[p+centy][q+centx];
                   sum2 += pic[i+p][j+q] * mask[p+centy][q+centx];
                }
             }
              outpic1[i][j] = sum1;
              outpic1[i][j] = sum2;
             //conv[i][j] = sum;
          }
        }

    
    //Bring in Sqrt of squares code from Sobel.c
    maxival = 0;
    for (i=mr; i<256-mr; i++)
    {
        for (j=mr; j<256-mr; j++)
        {
            ival[i][j]=sqrt((double)((outpic1[i][j]*outpic1[i][j]) +
                                     (outpic2[i][j]*outpic2[i][j])));
            if (ival[i][j] > maxival)
                maxival = ival[i][j];
        }
    }
    
    //EVERYTHING BELOW THIS IS DELETED!
        /*maxval  = 0;
        maxival = 0;
        minival = 255;

        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
             if (outpic1[i][j] > maxival)
                maxival = outpic1[i][j];
             if (outpic1[i][j] < minival)
                minival = outpic1[i][j];
           }
        }
        if (fabs(maxival) > fabs(minival))
           maxval = fabs(maxival);
        else
           maxval = fabs(minival);

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
          {
             outpic1[i][j] = ((((outpic1[i][j]) / maxval) + 1) * 127);
             fprintf(fo1,"%c",(char)((int)(outpic1[i][j])));
          }
        }

        for (i=mr;i<=255-mr;i++)
        {  for (j=mr;j<=255-mr;j++)
           {
                         outpic2[i][j] = 0;
             if (conv[i][j] > ZEROTOL)
             {
               for (p=-1;p<=1;p++)
               {
                 for (q=-1;q<=1;q++)
                 {
                   if (conv[i+p][j+q] < -ZEROTOL)
                   {
                     outpic2[i][j] = 255;
                   }
                 }
               }
             }
             else if ((fabs)(conv[i][j]) < ZEROTOL)
             {
                     if (((conv[i+1][j] > ZEROTOL) &&
                          (conv[i-1][j] < -ZEROTOL))   ||
                         ((conv[i+1][j] < -ZEROTOL) &&
                          (conv[i-1][j] > ZEROTOL)))
                     {
                       outpic2[i][j] = 255;
                     }
                     else if (((conv[i][j+1] > ZEROTOL) &&
                               (conv[i][j-1] < -ZEROTOL))   ||
                              ((conv[i][j+1] < -ZEROTOL) &&
                               (conv[i][j-1] > ZEROTOL)))
                     {
                       outpic2[i][j] = 255;
                     }
                     else if (((conv[i+1][j+1] > ZEROTOL) &&
                               (conv[i-1][j-1] < -ZEROTOL))   ||
                              ((conv[i+1][j+1] < -ZEROTOL) &&
                               (conv[i-1][j-1] > ZEROTOL)))
                     {
                       outpic2[i][j] = 255;
                     }
                     else if (((conv[i+1][j-1] > ZEROTOL) &&
                               (conv[i-1][j+1] < -ZEROTOL))   ||
                              ((conv[i+1][j-1] < -ZEROTOL) &&
                               (conv[i-1][j+1] > ZEROTOL)))
                     {
                       outpic2[i][j] = 255;
                     }
             }
           }
        }*/

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
          {  if (outpic2[i][j] == 255) outpic2[i][j]=0;
             else outpic2[i][j]=255;
             fprintf(fo2,"%c",(char)((int)(outpic2[i][j])));
          }
        }
    fclose(fp1);
    fclose(fo1);
    fclose(fo2);
    fclose(fo3);
    return 0;
}


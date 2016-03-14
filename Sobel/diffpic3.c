#include <stdio.h>
#include <stdlib.h>

       /* This program reads in two pictures, and as it is doing so, it
          computes the difference between pixels at the same location,
          and write a new picture composed of these differences */

       /* char pic[256][256]; This statement would be useful for storing pic */

int main(argc,argv)
int argc;
char **argv;
{
        int i,j,ci1,ci2,cdif;
        FILE *fo1, *fp2,*fp1, *fopen();
        char *foobar;

        char inputFilename[20], inputFilename2[20], outputFilename[20];
        printf("What is the name of your input file?\n");
        scanf("%s", inputFilename);
        printf("What is the name of your 2nd input file?\n");
        scanf("%s", inputFilename2);
        printf("What is the name of your output file?\n");
        scanf("%s", outputFilename);

        fp1 = fopen(inputFilename, "rb");
        fp2 = fopen(inputFilename2, "rb");
        fo1 = fopen(outputFilename, "wb");

        fprintf(fo1,"P5\n256 256\n255\n");  /* Print out the .pgm header */

///* Open file 1 for reading */
//    argc--; argv++;
//    foobar = *argv;
//    fp1=fopen(foobar,"rb");
//
///* Open file 1 for reading */
//    argc--; argv++;
//    foobar = *argv;
//    fp2=fopen(foobar,"rb");
//
///* Open file 1 for writing */
//    argc--; argv++;
//    foobar = *argv;
//    fo1=fopen(foobar,"wb");

    //fprintf(fo1,"P5\n256 256\n255\n");  /* Print out the .pgm header */

        for (i=0;i<256;i++)             /* Pictures are 256 x 256 size */
        { for (j=0;j<256;j++)
                {
                  ci1  =  getc (fp1);   /* read one pixel from Pic 1 */

                  ci2  =  getc (fp2);   /* read one pixel from Pic 2 */


                  cdif = abs(ci2 - ci1);     /* Take difference */

                  if (cdif>255)cdif=255;

                  fprintf(fo1,"%c",(char)cdif);  /* print the output Pic */

                }
        }
}


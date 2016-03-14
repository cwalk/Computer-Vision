#include <stdio.h>

       /* char pic[256][256]; */
main(argc,argv)
int argc;
char **argv;
{ 
        int i,j,ci1,ci2,cdif;
        FILE *fo1, *fp2,*fp1, *fopen();
        char *foobar;

    argc--; argv++;
    foobar = *argv;
    fp1=fopen(foobar,"rb");

    argc--; argv++;
    foobar = *argv;
    fp2=fopen(foobar,"rb");

    argc--; argv++;
    foobar = *argv;
    fo1=fopen(foobar,"wb");

        /* printf("\nfile name for input:");
        scanf("%s",pic1);
        if((fp1=fopen(pic1,"r"))==NULL) printf("can't open input file\n");
        */
        for (i=0;i<256;i++) 
        { for (j=0;j<256;j++)
                {  
                  ci1  =  getc (fp1);
                  ci1  &= 0377;     
                  ci2  =  getc (fp2);
                  ci2  &= 0377;

                  cdif = abs(ci2 - ci1);
                   if (cdif>255)cdif=255;
                  printf("%c",(char)cdif);
                  if (cdif>0)  
                     { fprintf(fo1, "i,j,dif,orig=%d,%d,%d,%d\n",i,j,cdif,ci1);

                     }
                }
        }
}            


## Introduction

Senior level Computer Vision course from UCF. Includes Sobel and Canny code written in C.

## Usage

Download the repository: `git clone https://github.com/cwalk/Computer-Vision`

Navigate into the project directory: `cd Computer-Vision/`

##Sobel

To run Sobel.c, make sure you have "face05.pgm" input file inside the same directory as the C file (or the home directory for OSX). 

To compile the C file, try: `$ gcc -o Sobel Sobel.c`

To execute: `$ ./Sobel`

You should get 3 output files, named: "HW1Magout.pgm", "HW1LOWout.pgm", and "HW1HIGHout.pgm". These represent the Magnitude, Low threshold, and High threshold respectively for Sobel. These can all be found in the Sample input and Sample output folders inside Sobel/.

An assignment description can be read, titled "assign1.001.pdf"

##Canny

To run Canny (marrh.c), make sure you have "garb34.pgm" input file inside the same directory as the C file (or the home directory for OSX). 

To compile the C file, try: `$ gcc -o Canny marrh.c`

To execute: `$ ./Canny`

You should get 3 output files, named: "garb34mag.pgm", "garb34peaks.pgm", and "garb34final.pgm". These represent the Magnitude, Peaks, and Final results respectively for Canny. These can all be found in the Sample input and Sample output folders inside Canny/.

An assignment description can be read, titled "assignCanny1.docx"

## YouTube

YouTube: https://www.youtube.com/watch?v=i3gTDSSlA_4

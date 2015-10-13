#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "main.h"
#include "matrix.h"

int main (int argc, char* argv[])
{
  IplImage* img = NULL;
  const char* window_title = "";

  if (argc < 2)
  {
    fprintf (stderr, "usage: %s IMAGE\n", argv[0]);
    return EXIT_FAILURE;
  }
  img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);

  if (img == NULL)
  {
    fprintf (stderr, "couldn't open image file: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  cvNamedWindow (window_title, CV_WINDOW_AUTOSIZE);
  cvShowImage (window_title, img);

/*
 fprintf (stderr, "test 1 \n");
 struct matrix test = zeros(2,2);
 print_matrix(test);




fprintf (stderr, "test 2 \n");
struct matrix test2;
unsigned int a = 1;
unsigned int* pa = &a;
unsigned int** ppa = &pa;
test2.values = ppa;
print_matrix(test2);


fprintf (stderr, "test 3 \n");
unsigned int * videoFrame = (unsigned int*) malloc (2*2* sizeof(unsigned int));
videoFrame[0] =1;
videoFrame[1] =2;
videoFrame[2] =3;
videoFrame[3] =4;
struct matrix test3 = init_matrix(2,2,videoFrame);
print_matrix(test3);
printf ("\n");



fprintf (stderr, "test 4 \n");
struct matrix test4 = init_matrix(2,2,(unsigned int*)img->imageData);
print_matrix(test4);
printf ("\n");



fprintf (stderr, "test mutiplication \n");
coef_matrix(test3,4);
print_matrix(test3);
printf ("\n");


fprintf (stderr, "test addition \n");
add_matrix(test3,test,test);
print_matrix(test);
printf ("\n");*/

printf ( "test mult \n");
printf ( "ma \n");
unsigned int * A = (unsigned int*) malloc (2*3* sizeof(unsigned int));
A[0] =1;
A[1] =2;
A[2] =0;
A[3] =4;
A[4] =3;
A[5] =1;
struct matrix MA = init_matrix(2,3,A);
print_matrix(MA);
printf ("\n");


printf ("mb \n");
unsigned int * B = (unsigned int*) malloc (3*2* sizeof(unsigned int));
B[0] =5;
B[1] =1;
B[2] =2;
B[3] =3;
B[4] =3;
B[5] =4;
struct matrix MB = init_matrix(3,2,B);
print_matrix(MB);
printf ( "\n");


printf ( "ans \n");
struct matrix ans = mult_matrix(MA,MB);
print_matrix(ans);
printf ( "\n");

  cvWaitKey(0);
  cvDestroyAllWindows();
  cvReleaseImage(&img);



  return EXIT_SUCCESS;
}

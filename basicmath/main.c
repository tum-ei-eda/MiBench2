#ifndef FISOC
#include <stdio.h>
#endif

#include "snipmath.h"
#include <math.h>
#include "../bareBench.h"

/* The printf's may be removed to isolate just the math calculations */

int main(void)
{
  double X;
  int i;
  unsigned long long l = 0x3fed0169L;
  struct int_sqrt q;
  double result;

 
  
  
  
  #ifndef FISOC
  printf("********* INTEGER SQR ROOTS ***********\n\r");
  #endif
  result = 0.0;
  /* perform some integer square roots */
  for (i = 0; i < 250; ++i)
    {
      usqrt(i, &q);
			// remainder differs on some machines
     // printf("sqrt(%3d) = %2d, remainder = %2d\n\r",
//     printf("sqrt(%3d) = %2d\n\r",
//	     i, q.sqrt);
       result += q.sqrt;
    }
  usqrt(l, &q);
  //printf("\n\rsqrt(%lX) = %X, remainder = %X\n\r", l, q.sqrt, q.frac);
//  printf("\n\rsqrt(%llX) = %X\n\r", l, q.sqrt);
  result += q.sqrt;
  
  #ifndef FISOC
  printf("result: %f\n", result);
  #else
  *(volatile double *)(0x180000) = result;
  #endif  


  #ifndef FISOC
  printf("********* ANGLE CONVERSION ***********\n\r");
  #endif
  result = 0.0;
  /* convert some rads to degrees */
  for (X = 0.0; X <= 360.0; X += 15.0)
/*    printf("%3.0f degrees = %.12f radians\n\r", X, deg2rad(X));*/
/*  printf("\n\r");*/
    result += deg2rad(X);
    
    
    
  for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 5))
/*    printf("%.12f radians = %3.0f degrees\n\r", X, rad2deg(X));*/
    result += rad2deg(X);
  
  #ifndef FISOC
  printf("result: %f\n", result);
  #else
  *(volatile double *)(0x180008) = result;
  #endif
  
  return 0;
}

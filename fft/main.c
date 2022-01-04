
#ifndef FISOC
#include <stdio.h>
#endif
#include <math.h>
#include <stdlib.h>
#include "../bareBench.h"
#include "fourier.h"

int invfft = 0;
unsigned MAXSIZE;  // small 4096, 8192 inverse, 512 for memory-limited systems
unsigned MAXWAVES = 1;  // large has 8
static float realin[1024];
static float imagin[1024];
static float realout[1024];
static float imagout[1024];
static float Coeff[16];
static float Amp[16];

int old_main();

// main for benchmark purposes that does fft and inverse fft
int main() {
  MAXSIZE = 16;
  old_main();

  return 0;
}

int old_main() {
  unsigned i, j;
  float *RealIn;
  float *ImagIn;
  float *RealOut;
  float *ImagOut;
  float *coeff;
  float *amp;

  srand(1);

  /* RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
   ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
   RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
   ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
   coeff=(float*)malloc(sizeof(float)*MAXWAVES);
   amp=(float*)malloc(sizeof(float)*MAXWAVES);
  */

  // Statically allocate
  RealIn = realin;
  ImagIn = imagin;
  RealOut = realout;
  ImagOut = imagout;
  coeff = Coeff;
  amp = Amp;

  /* Makes MAXWAVES waves of random amplitude and period */
  for (i = 0; i < MAXWAVES; i++) {
    coeff[i] = rand() % 1000;
    amp[i] = rand() % 1000;
  }

  for (i = 0; i < MAXSIZE; i++) {
    /*   RealIn[i]=rand();*/
    RealIn[i] = 0;
    for (j = 0; j < MAXWAVES; j++) {
      /* randomly select sin or cos */
      if (rand() % 2) {
        RealIn[i] += coeff[j] * cos(amp[j] * i);
      } else {
        RealIn[i] += coeff[j] * sin(amp[j] * i);
      }
      ImagIn[i] = 0;
    }
  }

  /* regular*/
  fft_float(MAXSIZE, invfft, RealIn, ImagIn, RealOut, ImagOut);

  float result = 0.0;

#ifndef FISOC
  for (i = 0; i < MAXSIZE; i++) result += RealOut[i];

  for (i = 0; i < MAXSIZE; i++) result -= ImagOut[i];

  printf("%f\n", result);
#else
  for (i = 0; i < MAXSIZE; i++) {
    result += RealOut[i];
  }
  for (i = 0; i < MAXSIZE; i++) {
    result -= ImagOut[i];
  }

  *(volatile float *)(0x180000) = result;
#endif

  /* free(RealIn);
   free(ImagIn);
   free(RealOut);
   free(ImagOut);
   free(coeff);
   free(amp);
  */
  return 0;
}

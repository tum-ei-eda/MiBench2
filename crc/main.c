/**********************************************************************
 *
 * Filename:    main.c
 *
 * Description: A simple test program for the CRC implementations.
 *
 * Notes:       To test a different CRC standard, modify crc.h.
 *
 *
 * Copyright (c) 2000 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/
#include "../bareBench.h"
#ifndef FISOC
#include <stdio.h>
#endif
#include <string.h>

#include "crc.h"

int main(void) {
  unsigned char test[] = "123456789";

#ifndef FISOC
  /*
   * Compute the CRC of the test message, slowly.
   */
  printf("The crcSlow() of \"123456789\" is 0x%X\n",
         crcSlow(test, strlen(test)));
#else
  *(volatile int *)(0xe000) = (int)crcSlow(test, strlen(test));
#endif

  /*
   * Compute the CRC of the test message, more efficiently.
   */
  crcInit();

#ifndef FISOC
  printf("The crcFast() of \"123456789\" is 0x%X\n",
         crcFast(test, strlen(test)));
#else
  *(volatile int *)(0xe004) = (int)crcFast(test, strlen(test));
#endif

  return 0;
} /* main() */

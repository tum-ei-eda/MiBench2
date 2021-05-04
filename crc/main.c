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

static unsigned addr = 0x180000;

int main(void) {
  unsigned char test[] = "123456789";

#ifndef FISOC
  /*
   * Compute the CRC of the test message, slowly.
   */
  printf("The crcSlow() of \"123456789\" is 0x%X\n",
         crcSlow(test, strlen(test)));
#else
  *(volatile int *)(addr) = (int)crcSlow(test, strlen(test));
  addr += 4;
#endif

  /*
   * Compute the CRC of the test message, more efficiently.
   */
  crcInit();

#ifndef FISOC
  printf("The crcFast() of \"123456789\" is 0x%X\n",
         crcFast(test, strlen(test)));
#else
  *(volatile int *)(addr) = (int)crcFast(test, strlen(test));
  addr += 4;
#endif

  return 0;
} /* main() */

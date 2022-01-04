/*
blowfish_test.c:  Test file for blowfish.c

Copyright (C) 1997 by Paul Kocher

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef FISOC
#include <stdio.h>
#endif
#include "../bareBench.h"
#include "blowfish.h"
#include "input.h"

//#define USE_PRINTF

unsigned char KEY[] = "1234567890abcdeffedcba0987654321";
BLOWFISH_CTX ctx;

int main(void) {
  unsigned long L = 1, R = 2;

#ifndef FISOC
#ifdef USE_PRINTF
  printf("Encrypt message\n");
#endif
#endif
  Blowfish_Init(&ctx, KEY, sizeof(KEY));

  unsigned long *plaintextPtr = (unsigned long *)test_data;
  long result = 0;
  while (plaintextPtr < (unsigned long *)(test_data + sizeof(test_data))) {
    Blowfish_Encrypt(&ctx, &plaintextPtr[0], &plaintextPtr[1]);
    //      printf("%08lX %08lX\n", plaintextPtr[0], plaintextPtr[1]);
    result ^= plaintextPtr[0];
    result ^= plaintextPtr[1];
    plaintextPtr += 2;
  }
#ifndef FISOC
#ifdef USE_PRINTF
  printf("%08lx\n", result);
#else
  *(volatile long *)(0x800000) = result;
#endif
#else
  *(volatile long *)(0x180000) = result;
#endif

#ifndef FISOC
#ifdef USE_PRINTF
  printf("Decrypt message\n");
#endif
#endif
  Blowfish_Init(&ctx, KEY, sizeof(KEY));

  result = 0;
  plaintextPtr = (unsigned long *)test_data;
  while (plaintextPtr < (unsigned long *)(test_data + sizeof(test_data))) {
    Blowfish_Decrypt(&ctx, &plaintextPtr[0], &plaintextPtr[1]);
    //      printf("%08lX %08lX\n", plaintextPtr[0], plaintextPtr[1]);
    result ^= plaintextPtr[0];
    result ^= plaintextPtr[1];
    plaintextPtr += 2;
  }
#ifndef FISOC
#ifdef USE_PRINTF
  printf("%08lx\n", result);
#else
  *(volatile long *)(0x800004) = result;
#endif
#else
  *(volatile long *)(0x180004) = result;
#endif

  return 0;
}

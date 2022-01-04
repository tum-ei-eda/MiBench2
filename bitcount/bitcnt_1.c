/* +++Date last modified: 05-Jul-1997 */

/*
**  Bit counter by Ratko Tomic
*/

#include "bitops.h"

int CDECL bit_count(long x)
{
        int n = 0;
/*
** The loop will execute once for each bit of x set, this is in average
** twice as fast as the shift/test method.
*/
        if (x) do
              n++;
        while (0 != (x = x&(x-1))) ;
        return(n);
}

#define TEST

#ifdef TEST

#include <stdlib.h>


int main()
{
  unsigned iterations = 100;
  long n = 0xDEADBEEF;
  
  int result = 0;
  for (int i=0; i<iterations; ++i) {
    result += bit_count(n * i);
  }
  
  #ifndef FISOC
  printf("result: %x\n", result);
  #else
  *(volatile int *)(0x180000) = result;
  #endif
  return 0;
}


#endif /* TEST */

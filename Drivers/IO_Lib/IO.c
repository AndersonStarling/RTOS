#include "IO.h"
#include "ITM_Print.h"

/* Override _write in syscalls.c to print string through SWD */

#if 0
int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    ITM_SendChar(*ptr++);
  }

  return len;
}
#endif













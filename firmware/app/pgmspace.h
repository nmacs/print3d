

#ifndef _PGMSPACE_H
#define _PGMSPACE_H

#include <stdint.h>
 
#define PGM_P   char *
#define PSTR(str) str

#define pgm_read_byte(p) (*p)
#define pgm_read_word(p) (*p)

#endif


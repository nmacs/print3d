

#ifndef _EEPROM_H
#define _EEPROM_H
 
#define EEMEM

#include <stdint.h>
 
uint16_t eeprom_read_word (const uint16_t *__p) ;
uint32_t eeprom_read_dword (const uint32_t *__p) ;

void eeprom_write_word (uint16_t *__p, uint16_t __value);
void eeprom_write_dword (uint32_t *__p, uint32_t __value);

#endif
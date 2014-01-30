#ifndef MAX31855_H
#define MAX31855_H

#include "ch.h"
#include "hal.h"

struct max31855_plat_data {
  SPIDriver *bus;
  const SPIConfig *config;
};

#endif

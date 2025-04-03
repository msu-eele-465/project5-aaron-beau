#ifndef adc_control_H
#define adc_control_H

#include "src/adc_control.h"
#include <msp430.h>
#include <stdint.h>

// Function prototype
void init_moving_average();
float add_temperature_value(float new_temp);
void set_moving_average_size(int new_n);
void Convert_Float(float value);
#endif

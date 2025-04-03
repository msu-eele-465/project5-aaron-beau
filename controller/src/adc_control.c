/*----------------------------------------------------------------------------------
Beau Coburn & Aaron Foster
EELE 465
2/25/25
Project 3: Keypad LED Pattersn
Description:  




-------------------------------------------------------------------------------------*/
#include <msp430.h> 
#include "adc_control.h"
#include <stdint.h>

// Initializations
    int16_t temp_values[9];  // Circular buffer to store the last n temperature values
    int n = 3;                   // Default size of the moving average window (n = 3)
    int16_t sum = 0;             // Running sum of the last n temperature values
    int index = 0;               // Index for the circular buffer
    int i;




 void init_moving_average() {   
    for (i = 0; i < 9; i++) {
        temp_values[i] = 0;  // Initialize the buffer to 0
    }
    sum=0;
    index=0;
 }
float add_temperature_value(float new_temp){
    // Subtract the value that is going to be replaced from the sum
    sum -= temp_values[index];
    // Add the new value to the sum
    sum += new_temp;
    // Move the index to the next position in the buffer (circular behavior)
    index = (index + 1) % n;
    // Calculate and return the moving average
    return (float)sum / n;
}

void set_moving_average_size(int new_n){

    n=new_n;                // Set new sample #

    init_moving_average();  //reinitialize the buffer
}

void convert_and_send_float(float value) {
    int Data_Cnt = 0;              // Used for multiple bytes sent
    int i=0;
    int whole = (int)value;        // Get whole number part
    int decimal = (int)((value - whole) * 10);// Get first decimal digit
    char temp_packet[] = {0x0C, whole, decimal};
   
  }


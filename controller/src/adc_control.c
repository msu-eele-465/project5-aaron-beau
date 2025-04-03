/*----------------------------------------------------------------------------------
Beau Coburn & Aaron Foster
EELE 465
2/25/25
Project 3: Keypad LED Pattersn
Description:  




-------------------------------------------------------------------------------------*/
#include <msp430.h> 
#include "adc_control.h"
#include "intrinsics.h"
#include <stdint.h>

// Initializations
    int16_t temp_values[9];  // Circular buffer to store the last n temperature values
    int n = 3;                   // Default size of the moving average window (n = 3)
    int16_t sum = 0;             // Running sum of the last n temperature values
    int index = 0;               // Index for the circular buffer
    int i;



void ADC_init(){

    P5SEL1 |= BIT0;  // Set P5.0 as ADC input
    P5SEL0 |= BIT0;

    ADCCTL0 &= ~ADCSHT;         //Clear ADCSHT
    ADCCTL0 |=  ADCSHT_2;       //Conversion Cycles = 16
    ADCCTL0 |= ADCON;           //turn ADC ON

    ADCCTL1 |= ADCSHP;          //sample signal source = sampling timer

    ADCCTL2 &= ~ADCRES;         //Clear ADCRES
    ADCCTL2 |= ADCRES_2;        // Resoultion  = 12 bit

    ADCMCTL0 |= ADCINCH_8;      //ADC INPUT Channel = A8
    __enable_interrupt();

    

}
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

void Convert_Float(float value) {
    int whole = (int)value;              // Get whole number part
    int decimal = (int)((value - whole) * 10);  // Get first decimal digit
}


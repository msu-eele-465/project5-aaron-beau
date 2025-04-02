#include "src/controller_control.h"
#include "intrinsics.h"
#include "sys/cdefs.h"

void controller_init(){
//----------------------------Pin Initialization--------------------------------
//--RGB LED (1=red, 2=green, 3=blue, 4=yellow)
    P4DIR |= BIT0;                              // Configure red part
    P4OUT &= ~BIT0;

    P2DIR |= BIT2;                              // Configure green part
    P2OUT &= ~BIT2;

    P2DIR |= BIT0;                              // Configure blue part
    P2OUT &= ~BIT0;

//--Columns
    P3DIR |= BIT4 | BIT5 | BIT6 | BIT7;        // Set columns as outputs
    P3OUT &= ~(BIT4 | BIT5 | BIT6 | BIT7);     // Initially set all low

//--Rows
    P3DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3);
    P3REN |= BIT0 | BIT1 | BIT2 | BIT3;
    P3OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);

    P6DIR |= BIT6;                             // Set P16 to output direction
    P6OUT |= BIT6;      // Clear P16 output latch for a defined power-on state

//----------------------------ADC Initialization------------------------------

    ADCCTL0 |= ADCSHT_2 | ADCON;        // Sample and hold time, ADC ON
    ADCCTL1 |= ADCSHP;                  // Use sampling timer
    ADCCTL2 |= ADCRES_2;                 // 12-bit resolution
    ADCMCTL0 |= ADCINCH_8 | ADCSREF_0;  // Correct definition for A8 (P5.0)
    ADCIE |= ADCIE0;                     // Enable ADC interrupt

    P5SEL1 |= BIT0;  // Set P5.0 as ADC input
    P5SEL0 |= BIT0;
}





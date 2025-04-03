/*-----------------------------------------------------------------------------
* Project 5: Reading an Analog Temperature Sensor with an ADC
* Aaron Foster & Beau Coburn
* EELE 465
* 4/3/25
* 
* Main file for the controller msp. receives
* a character from the keypad to unlock. Later receives
* characters from the keypad and transmits commands to 
* the peripherals. Also reads LM19 temperature sensor and sends output to 
* LCD microcontroller
*///----------------------------------------------------------------------------




#include <msp430.h>
#include <stdint.h>
#include "intrinsics.h"
#include "msp430fr2355.h"
#include "src/controller_control.h"
#include "src/keypad_scan.h"
#include "src/rgb_control.h"
#include "src/controller_control.h"
#include "src/adc_control.h"


//---------------------- Variables ---------------------------------------------
int locked = 1;                                 // Locked Boolean
int relock = 0;                                 // Toggle to relock
volatile uint8_t *txData;                       // Pointer to data buffer
int SetOnce=1;                                  // Variable to trigger Tx once
//---------------------- i2c Variables -----------------------------------------
char Packet[] = {0x00};                         // Tx Packet
int Data_Cnt = 0;                               // Used for multiple bytes sent
int i;                                          // Delay counter variable
//---------------------- ADC Variables -----------------------------------------
volatile unsigned int adc_value;                // Stores raw ADC reading (0-4095)
volatile float temperature_C;                   // Stores calculated temperature in Celsius

//------------------------------------------------------------------------------
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer


controller_init();
controller_i2c_init();
__bis_SR_register(GIE);  // Enable global interrupts

    PM5CTL0 &= ~LOCKLPM5;  // Disable Low power mode
//------------------------ End Initialization ----------------------------------

/* 
* Main loop continually scans keypad and jumps to different while(locked) loops 
* Depending on the button pressed
*/
    while (1) {



//--Locked                                 // While Locked variable is set  
        while (locked == 1) {              // Set led bar off and scan keypad
            if(SetOnce==1){
                Packet[0]=0x00;
                SetOnce=0;
                UCB1CTLW0 |= UCTXSTT;
            }

            rgb_control(1);
            locked = unlock_keypad();
        }

//--Unlocked                               // When locked variable is not set
        while (locked == 0) {              // continually scan keypad and tx
            rgb_control(3);                // Based on button press
            relock = led_pattern();

/* Set packet for tx, transmit, briefly change LED to green */

            switch(relock){
                case 0: UCB1I2CSA = 0x0069; Packet[0]=0x00; SetOnce=1; UCB1CTLW0 |= UCTXSTT; 
	                    for(i=0; i<100; i++){} UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                        rgb_control(2); __delay_cycles(500000); break;

                case 1: UCB1I2CSA = 0x0069; Packet[0]=0x01; SetOnce=1; UCB1CTLW0 |= UCTXSTT;
                        for(i=0; i<100; i++){} UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                        rgb_control(2); __delay_cycles(500000); break;

                case 2: UCB1I2CSA = 0x0069; Packet[0]=0x02; SetOnce=1; UCB1CTLW0 |= UCTXSTT;
                        for(i=0; i<100; i++){} UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT;
                        rgb_control(2); __delay_cycles(500000); break;
                        
                case 3: UCB1I2CSA = 0x0069; Packet[0]=0x03; SetOnce=1; UCB1CTLW0 |= UCTXSTT;
                        for(i=0; i<100; i++){} UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                        rgb_control(2); __delay_cycles(500000); break;

                case 4: UCB1I2CSA = 0x0069; Packet[0]=0x04; SetOnce=1; UCB1CTLW0 |= UCTXSTT;
                        for(i=0; i<100; i++){} UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                        rgb_control(2); __delay_cycles(500000); break;

                case 5: UCB1I2CSA = 0x00E; Packet[0] = 0x5; UCB1CTLW0 |= UCTXSTT;
                        rgb_control(2); __delay_cycles(500000); break;

                case 6: UCB1I2CSA = 0x00E; Packet[0] = 0x6; UCB1CTLW0 |= UCTXSTT;
                        rgb_control(2); __delay_cycles(500000); break;

                case 7: UCB1I2CSA = 0x00E; Packet[0] = 0x7; UCB1CTLW0 |= UCTXSTT;
                        rgb_control(2); __delay_cycles(500000); break;

                case 8: UCB1I2CSA = 0x00E; Packet[0] = 0x8; UCB1CTLW0 |= UCTXSTT;
                        rgb_control(2); __delay_cycles(500000); break;                

                case 9:  Packet[0]=0x9; SetOnce=1;
                          UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                         rgb_control(2); __delay_cycles(500000); break;

                case 0xA: Packet[0]=0xA; SetOnce=1; UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                         rgb_control(2); __delay_cycles(500000); break;

                case 0xB: Packet[0]=0xB; SetOnce=1; UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                         rgb_control(2); __delay_cycles(500000); break;

                case 0xC:  Packet[0]=0xC; SetOnce=1;
                          UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                         rgb_control(2); __delay_cycles(500000); break;

                case 0xD: UCB1I2CSA = 0x0069; Packet[0]=0xD; locked=1; SetOnce=1; UCB1CTLW0 |= UCTXSTT; 
                         for(i=0; i<100; i++){} UCB1I2CSA = 0x00E; UCB1CTLW0 |= UCTXSTT; 
                         rgb_control(2); __delay_cycles(500000); break;

                default: 
                    break;
            }
        }
    }

    return 0;
}
//------------------Interrupt Service Routines----------------------------------
/* ISR for I2C, iterates through Packet for each variable to be sent*/
#pragma vector = USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void) {
    if(Data_Cnt == (sizeof(Packet)-1)) {
        UCB1TXBUF = Packet[Data_Cnt];
        Data_Cnt = 0;
    }else{
        UCB1TXBUF = Packet[Data_Cnt];
        Data_Cnt++;
    }
}
/*ISR to trigger ADC read every 0.5s*/
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_OVERFLOW(void)
{    
         ADCCTL0 |= ADCENC | ADCSC;            // Enable temp read
         TB0CTL &= ~TBIFG;                     // Clear interrupt flag

}
/*IRS for reading ADC temperature*/
#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void)
{
    adc_value = ADCMEM0;  // Read ADC result

    // Calibration factor to map 495 to room temp
    float calibration_factor = 20.0 / 495.0;

    temperature_C = adc_value * calibration_factor; // Scale ADC value to C
    add_temperature_value(temperature_C);

}

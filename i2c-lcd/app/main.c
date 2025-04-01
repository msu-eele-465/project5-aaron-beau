
#include <msp430.h>
#include "lcd_control.h"

const char widnow_size[2] = {0b01001110, 0b00111101};
const char set_window[15] = {0b01110011, 0b01100101, 0b01110100, 0b00010000, 0b01110111, 0b01101001, 0b01101110, 0b01100100, 0b01101111, 0b01110111, 0b00010000, 0b01110011, 0b01101001, 0b01111010, 0b01100101};
const char set_pattern[11] = {0b01110011, 0b01100101, 0b01110100, 0b00010000, 0b01110000, 0b01100001, 0b01110100, 0b01110100, 0b01100101, 0b01110010, 0b01101110};
const char pattern_static[6] = {0b01110011, 0b01110100, 0b01100001, 0b01110100, 0b01101001, 0b01100011};
const char pattern_toggle[6] = {0b01110100, 0b01101111, 0b01100111, 0b01100111, 0b01101100, 0b01100101};
const char pattern_up_counter[10] = {0b01110101, 0b01110000, 0b00010000, 0b01100011, 0b01101111, 0b01110101, 0b01101110, 0b01110100, 0b01100101, 0b01110010};
const char pattern_in_and_out[10] = {0b01101001, 0b01101110, 0b00010000, 0b01100001, 0b01101110, 0b01100100, 0b00010000, 0b01101111, 0b01110101, 0b01110100};
const char n_size[10] = {0b00110001, 0b00110001, 0b00110010, 0b00110011, 0b00110100, 0b00110101, 0b00110110, 0b00110111, 0b00111000, 0b00111001};              
                        
unsigned int i;
int status;
int RXDATA = 0;
int pattern_set = 0;
int window_size_set = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    P1OUT &= ~BIT1;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT1;                          // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    LCD_init();
    LCD_setup();
    while(1)
    {
        
        while(pattern_set == 0){
        switch(RXDATA){
            case 0:     break;

            case 0x1:   LCD_Clear();
                        for(i = 0; i < 6; i++){
                            LCD_write(pattern_static[i]);
                        }
                        RXDATA = 0;
                        break;

            case 0x2:   LCD_Clear();
                        for(i = 0; i < 6; i++){
                            LCD_write(pattern_toggle[i]);
                        }
                        RXDATA = 0;
                        break;
            
            case 0x3:   LCD_Clear();
                        for(i = 0; i < 10; i++){
                            LCD_write(pattern_up_counter[i]);
                        }
                        RXDATA = 0;
                        break;

            case 0x4:   LCD_Clear();
                        for(i = 0; i < 10; i++){
                            LCD_write(pattern_up_counter[i]);
                        }
                        RXDATA = 0;
                        break;
                    
            default:    break;
            } 
        }  
        while(window_size_set == 0){
            for(i = 0; i < 2; i++){
                LCD_write(window_size[i]);
            }
            LCD_write(n_size[RXDATA]);
            window_size_set =1;
            
        }         

        

        P1OUT ^= BIT1;                      // Toggle P1.0 using exclusive-OR
        __delay_cycles(100000);             // Delay for 100000*(1/MCLK)=0.1s
    }
}
//--------- I2C Receive ISR (Handles Incoming Data) ---------------------------
/* ISR triggers upon start condition from I2C bus and receives sent data from
 * master 
 */
#pragma vector = EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_ISR(void)
{
    switch (__even_in_range(UCB0IV, 0x1E)) {
        case 0x16:  // UCRXIFG0: Byte received
            RXDATA = UCB0RXBUF;  // Read received byte
            status=1;
            break;

        case 0x12:  // UCSTPIFG: Stop condition detected
            UCB0IFG &= ~UCSTPIFG;  // Clear STOP flag
            break;

        default:
            break;
    }
    
}
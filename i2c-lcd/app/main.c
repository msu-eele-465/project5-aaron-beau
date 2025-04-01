
#include <msp430.h>
#include "lcd_control.h"

const char widnow_size[3] = {0b01001110, 0b00111101};
const char set_window[15] = {0b01110011, 0b01100101, 0b01110100, 0b00010000, 0b01110111, 0b01101001, 0b01101110, 0b01100100, 0b01101111, 0b01110111, 0b00010000, 0b01110011, 0b01101001, 0b01111010, 0b01100101};
const char set_pattern[11] = {0b01110011, 0b01100101, 0b01110100, 0b00010000, 0b01110000, 0b01100001, 0b01110100, 0b01110100, 0b01100101, 0b01110010, 0b01101110};
const char pattern_static[6] = {0b01110011, 0b01110100, 0b01100001, 0b01110100, 0b01101001, 0b01100011};
const char pattern_toggle[6] = {0b01110100, 0b01101111, 0b01100111, 0b01100111, 0b01101100, 0b01100101};
const char pattern_up_counter[10] = {0b01110101, 0b01110000, 0b00010000, 0b01100011, 0b01101111, 0b01110101, 0b01101110, 0b01110100, 0b01100101, 0b01110010};
const char pattern_in_and_out[10] = {0b01101001, 0b01101110, 0b00010000, 0b01100001, 0b01101110, 0b01100100, 0b00010000, 0b01101111, 0b01110101, 0b01110100};
                 
                        
unsigned int i;
int status;
int RXDATA = 0x6;

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

            case 0x5:   LCD_Clear();
                        for(i = 0; i < 15; i++){
                            LCD_write(set_window[i]);
                        }
                        RXDATA = 0;
                        break;

            case 0x6:   LCD_Clear();
                        for(i = 0; i < 11; i++){
                            LCD_write(set_pattern[i]);
                        }
                        RXDATA = 0;
                        break;
                    
            default:    break;
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
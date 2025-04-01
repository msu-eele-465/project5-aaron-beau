
#include <msp430.h>
#include "lcd_control.h"
//"N ="
const char window_size[2] = {0b01001110, 0b00111101};
//"set window size"
const char set_window_size[15] = {0b01110011, 0b01100101, 0b01110100, 0b00010000, 0b01110111, 0b01101001, 0b01101110, 0b01100100, 0b01101111, 0b01110111, 0b00010000, 0b01110011, 0b01101001, 0b01111010, 0b01100101};
//"set pattern"
const char set_pattern[11] = {0b01110011, 0b01100101, 0b01110100, 0b00010000, 0b01110000, 0b01100001, 0b01110100, 0b01110100, 0b01100101, 0b01110010, 0b01101110};
///"static"
const char pattern_static[6] = {0b01110011, 0b01110100, 0b01100001, 0b01110100, 0b01101001, 0b01100011};
//"toggle"
const char pattern_toggle[6] = {0b01110100, 0b01101111, 0b01100111, 0b01100111, 0b01101100, 0b01100101};
//"up counter"
const char pattern_up_counter[10] = {0b01110101, 0b01110000, 0b00010000, 0b01100011, 0b01101111, 0b01110101, 0b01101110, 0b01110100, 0b01100101, 0b01110010};
//"in and out"
const char pattern_in_and_out[10] = {0b01101001, 0b01101110, 0b00010000, 0b01100001, 0b01101110, 0b01100100, 0b00010000, 0b01101111, 0b01110101, 0b01110100};
//numbers 0-9
const char n_size[10] = {0b00110001, 0b00110001, 0b00110010, 0b00110011, 0b00110100, 0b00110101, 0b00110110, 0b00110111, 0b00111000, 0b00111001};              
                        
unsigned int i;
int user_mode = 0xA;
int select_output;
int RXDATA = 0xA;
int wait;
int user_size = 0;
int pattern_number = 0;
int print_window_size;


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

        if(user_mode == 0xA){                               //Window size input operation
            for(i = 0; i< 15; i++){
                LCD_write(set_window_size[i]);              //print "set window size"
            }
            RXDATA = 0;                                     //clear RXDATA for next transmission
            while(wait == 1){                               //wait for window size from user
                if(RXDATA != 0){                            //enter when a valid value has been chosen
                    user_size = RXDATA;                  
                    wait = 0;                               //clear wait flag
                    user_mode = 0;                          //set user mode to zero to stop reprint
                    print_window_size = 0;                  //set flag that window size can be printed
                }
                
                }
            }
        
        else if(user_mode == 0xB){                          //Pattern select operation
            for(i = 0; i < 11; i++){                        
                LCD_write(set_pattern[i]);                  //print "set pattern"
            }
            RXDATA = 0;                                     //clear RXDATA for next transmission
            while(wait == 1){                               //wait for pattern to be selected
                if(RXDATA != 0){                            //if valid pattern was selected
                    pattern_number = RXDATA;                
                    wait = 0;                               //clear wait flag
                    user_mode = 0;                          //clear flag to stop rewrite
                }
            }
        }

        switch(pattern_number){
            case 0x1:   for(i = 0; i < 6; i++){
                        LCD_write(pattern_static[i]);       //print "static"
                        }
                        pattern_number = 0;                 //clear to stop rewrite
                        break;

            case 0x2:   for(i = 0; i < 6; i++){
                        LCD_write(pattern_toggle[i]);       //print "toggle"
                        }
                        pattern_number = 0;                 //clear to stop rewrite
                        break;

            case 0x3:   for(i = 0; i < 10; i++){
                        LCD_write(pattern_up_counter[i]);   //print "up counter"
                        }
                        pattern_number = 0;                 //clear to stop rewrite
                        break;

            case 0x4:   for(i = 0; i < 10; i++){
                        LCD_write(pattern_in_and_out[i]);   //print "in and out"
                        }
                        pattern_number = 0;                 //clear to stop rewrite
                        break;

            default:    break;
        }

        if(print_window_size == 0){
            LCD_command(0xCD);                  //move to third to last character of second row
            for(i = 0; i < 2; i++){             //print "N =""
                LCD_write(window_size[i]);
            }
                LCD_write(n_size[user_size]); //print number that was entered by user
                print_window_size = 1;          //set flag that window # has been written
        }

        
    }   
        
       
                 

        

        P1OUT ^= BIT1;                      // Toggle P1.0 using exclusive-OR
        __delay_cycles(100000);             // Delay for 100000*(1/MCLK)=0.1s
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

            if(RXDATA == 0xA | 0xB){       //check to see if user mode has been selected
                RXDATA = user_mode;
                wait = 1;                   //set flag to wait for second transmission
            }
            
            break;

        case 0x12:  // UCSTPIFG: Stop condition detected
            UCB0IFG &= ~UCSTPIFG;  // Clear STOP flag
            break;

        default:
            break;
    }
    
}
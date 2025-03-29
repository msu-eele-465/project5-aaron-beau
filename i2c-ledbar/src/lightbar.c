/*
This module contains all of the pattern information that is driven to the off board LED bar display.
An integer denoting which pattern is desired is passed into the function and will then be driven 
through the timer ISR within the main loop of the system.  A count flag is implemented so that when a 
pattern is changed it can return to the place where it was before the pattern was changed.  All ports are
directly driven to the off board LED bar display
*/

#include "lightbar.h"
#include "intrinsics.h"
#include "msp430fr2310.h"
#include <stdint.h>

int lightbar(int count, int patt, uint8_t value){        //function to carry through each pattern


 if (patt == 1){
    P1OUT |= BIT0;               //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT |= BIT6;               //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT |= BIT7;               //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT |= BIT5;               //Light 4
    P1OUT &= ~BIT4;              //Light 3
 }else if (patt==2){
    if(count ==0){
    P1OUT |= BIT0;               //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT |= BIT6;               //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT |= BIT7;               //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT |= BIT5;               //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count++;
    }else if (count ==1) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT |= BIT7;               //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT |= BIT0;               //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT |= BIT6;               //Light 5
    P1OUT &= ~BIT5;              //Light 4
    P1OUT |= BIT4;               //Light 3
    count++;
    }else if (count ==2) {
    P1OUT |= BIT0;               //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT |= BIT6;               //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT |= BIT7;               //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT |= BIT5;               //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count++; 
    }else if (count ==3) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT |= BIT7;               //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT |= BIT0;               //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT |= BIT6;               //Light 5
    P1OUT &= ~BIT5;              //Light 4
    P1OUT |= BIT4;               //Light 3
    count++; 
    }else if (count ==4) {
    P1OUT |= BIT0;               //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT |= BIT6;               //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT |= BIT7;               //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT |= BIT5;               //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count++;
    }else if (count ==5) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT |= BIT7;               //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT |= BIT0;               //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT |= BIT6;               //Light 5
    P1OUT &= ~BIT5;              //Light 4
    P1OUT |= BIT4;               //Light 3
    count++;
    }else if (count ==6) {
    P1OUT |= BIT0;               //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT |= BIT6;               //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT |= BIT7;               //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT |= BIT5;               //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count++;
    }else if (count ==7) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT |= BIT7;               //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT |= BIT0;               //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT |= BIT6;               //Light 5
    P1OUT &= ~BIT5;              //Light 4
    P1OUT |= BIT4;               //Light 3
    count=0;
    }
    }else if (patt==3){
    // Use bitwise operations to light up LEDs based on the 8-bit value
    if (value & BIT0){ 
        P1OUT |= BIT4;
    }else{
        P1OUT &= ~BIT4;
    }
    if (value & BIT1){
        P1OUT |= BIT5; 
    }else {
        P1OUT &= ~BIT5;
    }
    if (value & BIT2){ 
        P1OUT |= BIT6;  
    }else{ 
        P1OUT &= ~BIT6;
    }
    if (value & BIT3) {
        P1OUT |= BIT7; 
    }else{ 
        P1OUT &= ~BIT7;
    }
    if (value & BIT4) {
        P2OUT |= BIT0;
    }else{
        P2OUT &= ~BIT0;
    }
    if (value & BIT5) {
        P2OUT |= BIT6;
    }else{ 
        P2OUT &= ~BIT6;
    }
    if (value & BIT6) {
        P2OUT |= BIT7;
    }else{
        P2OUT &= ~BIT7;
    }
    if (value & BIT7) { 
        P1OUT |= BIT0;
    }else{
        P1OUT &= ~BIT0;
    }
}

else if (patt==4){
    if(count ==0){
    P1OUT &= ~BIT0;              //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT |= BIT0;              //Light 7
    P1OUT |= BIT7;              //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT &= ~BIT5;              //Light 4
    P1OUT &= ~BIT4;               //Light 3
    count++;
    }else if (count ==1) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT |= BIT6;              //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT |= BIT6;              //Light 5
    P1OUT &= ~BIT5;               //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count++;
    }else if (count ==2) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT |= BIT7;              //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT &= ~BIT6;               //Light 5
    P1OUT |= BIT5;              //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count++; 
    }else if (count ==3) {
    P1OUT |= BIT0;              //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT &= ~BIT7;               //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT &= ~BIT5;              //Light 4
    P1OUT |= BIT4;              //Light 3
    count++; 
    }else if (count ==4) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT |= BIT7;              //Light 9
    P2OUT &= ~BIT6;              //Light 8
    P2OUT &= ~BIT0;               //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT &= ~BIT6;              //Light 5
    P1OUT |= BIT5;              //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count++;
    }else if (count ==5) {
    P1OUT &= ~BIT0;              //Light 10
    P2OUT &= ~BIT7;              //Light 9
    P2OUT |= BIT6;               //Light 8
    P2OUT &= ~BIT0;              //Light 7
    P1OUT &= ~BIT7;              //Light 6
    P1OUT |= BIT6;              //Light 5
    P1OUT &= ~BIT5;              //Light 4
    P1OUT &= ~BIT4;              //Light 3
    count=0;
    }
}


    return count;
}

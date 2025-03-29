



#include <msp430.h>
#include <stdint.h>


int main(void){
    WDTCTL = WDTPW | WDTHOLD        // Stop watchdog timer


    PM5CTL0 &= ~LOCKLPM5;           // Disable GPIO power-on default high-imedance mode



return 0;
}
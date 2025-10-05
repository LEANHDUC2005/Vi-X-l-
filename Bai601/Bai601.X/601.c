// 'C' source line config statements
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 20000000UL
unsigned char d;
unsigned char dem = 0;
void main(void) {
    
    d = 0;
    TRISD = 0;
    PORTD = d;
    
    T1CONbits.TMR1ON = 1;  
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 1;
     
    // TMR1 = 21786 = 551A
    TMR1H = 0x55; 
    TMR1L = 0x1A;
    
    while(1)
    {
        PORTD = d;
        if ( PIR1bits.TMR1IF )
        {
            PIR1bits.TMR1IF = 0;
            TMR1H = 0x55;
            TMR1L = 0x1A;
            dem++;
            // Tran du 3 lan
            if ( dem == 3 ) 
            {
                // bat 8 LED
                d = ~d;
                PORTD = d;
                dem = 0;    
            }           
        }      
    }  
    return;
}

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000UL
unsigned char dem = 0;
unsigned char d;
void main(void)
{
    // Khoi tao TIMER1
    TMR0 = 0x06;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 0;
    
    d = 0xFF;
    TRISD = 0;
    PORTD = d;
    INTCONbits.T0IF = 0;
    
    while(1)
    {
        if( INTCONbits.T0IF )
        {
            INTCONbits.T0IF = 0;
            TMR0 = 0x06;
            dem++;
            if ( dem == 13 )
            {
                d = ~d;
                PORTD = d;
                dem = 0;
            }
        } 
    } 
}

/* test
void main(void)
{
    TRISD = 0;
    PORTD = d;
    while(1)
    {
        d = ~d;
        PORTD = d;
        __delay_ms(26);
    }
}
*/
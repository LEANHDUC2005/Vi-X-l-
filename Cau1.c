/ 'C' source line config statements
#define _XTAL_FREQ 4000000
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

void LED16_sangduoi(unsigned char start)
{
    char i;
    
    for(i = 0; i < 16 ; i++)
    {
       
       if( i < 8 )
       {
           PORTC = (unsigned char)( start >> i ); 
           PORTD = 0;
           __delay_ms(200);
       }
       
       else
       {
           PORTC = 0;
           PORTD = (unsigned char)( start >> ( i % 8));
           __delay_ms(200);
       }    
       
    }
}
void LED16_sangdan(unsigned char start) //0x80
{
    char i;
    PORTC = 0;
    PORTD = 0;
    
    for(i = 0; i < 16; i++)
    {
        if ( i < 8 )
        {
            PORTC = (unsigned char)( PORTC | (start >> i));
            PORTD = 0;
        }
        
        else 
        {
            PORTD = (unsigned char)( PORTD | (start >> ( i % 8)));
        }  
        
        __delay_ms(200);          
    } 
}

void LED16_sangluu(unsigned char left, unsigned char right) //0x80
{
    for(int i = 0; i <= 8; i++)
    {
        PORTC = (unsigned char)( PORTC | ( left >> i ) );
        PORTD = (unsigned char)( PORTD | ( right << i) );
        __delay_ms(300);      
        
        if ( ( PORTC & PORTD ) == 0xff )
        {
            PORTC = PORTD = 0;
        }
        
    }  
}


void main(void) {
    ANSEL = ANSELH = 0;
    TRISC = 0;
    TRISD = 0;
    PORTC = PORTD = 0;
    while(1)
    {
        LED16_sangdan(0x80);
        LED16_sangduoi(0x80);
        LED16_sangluu(0x80, 0x01);    
    }
    return;
}

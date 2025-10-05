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
#define _XTAL_FREQ 20000000UL // Th?ch anh 20 MHz
unsigned int d; // 8-bit bi?n ?i?u khi?n PORTD
void main(void) 
{
// --- C?u hình PORTD ---
           TRISD = 0x00; // PORTD là output
           d=0x00;
           PORTD = d; // Ban ??u t?t LED
// --- C?u hình Timer1 ---
           T1CONbits.TMR1CS = 0; // Clock n?i (Fosc/4)
           T1CONbits.T1CKPS = 0b11; // Prescaler 1:8
           T1CONbits.TMR1ON = 1; // B?t Timer1
// N?p tr??c Timer1 cho ~105 ms
           TMR1H = 0x00;
           TMR1L = 0x00;
           while (1) 
           {
              if (PIR1bits.TMR1IF == 1) 
              {
                         d = ~d; // ??o tr?ng thái LED
                         PORTD = d; // Xu?t ra PORTD
                         PIR1bits.TMR1IF = 0; // Xóa c? tràn
              }
           }
}
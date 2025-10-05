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
#include <stdint.h>
#define _XTAL_FREQ 20000000UL
// B?ng mã 7 ?o?n (common cathode) cho s? 0?9
// Mã 7 ?o?n cho Anode chung (gfedcba)
const uint8_t ma7doan[10] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90 // 9
};
void main(void) 
{
// --- C?u hình PORT ---
    TRISB = 0x00; // PORTB output (LED hàng ch?c)
    TRISD = 0x00; // PORTD output (LED hàng ??n v?)
    PORTB = 0x00;
    PORTD = 0x00;
// --- C?u hình Timer1 ? ch? ?? counter ---
    T1CONbits.TMR1CS = 1; // Clock ngoài qua chân T1CKI (RC0)
    T1CONbits.T1CKPS = 0; // Prescaler = 1:1
    T1CONbits.T1OSCEN = 0; // T?t oscillator ph?
    T1CONbits.TMR1ON = 1; // B?t Timer1
    TMR1H = 0; // Reset Timer1
    TMR1L = 0;
            
    while(1) {
        uint16_t t1 = ((uint16_t)TMR1H << 8) | TMR1L; // ??c 16-bit Timer1
        // Hi?n th? s? ??n v? (PORTD)
        PORTD = ma7doan[t1 % 10];
        // Hi?n th? s? hàng ch?c (PORTB)
        if (t1 / 10 == 0)
            PORTB = 0xFF; // T?t LED hàng ch?c khi ch?a có s?
        else
            PORTB = ma7doan[(t1 / 10) % 10];
        // Reset khi ?? 100 xung
        if (t1 >= 100) 
        {
            TMR1H = 0;
            TMR1L = 0;
        }
    }
      
}
